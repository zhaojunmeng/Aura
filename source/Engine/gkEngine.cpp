/*
-------------------------------------------------------------------------------
    This file is part of OgreKit.
    http://gamekit.googlecode.com/

    Copyright (c) 2006-2013 Charlie C.

    Contributor(s): xat.
-------------------------------------------------------------------------------
  This software is provided 'as-is', without any express or implied
  warranty. In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
-------------------------------------------------------------------------------
*/

#include "gkEngine.h"
#include "gkWindowSystem.h"
#include "gkWindow.h"
//#include "gkScene.h"
//#include "gkSceneManager.h"
#include "gkLogger.h"
//#include "gkUtils.h"
#include "gkRenderFactory.h"
#include "gkUserDefs.h"
//#include "gkTextManager.h"
//#include "gkDynamicsWorld.h"
//#include "gkDebugScreen.h"
//#include "gkDebugProperty.h"
#include "gkTickState.h"
//#include "gkDebugFps.h"
//#include "gkStats.h"
//#include "gkMessageManager.h"
//#include "gkMeshManager.h"
//#include "gkGroupManager.h"
//#include "gkGameObjectManager.h"
//#include "gkResourceGroupManager.h"

//# include "Sound/gkSoundManager.h"

// Ogre includes
#include "OgreRoot.h"
#include "OgreConfigFile.h"
#include "OgreRenderSystem.h"
#include "OgreStringConverter.h"
#include "OgreFrameListener.h"
#include "OgreOverlayManager.h"

// temporary hack for keeping compatibility with ogre18 due to the android-version
#ifndef BUILD_OGRE18
#include "OgreOverlaySystem.h"
#endif

#ifdef OGREKIT_USE_RTSHADER_SYSTEM
//#include "OgreRTShaderSystem.h"
#endif

// shorthand
#define gkOgreEnginePrivate			gkEngine::Private
#define ENGINE_TICKS_PER_SECOND		gkScalar(60)

// tick states
gkScalar gkEngine::m_tickRate = ENGINE_TICKS_PER_SECOND;


class gkOgreEnginePrivate : public Ogre::FrameListener, public gkTickState
{
public:
	Private(gkEngine* par)
		:       gkTickState(par->getTickRate()),
		        engine(par),
		        windowsystem(0),
			timer(0),
			root(0)

	{
		timer = new btClock();
		timer->reset();
		curTime = timer->getTimeMilliseconds();

		plugin_factory = new gkRenderFactoryPrivate();
	}

	virtual ~Private()
	{
		delete timer;
		delete plugin_factory;
	}


	// one full update
	void tickImpl(gkScalar delta);
	void beginTickImpl(void);
	void endTickImpl(void);

	bool frameStarted(const Ogre::FrameEvent& evt);
	bool frameRenderingQueued(const Ogre::FrameEvent& evt);
	bool frameEnded(const Ogre::FrameEvent& evt);

	gkEngine*                   engine;
	gkWindowSystem*             windowsystem;       // current window system
	gkRenderFactoryPrivate*     plugin_factory;     // static plugin loading
	Ogre::Root*                 root;
	
	btClock*					timer;
	unsigned long				curTime;

#ifndef BUILD_OGRE18
	Ogre::OverlaySystem*		overlaySystem;
#endif
};




gkEngine::gkEngine(gkUserDefs* oth)
	:	m_window(0),
		m_initialized(false),
		m_ownsDefs(oth != 0),
		m_running(false)
{
	m_private = new gkOgreEnginePrivate(this);
	if (oth != 0)
		m_defs = oth;
	else
		m_defs = new gkUserDefs();
}




gkEngine::~gkEngine()
{
	if (m_initialized)
		finalize();

	// persistent throughout
	gkLogger::disable();

	if (!m_ownsDefs)
	{
		delete m_defs;
		m_defs = 0;
	}
}



void gkEngine::initialize()
{
	if (m_initialized) return;

	gkUserDefs& defs = getUserDefs();
	gkLogger::enable(defs.log, defs.verbose);

	if (defs.rendersystem == OGRE_RS_UNKNOWN)
	{
		gkPrintf("Unknown rendersystem!\n");
		return;
	}

	// Creating the root stuff :)
	Ogre::Root* root = new Ogre::Root("", "");
	m_private->root = root;
	m_private->plugin_factory->createRenderSystem(root, defs.rendersystem);
	m_private->plugin_factory->createParticleSystem(root);
	//	m_private->archive_factory->addArchiveFactory();

#ifndef BUILD_OGRE18
	m_private->overlaySystem = new Ogre::OverlaySystem();
#endif
	const Ogre::RenderSystemList& renderers = root->getAvailableRenderers();
	if (renderers.empty())
	{
		gkPrintf("No rendersystems present\n");
		return;
	}

	root->setRenderSystem(renderers[0]);
#if defined(_MSC_VER) && defined(OGRE_BUILD_RENDERSYSTEM_GLES2)
	renderers[0]->setConfigOption("RTT Preferred Mode", "Copy"); //angleproject gles2
#endif

	root->initialise(false);

	m_private->windowsystem = new gkWindowSystem();

	initializeWindow();

	// Load the resources :) Good thing, I guess
	if (!defs.resources.empty())
		loadResources(defs.resources);

#ifdef OGREKIT_USE_RTSHADER_SYSTEM	
	defs.hasFixedCapability = renderers[0]->getCapabilities()->hasCapability(Ogre::RSC_FIXED_FUNCTION);

	gkResourceGroupManager::getSingleton().initRTShaderSystem(
		m_private->plugin_factory->getShaderLanguage(), defs.shaderCachePath, defs.hasFixedCapability);
#endif

	// create the builtin resource group
	//gkResourceGroupManager::getSingleton().createResourceGroup(GK_BUILTIN_GROUP);

	//gkResourceGroupManager::getSingleton().initialiseAllResourceGroups();

#ifdef OGREKIT_USE_PARTICLE
	//gkParticleManager::getSingleton().initialize();
#endif

#ifdef OGREKIT_USE_COMPOSITOR
	//gkCompositorManager::getSingleton().initialize();
#endif





	m_initialized = true;

	// Maybe more things here :)

}




