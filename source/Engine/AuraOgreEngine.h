/*
  -----------------------------------------------------------------------------
  This source file is part of OGRE
  (Object-oriented Graphics Rendering Engine)
  For the latest info, see http://www.ogre3d.org/
 
  Copyright (c) 2000-2013 Torus Knot Software Ltd
 
  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:
 
  The above copyright notice and this permission notice shall be included in
  all copies or substantial portions of the Software.
 
  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
  THE SOFTWARE.
  -----------------------------------------------------------------------------
*/
#ifndef __AuraOgreEngine_H__
#define __AuraOgreEngine_H__

#include "Ogre.h"
#include "OgreBuildSettings.h"
#include "OgreLogManager.h"
#include "OgrePlugin.h"
#include "OgreFileSystemLayer.h"
#include "OgreOverlaySystem.h"

#if OGRE_PLATFORM == OGRE_PLATFORM_WINRT
// For the phone we only support running from the cache file.
#    define ENABLE_SHADERS_CACHE_LOAD 1
#endif

#define ENABLE_SHADERS_CACHE_SAVE 1
#define ENABLE_SHADERS_CACHE_LOAD 1

// Static plugins declaration section
// Note that every entry in here adds an extra header / library dependency
#  ifdef OGRE_BUILD_RENDERSYSTEM_GL
#    define OGRE_STATIC_GL
#  endif
#  ifdef OGRE_BUILD_RENDERSYSTEM_GLES
#    define OGRE_STATIC_GLES
#    undef USE_RTSHADER_SYSTEM
#  endif
#  ifdef OGRE_BUILD_RENDERSYSTEM_GLES2
#  undef OGRE_STATIC_GLES
#    define USE_RTSHADER_SYSTEM
#    define OGRE_STATIC_GLES2
#  endif
#  if OGRE_PLATFORM == OGRE_PLATFORM_WIN32 || OGRE_PLATFORM == OGRE_PLATFORM_WINRT
#    ifdef OGRE_BUILD_RENDERSYSTEM_D3D9
#		define OGRE_STATIC_Direct3D9
#    endif
// dx11 will only work on vista and above, so be careful about statically linking
#    ifdef OGRE_BUILD_RENDERSYSTEM_D3D11
#      define OGRE_STATIC_Direct3D11
#    endif
#  endif

#  ifdef OGRE_BUILD_PLUGIN_BSP
#   define OGRE_STATIC_BSPSceneManager
#  endif
#  ifdef OGRE_BUILD_PLUGIN_PFX
#   define OGRE_STATIC_ParticleFX
#  endif
#  ifdef OGRE_BUILD_PLUGIN_CG
#   define OGRE_STATIC_CgProgramManager
#  endif

#  ifdef OGRE_USE_PCZ
#    ifdef OGRE_BUILD_PLUGIN_PCZ
#    define OGRE_STATIC_PCZSceneManager
#    define OGRE_STATIC_OctreeZone
#    endif
#  else
#    ifdef OGRE_BUILD_PLUGIN_OCTREE
#    define OGRE_STATIC_OctreeSceneManager
#  endif
# endif

#include "OgreStaticPluginLoader.h"

#ifdef USE_RTSHADER_SYSTEM
  #include "ShaderController.h"
#endif

namespace Aura
{

  /*=============================================================================
    | Base class responsible for setting up a common context.
    =============================================================================*/
  class AuraOgreEngine : public Ogre::FrameListener, public Ogre::WindowEventListener
      {
      public:
	friend class AuraApplication;

	AuraOgreEngine()
	  {
	    mFSLayer = OGRE_NEW_T(Ogre::FileSystemLayer, Ogre::MEMCATEGORY_GENERAL)(OGRE_VERSION_NAME);
	    mRoot = 0;
	    mWindow = 0;
	    mOverlaySystem = 0;
#ifdef USE_RTSHADER_SYSTEM
	    mShaderController = 0;
#endif
	  }

	virtual ~AuraOgreEngine() 
	  {
	    OGRE_DELETE_T(mFSLayer, FileSystemLayer, Ogre::MEMCATEGORY_GENERAL);
	  }

	virtual void init( )
	{
	  createRoot();
	  Ogre::String nextRenderer = mRoot->getAvailableRenderers()[0]->getName();
	  mRoot->setRenderSystem(mRoot->getRenderSystemByName(nextRenderer));
	  setup();
	}

	virtual Ogre::RenderWindow* createWindow()
	  {
	    Ogre::RenderWindow* res = mRoot->initialise(true, "AuraWindow");
	    return res;
	  }


