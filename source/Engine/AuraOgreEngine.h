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

      AuraOgreEngine();
      virtual ~AuraOgreEngine();
      virtual void init( );
      virtual Ogre::RenderWindow* createWindow();
      void setup();
      virtual void shutdown();

      virtual bool auraFrameStarted(){return true;}
      virtual bool auraFrameEnded(){return true;}
      virtual bool auraRenderOneFrame(){
	Ogre::WindowEventUtilities::messagePump();
	return mRoot->renderOneFrame();
      }
	
      bool frameStarted(const Ogre::FrameEvent& evt){ return true; }
      bool frameEnded(const Ogre::FrameEvent& evt){  return true; }

      virtual void createRoot();
      virtual void loadConfigFile(Ogre::ConfigFile& cf);
      void locateResources();
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
    };
}

#endif // _AuraOgreEngine_h_
