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


// shorthand
#define ENGINE_TICKS_PER_SECOND		gkScalar(60)

// tick states
gkScalar gkEngine::m_tickRate = ENGINE_TICKS_PER_SECOND;


gkEngine::gkEngine(gkUserDefs* oth)
	:	gkTickState(getTickRate()),
		m_window(0),
		m_initialized(false),
		m_ownsDefs(oth != 0),
		m_running(false),
		m_windowsystem(0),
		m_timer(0),
		m_root(0)

{

  m_timer = new btClock();
  m_timer->reset();
  m_curTime = m_timer->getTimeMilliseconds();
  m_plugin_factory = new gkRenderFactoryPrivate();

	if (oth != 0)
		m_defs = oth;
	else
		m_defs = new gkUserDefs();
}

gkEngine::~gkEngine()
{
	if (m_initialized)
		finalize();

	delete m_timer;
	delete m_plugin_factory;

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
	m_root = root;

	m_plugin_factory->createRenderSystem(root, defs.rendersystem);

	m_plugin_factory->createParticleSystem(root);

#ifndef BUILD_OGRE18
	m_overlaySystem = new Ogre::OverlaySystem();
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

	m_sceneManager = m_root->createSceneManager(Ogre::ST_GENERIC);

	m_windowsystem = new gkWindowSystem();

	initializeWindow();

#ifdef OGREKIT_USE_RTSHADER_SYSTEM	
	defs.hasFixedCapability = renderers[0]->getCapabilities()->hasCapability(Ogre::RSC_FIXED_FUNCTION);

	gkResourceGroupManager::getSingleton().initRTShaderSystem(
		m_plugin_factory->getShaderLanguage(), defs.shaderCachePath, defs.hasFixedCapability);
#endif


	// Create the camera
	m_cam = m_sceneManager->createCamera("MainCamera");
	m_cam->setPosition(Ogre::Vector3(5,10,20));
	m_cam->lookAt(Ogre::Vector3(0,0,0));
	m_cam->setNearClipDistance(5);
	m_cam->setFarClipDistance(10000);


	m_viewport = m_window->addViewport(m_cam);
	m_viewport->getViewport()->setBackgroundColour(Ogre::ColourValue(0.0,0.0,0.0));
	double width = m_viewport->getViewport()->getActualWidth();
	double height = m_viewport->getViewport()->getActualHeight();
	m_cam->setAspectRatio(width / height);


	// Load the resources :) Good thing, I guess
	if (!defs.resources.empty())
		loadResources(defs.resourcesPath + defs.resources);

	m_initialized = true;


}




void gkEngine::initializeWindow(void)
{
	if (m_windowsystem && !m_window)
	{
		gkWindowSystem* sys = m_windowsystem;
		gkUserDefs& defs = getUserDefs();
		m_window = sys->createWindow(defs);
	}
}





void gkEngine::finalize()
{
	if (!m_initialized) return;	

#ifndef BUILD_OGRE18
	delete m_overlaySystem;
#endif

#ifdef OGREKIT_USE_RTSHADER_SYSTEM
	Ogre::MaterialManager::getSingleton().setActiveScheme(Ogre::MaterialManager::DEFAULT_SCHEME_NAME);
	Ogre::RTShader::ShaderGenerator::finalize();
#endif

	delete m_root;

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
			for (Ogre::ConfigFile::SettingsMultiMap::iterator dit = ptr->begin(); dit != ptr->end(); ++dit){
			  resourceManager->addResourceLocation(getUserDefs().resourcesPath + dit->second, dit->first, elementname);
			}
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

void gkEngine::run(void)
{
	if (!initializeStepLoop()) return;

	while (stepOneFrame());

	finalizeStepLoop();

}

bool gkEngine::initializeStepLoop(void)
{
	// init main game loop

	gkWindowSystem* sys = m_windowsystem;
	if (!sys)
	{
		gkLogMessage("Engine: Can't run with out a window system. exiting\n");
		return false;
	}


	// setup timer
	m_root->clearEventTimes();
	m_root->getRenderSystem()->_initRenderTargets();
	m_root->addFrameListener(this);
	reset();

	m_running = true;

	return true;
}


bool gkEngine::stepOneFrame(void)
{
  _LOGI_("Steping one frame");
  _LOGI_("Getting time");
	m_curTime = m_timer->getTimeMilliseconds();


  _LOGI_("Sys process");
	gkWindowSystem* sys = m_windowsystem;
	sys->process();

  _LOGI_("Root render one frame");
  if (!m_root->renderOneFrame())
    return false;

  _LOGI_("Good! rendered! Exit request?");
	return !sys->exitRequest();
}


void gkEngine::finalizeStepLoop(void)
{
	m_running = false;
}

unsigned long gkEngine::getCurTime()
{
	return m_curTime;
}





void gkEngine::tickImpl(gkScalar dt)
{
	// dispatch inputs
	m_windowsystem->dispatch();

	// update callbacks
	utArrayIterator<gkEngine::Listeners> iter(m_listeners);
	while (iter.hasMoreElements())
		iter.getNext()->tick(dt);

}




bool gkEngine::frameRenderingQueued(const Ogre::FrameEvent& evt)
{
  tick();
  return true;
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


// bool gkEngine::frameEnded(const Ogre::FrameEvent& evt)
// {
// 	return true;
// }
// bool gkEngine::frameStarted(const Ogre::FrameEvent& evt)
// {
// 	return true;
// }



UT_IMPLEMENT_SINGLETON(gkEngine);