void gkEngine::initializeWindow(void)
{
	if (m_private->windowsystem && !m_window)
	{
		gkWindowSystem* sys = m_private->windowsystem;
		gkUserDefs& defs = getUserDefs();

		m_window = sys->createWindow(defs);
	}
}





void gkEngine::finalize()
{
	if (!m_initialized) return;	

#ifdef OGREKIT_OPENAL_SOUND
	//gkSoundManager::getSingleton().stopAllSounds();
#endif	

#ifdef OGREKIT_USE_PARTICLE
	//delete gkParticleManager::getSingletonPtr();
#endif
	//delete gkHUDManager::getSingletonPtr();
	//delete gkAnimationManager::getSingletonPtr();

#ifdef OGREKIT_OPENAL_SOUND
	//delete gkSoundManager::getSingletonPtr();
#endif

#ifdef OGREKIT_USE_RTSHADER_SYSTEM
	//Ogre::MaterialManager::getSingleton().setActiveScheme(Ogre::MaterialManager::DEFAULT_SCHEME_NAME);
	//Ogre::RTShader::ShaderGenerator::finalize();
#endif

#ifndef BUILD_OGRE18
	delete m_private->overlaySystem;
#endif
	delete m_private->root;
	delete m_private;

	m_initialized = false;
}




gkUserDefs& gkEngine::getUserDefs(void)
{
	GK_ASSERT(m_defs);
	return *m_defs;
}

void gkEngine::requestExit(void)
{
	gkWindowSystem::getSingleton().exit(true);
}

void gkEngine::loadResources(const gkString& name)
{
	if (name.empty()) return;

	try
	{
		Ogre::ConfigFile fp;
		fp.load(name);

		Ogre::ResourceGroupManager* resourceManager = Ogre::ResourceGroupManager::getSingletonPtr();
		Ogre::ConfigFile::SectionIterator cit = fp.getSectionIterator();

		while (cit.hasMoreElements())
		{
			gkString elementname = cit.peekNextKey();
			Ogre::ConfigFile::SettingsMultiMap* ptr = cit.getNext();
			for (Ogre::ConfigFile::SettingsMultiMap::iterator dit = ptr->begin(); dit != ptr->end(); ++dit)
				resourceManager->addResourceLocation(dit->second, dit->first, elementname);
		}
		Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
	}
	catch (Ogre::Exception& e)
	{
		gkLogMessage("Engine: Failed to load resource file!\n" << e.getDescription());
	}
}



gkScalar gkEngine::getStepRate(void)
{
	return gkScalar(1.0) / m_tickRate;
}



gkScalar gkEngine::getTickRate(void)
{
	return m_tickRate;
}

void gkEngine::addListener(gkEngine::Listener* listener)
{
	m_listeners.push_back(listener);
}

void gkEngine::removeListener(gkEngine::Listener* listener)
{
	if (m_listeners.find(listener))
		m_listeners.erase(listener);
}


void gkEngine::run(void)
{
	if (!initializeStepLoop()) return;

	while (stepOneFrame());

	finalizeStepLoop();

}

bool gkEngine::initializeStepLoop(void)
{
	// init main game loop

	GK_ASSERT(m_private);

	gkWindowSystem* sys = m_private->windowsystem;
	if (!sys)
	{
		gkLogMessage("Engine: Can't run with out a window system. exiting\n");
		return false;
	}


	// setup timer
	m_private->root->clearEventTimes();
	m_private->root->getRenderSystem()->_initRenderTargets();
	m_private->root->addFrameListener(m_private);
	m_private->reset();

	m_running = true;

	return true;
}


bool gkEngine::stepOneFrame(void)
{
	m_private->curTime = m_private->timer->getTimeMilliseconds();

	gkWindowSystem* sys = m_private->windowsystem;
	sys->process();

	if (!m_private->root->renderOneFrame())
		return false;

	return !sys->exitRequest();
}


void gkEngine::finalizeStepLoop(void)
{
	m_private->root->removeFrameListener(m_private);
	m_running = false;
}

unsigned long gkEngine::getCurTime()
{
	return m_private->curTime;
}

bool gkOgreEnginePrivate::frameStarted(const Ogre::FrameEvent& evt)
{




	return true;
}



bool gkOgreEnginePrivate::frameRenderingQueued(const Ogre::FrameEvent& evt)
{



}




bool gkOgreEnginePrivate::frameEnded(const Ogre::FrameEvent& evt)
{

	return true;
}




void gkOgreEnginePrivate::beginTickImpl(void)
{

}




void gkOgreEnginePrivate::endTickImpl(void)
{

}




void gkOgreEnginePrivate::tickImpl(gkScalar dt)
{
	// dispatch inputs
	windowsystem->dispatch();


	// update callbacks
	utArrayIterator<gkEngine::Listeners> iter(engine->m_listeners);
	while (iter.hasMoreElements())
		iter.getNext()->tick(dt);

}



UT_IMPLEMENT_SINGLETON(gkEngine);