	void setup()
	{
	  if(mWindow == NULL)  mWindow = createWindow();

	  mSceneManager = mRoot->createSceneManager(Ogre::ST_GENERIC, "SceneManager");
	  mSceneManager->addRenderQueueListener(mOverlaySystem);
	  mCamera = mSceneManager->createCamera("Camera");
      
	  // Load shader!!
#ifdef USE_RTSHADER_SYSTEM
	  mShaderController = new ShaderController(mFSLayer);
#endif

	  locateResources();
	  loadResources();

#ifdef USE_RTSHADER_SYSTEM
	  mShaderController->init();
#endif

	  Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);
            
	  // adds context as listener to process context-level (above the sample level) events
	  mRoot->addFrameListener(this);

#if OGRE_PLATFORM != OGRE_PLATFORM_ANDROID
	  Ogre::WindowEventUtilities::addWindowEventListener(mWindow, this);
#endif
	  windowResized(mWindow);   // adjust menus for resolution

	  // add a bright light above the scene
	  Ogre::Light* light = mSceneManager->createLight();
	  light->setType(Ogre::Light::LT_POINT);
	  light->setPosition(-10, 40, 20);
	  light->setSpecularColour(Ogre::ColourValue::White);

	  //mWindow->removeAllViewports();
	  Ogre::Viewport* viewport = mWindow->addViewport(mCamera);
	  viewport->setBackgroundColour(Ogre::ColourValue(1.0,0.0,0.0));
	  double width = viewport->getActualWidth();
	  double height = viewport->getActualHeight();
	  mCamera->setAspectRatio(width / height);
	}

	
	virtual void shutdown()
	{
#if OGRE_PLATFORM == OGRE_PLATFORM_APPLE_IOS
	  [mGestureView release];
#endif
	  // Shutdown input
	  mWindow = 0;
	  // remove window event listener before shutting down OIS
	  Ogre::WindowEventUtilities::removeWindowEventListener(mWindow, this);
	  
	  if (mRoot)
	    {
	      OGRE_DELETE mOverlaySystem;
	      OGRE_DELETE mRoot;
	    }
	  mStaticPluginLoader.unload();

#ifdef USE_RTSHADER_SYSTEM
	  mShaderController->shutdown();
#endif
	}
	

	virtual bool auraFrameStarted(){return true;}
	virtual bool auraFrameEnded(){return true;}
	virtual bool auraRenderOneFrame(){
	  Ogre::WindowEventUtilities::messagePump();
	  return mRoot->renderOneFrame();
	}
	
	bool frameStarted(const Ogre::FrameEvent& evt){ return true; }
			
	bool frameEnded(const Ogre::FrameEvent& evt){  return true; }

	virtual void createRoot()
	{
	  Ogre::String pluginsPath = Ogre::StringUtil::BLANK;
	  mRoot = OGRE_NEW Ogre::Root(pluginsPath, mFSLayer->getWritablePath("ogre.cfg"), 
				      mFSLayer->getWritablePath("ogre.log"));
	  mStaticPluginLoader.load();
	  mOverlaySystem = OGRE_NEW Ogre::OverlaySystem();
	}

	virtual void loadConfigFile(Ogre::ConfigFile& cf){
	  cf.load(mFSLayer->getConfigFilePath("resources.cfg"));	  
	}

	void locateResources()
	{
	  Ogre::ConfigFile cf;
	  loadConfigFile(cf);

	  Ogre::ConfigFile::SectionIterator seci = cf.getSectionIterator();
	  Ogre::String sec, type, arch;

	  // go through all specified resource groups
	  while (seci.hasMoreElements())
	    {
	      sec = seci.peekNextKey();
	      Ogre::ConfigFile::SettingsMultiMap* settings = seci.getNext();
	      Ogre::ConfigFile::SettingsMultiMap::iterator i;

	      // go through all resource paths
	      for (i = settings->begin(); i != settings->end(); i++)
		{
		  type = i->first;
		  arch = i->second;

#if OGRE_PLATFORM == OGRE_PLATFORM_APPLE || OGRE_PLATFORM == OGRE_PLATFORM_APPLE_IOS
		  // OS X does not set the working directory relative to the app,
		  // In order to make things portable on OS X we need to provide
		  // the loading with it's own bundle path location
		  if (!Ogre::StringUtil::startsWith(arch, "/", false)) // only adjust relative dirs
		    arch = Ogre::String(Ogre::macBundlePath() + "/" + arch);
#endif
		  Ogre::ResourceGroupManager::getSingleton().addResourceLocation(arch, type, sec);
		}
	    }

#ifdef USE_RTSHADER_SYSTEM
	  mShaderController->locateShaderResources();
#endif

	}
		
	void loadResources(){ Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();}

      protected:

