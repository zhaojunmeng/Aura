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
#ifndef __AuraEngine_H__
#define __AuraEngine_H__

#include "Ogre.h"
#include "OgreBuildSettings.h"
#include "OgreLogManager.h"
#include "OgrePlugin.h"
#include "OgreFileSystemLayer.h"
#include "OgreOverlaySystem.h"

#include "AuraApplication.h"
#include "AuraIOEngine.h"
#include "AuraQCARController.h"
#include "AuraAudioController.h"
#include "AuraLog.h"
#include "Singleton.h"

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
#    ifndef USE_RTSHADER_SYSTEM
#      define USE_RTSHADER_SYSTEM
#    endif
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
  
  class AuraApplication;
  
  /*=============================================================================
    | Base class responsible for setting up a common context.
    =============================================================================*/
  class AuraEngine : public Ogre::FrameListener, public Ogre::WindowEventListener
    {

    public:
      AuraEngine();
      virtual ~AuraEngine();

      virtual void init( );
      
      virtual void start(AuraApplication* app) = 0;

      AuraApplication* getAuraApp(){return mAuraApp; }

      void updateBackground();
      
      void _initEngine();
      void _initResources();
      void _freeEngine();

      virtual void createRoot();
      virtual void createWindow() = 0;
      virtual void setupInput();

      virtual void loadConfigFile(Ogre::ConfigFile& cf);
      void locateResources();
      void loadResources();
      void createBackground();

      void finish() {
#if OGRE_PLATFORM == OGRE_PLATFORM_ANDROID
	AuraJNIUtils::getInstance()->finishActivity();
#endif
      }


      void engineRenderOneFrame(Ogre::Real differenceInSeconds = Ogre::Real(0));

      bool frameStarted(const Ogre::FrameEvent& evt){ 
	if(mSceneCreated) return mAuraApp->frameStarted(evt); 
	return true;
      }
      bool frameEnded(const Ogre::FrameEvent& evt){ 
       	if(mSceneCreated) return mAuraApp->frameEnded(evt); 
	return true;
      } 

      bool mInit;
      bool mSceneCreated;
      AuraApplication* mAuraApp;
      AuraIOEngine* mIOEngine;
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

      // Some variables to optimize backgrond drawing
      int mTexBytesRow;
      int mFrameWidth, mFrameHeight;
      int mFrameImageId;
    };
}

#endif // _AuraEngine_h_
