/*
-------------------------------------------------------------------------------
    This file is part of OgreKit.
    http://gamekit.googlecode.com/

    Copyright (c) 2006-2013 Charlie C.

    Contributor(s): Thomas Trocha(dertom)
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
#ifndef _gkEngine_h_
#define _gkEngine_h_

#include "gkMathUtils.h"
#include "utSingleton.h"
#include "gkWindowSystem.h"
#include "gkWindow.h"
#include "gkLogger.h"
#include "gkRenderFactory.h"
#include "gkUserDefs.h"
#include "gkTickState.h"
#include "gkViewport.h"
#include "gkResourceGroupManager.h"

// Ogre includes
#include "Ogre.h"
/* #include "OgreRoot.h" */
/* #include "OgreConfigFile.h" */
/* #include "OgreRenderSystem.h" */
/* #include "OgreStringConverter.h" */
/* #include "OgreFrameListener.h" */
/* #include "OgreOverlayManager.h" */
/* #include "OgreViewport.h" */

// temporary hack for keeping compatibility with ogre18 due to the android-version
#ifndef BUILD_OGRE18
#include "OgreOverlaySystem.h"
#endif

#ifdef OGREKIT_USE_RTSHADER_SYSTEM
#include "OgreRTShaderSystem.h"
#endif


class gkEngine : public utSingleton<gkEngine>, public Ogre::FrameListener, public gkTickState 
{
public:

	class Listener
	{
	public:
		virtual ~Listener() {}
		virtual void tick(gkScalar rate) = 0;
	};

	typedef utArray<Listener*>	Listeners;

 public: // Public interface :)
	gkEngine(gkUserDefs* otherDefs = 0);
	~gkEngine();

	bool isInitialized(void)  {return m_initialized;}
	bool isRunning(void)      {return m_running;}

	void addListener(Listener* listener);
	void removeListener(Listener* listener);

	void initialize();
	void finalize(void);
	void run(void);

	Ogre::SceneManager* getSceneManager(){ return m_sceneManager;}
	gkUserDefs& getUserDefs(void);

	bool initializeStepLoop(void);
	bool stepOneFrame(void);
	void finalizeStepLoop(void);

private:

	void initializeWindow(void);

	void requestExit(void);

	void loadResources(const gkString& name);

	static gkScalar getStepRate();
	static gkScalar getTickRate();

	unsigned long getCurTime(); //return ms, updated per frame


	// one full update
	void tickImpl(gkScalar delta);

	// Ogre listener
	bool frameRenderingQueued(const Ogre::FrameEvent& evt);


private:

	gkWindow*		m_window;
	bool                    m_initialized;
	bool                    m_ownsDefs;
	bool                    m_running;
	gkUserDefs*             m_defs;
	static gkScalar         m_tickRate;
	gkEngine*               m_engine;
	gkWindowSystem*         m_windowsystem;       // current window system
	gkRenderFactoryPrivate* m_plugin_factory;     // static plugin loading
	btClock*		m_timer;
	unsigned long		m_curTime;
	Listeners               m_listeners;

#ifndef BUILD_OGRE18
	Ogre::OverlaySystem*		m_overlaySystem;
#endif


	// What I really need
	Ogre::Root*             m_root;
	Ogre::Camera* m_cam;
	Ogre::SceneManager* m_sceneManager;
	gkViewport* m_viewport;

	UT_DECLARE_SINGLETON(gkEngine);
};



#endif//_gkEngine_h_