        Ogre::FileSystemLayer* mFSLayer; // File system abstraction layer
	Ogre::Root* mRoot;              // OGRE root
	Ogre::OverlaySystem* mOverlaySystem;  // Overlay system
        Ogre::StaticPluginLoader mStaticPluginLoader;
	Ogre::SceneManager* mSceneManager;
	Ogre::Camera* mCamera;
        Ogre::RenderWindow* mWindow;    // render window
#ifdef USE_RTSHADER_SYSTEM
	ShaderController* mShaderController;
#endif


#if (OGRE_PLATFORM == OGRE_PLATFORM_WINRT)
	Platform::Agile<Windows::UI::Core::CoreWindow> mNativeWindow;
#	if (OGRE_WINRT_TARGET_TYPE == DESKTOP_APP)
	Windows::UI::Xaml::Shapes::Rectangle^ mNativeControl;
#	endif // (OGRE_WINRT_TARGET_TYPE == DESKTOP_APP)
#endif // (OGRE_PLATFORM == OGRE_PLATFORM_WINRT)
      };
}

#endif // _AuraOgreEngine_h_

	/* #if (OGRE_NO_VIEWPORT_ORIENTATIONMODE == 0) */
	/* #if (OGRE_PLATFORM == OGRE_PLATFORM_APPLE_IOS) || (OGRE_PLATFORM == OGRE_PLATFORM_ANDROID) */
	/*         void transformInputState(OIS::MultiTouchState &state) */
	/* #else */
	/* 	  void transformInputState(OIS::MouseState &state) */
	/* #endif */
	/*         { */
	/* 	  int w = mWindow->getViewport(0)->getActualWidth(); */
	/* 	  int h = mWindow->getViewport(0)->getActualHeight(); */
	/* 	  int absX = state.X.abs; */
	/* 	  int absY = state.Y.abs; */
	/* 	  int relX = state.X.rel; */
	/* 	  int relY = state.Y.rel; */

	/* 	  switch (mWindow->getViewport(0)->getOrientationMode()) */
	/*             { */
	/*             case Ogre::OR_DEGREE_0: */
	/* 	      break; */
	/*             case Ogre::OR_DEGREE_90: */
	/* 	      state.X.abs = w - absY; */
	/* 	      state.Y.abs = absX; */
	/* 	      state.X.rel = -relY; */
	/* 	      state.Y.rel = relX; */
	/* 	      break; */
	/*             case Ogre::OR_DEGREE_180: */
	/* 	      state.X.abs = w - absX; */
	/* 	      state.Y.abs = h - absY; */
	/* 	      state.X.rel = -relX; */
	/* 	      state.Y.rel = -relY; */
	/* 	      break; */
	/*             case Ogre::OR_DEGREE_270: */
	/* 	      state.X.abs = absY; */
	/* 	      state.Y.abs = h - absX; */
	/* 	      state.X.rel = relY; */
	/* 	      state.Y.rel = -relX; */
	/* 	      break; */
	/*             } */
	/*         } */
	/* #elif (OGRE_NO_VIEWPORT_ORIENTATIONMODE == 1) && (OGRE_PLATFORM == OGRE_PLATFORM_APPLE_IOS) */
	/* 	// Variation based upon device orientation for use with a view controller */
	/* 	void transformInputState(OIS::MultiTouchState &state) */
	/* 	{ */
	/* 	  int w = mWindow->getViewport(0)->getActualWidth(); */
	/* 	  int h = mWindow->getViewport(0)->getActualHeight(); */
	/* 	  int absX = state.X.abs; */
	/* 	  int absY = state.Y.abs; */
	/* 	  int relX = state.X.rel; */
	/* 	  int relY = state.Y.rel; */

	/* 	  UIInterfaceOrientation interfaceOrientation = [UIApplication sharedApplication].statusBarOrientation; */
	/* 	  switch (interfaceOrientation) */
	/* 	    { */
	/*             case UIInterfaceOrientationPortrait: */
	/* 	      break; */
	/*             case UIInterfaceOrientationLandscapeLeft: */
	/* 	      state.X.abs = w - absY; */
	/* 	      state.Y.abs = absX; */
	/* 	      state.X.rel = -relY; */
	/* 	      state.Y.rel = relX; */
	/* 	      break; */
	/*             case UIInterfaceOrientationPortraitUpsideDown: */
	/* 	      state.X.abs = w - absX; */
	/* 	      state.Y.abs = h - absY; */
	/* 	      state.X.rel = -relX; */
	/* 	      state.Y.rel = -relY; */
	/* 	      break; */
	/*             case UIInterfaceOrientationLandscapeRight: */
	/* 	      state.X.abs = absY; */
	/* 	      state.Y.abs = h - absX; */
	/* 	      state.X.rel = relY; */
	/* 	      state.Y.rel = -relX; */
	/* 	      break; */
	/* 	    } */
	/* 	} */
	/* #endif */
