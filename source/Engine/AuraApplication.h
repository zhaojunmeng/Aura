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
#ifndef __AuraApplication_H__
#define __AuraApplication_H__

#include "AuraContext.h"

#if OGRE_PLATFORM == OGRE_PLATFORM_APPLE || OGRE_PLATFORM == OGRE_PLATFORM_APPLE_IOS
#include "macUtils.h"
#endif

#if OGRE_PLATFORM == OGRE_PLATFORM_WINRT
// For the phone we only support running from the cache file.
#    define ENABLE_SHADERS_CACHE_LOAD 1
#endif

#define ENABLE_SHADERS_CACHE_SAVE 1
#define ENABLE_SHADERS_CACHE_LOAD 1

#if OGRE_PLATFORM == OGRE_PLATFORM_ANDROID
#include <android_native_app_glue.h>
#include "Android/OgreAPKFileSystemArchive.h"
#include "Android/OgreAPKZipArchive.h"
#endif
#   ifdef USE_RTSHADER_SYSTEM
#       include "OgreRTShaderSystem.h"

// Remove the comment below in order to make the RTSS use valid path for writing down the generated shaders.
// If cache path is not set - all shaders are generated to system memory.
//#define _RTSS_WRITE_SHADERS_TO_DISK
#   endif // USE_RTSHADER_SYSTEM

#endif // OGRE_STATIC_LIB

#if OGRE_PLATFORM == OGRE_PLATFORM_APPLE_IOS
#   ifdef __OBJC__
#       import <UIKit/UIKit.h>
#   endif

namespace Aura
{
  class AuraApplication;
}

@interface AuraApplicationGestureView : UIView
{
  Aura::AuraApplication *mBrowser;
}
@property (assign) Aura::AuraApplication *mBrowser;

		   @end
#endif

		   namespace Aura
{
#ifdef USE_RTSHADER_SYSTEM

  /** This class demonstrates basic usage of the RTShader system.
      It sub class the material manager listener class and when a target scheme callback
      is invoked with the shader generator scheme it tries to create an equivalent shader
      based technique based on the default technique of the given material.
  */
  class ShaderGeneratorTechniqueResolverListener : public Ogre::MaterialManager::Listener
    {
    public:

      ShaderGeneratorTechniqueResolverListener(Ogre::RTShader::ShaderGenerator* pShaderGenerator)
	{
	  mShaderGenerator = pShaderGenerator;			
	}

      /** This is the hook point where shader based technique will be created.
	  It will be called whenever the material manager won't find appropriate technique
	  that satisfy the target scheme name. If the scheme name is out target RT Shader System
	  scheme name we will try to create shader generated technique for it. 
      */
      virtual Ogre::Technique* handleSchemeNotFound(unsigned short schemeIndex, 
						    const Ogre::String& schemeName, Ogre::Material* originalMaterial, unsigned short lodIndex, 
						    const Ogre::Renderable* rend)
	{	
	  Ogre::Technique* generatedTech = NULL;

	  // Case this is the default shader generator scheme.
	  if (schemeName == Ogre::RTShader::ShaderGenerator::DEFAULT_SCHEME_NAME)
	    {
	      bool techniqueCreated;

	      // Create shader generated technique for this material.
	      techniqueCreated = mShaderGenerator->createShaderBasedTechnique(
									      originalMaterial->getName(), 
									      Ogre::MaterialManager::DEFAULT_SCHEME_NAME, 
									      schemeName);	

	      // Case technique registration succeeded.
	      if (techniqueCreated)
		{
		  // Force creating the shaders for the generated technique.
		  mShaderGenerator->validateMaterial(schemeName, originalMaterial->getName());
				
		  // Grab the generated technique.
		  Ogre::Material::TechniqueIterator itTech = originalMaterial->getTechniqueIterator();

		  while (itTech.hasMoreElements())
		    {
		      Ogre::Technique* curTech = itTech.getNext();

		      if (curTech->getSchemeName() == schemeName)
			{
			  generatedTech = curTech;
			  break;
			}
		    }				
		}
	    }

	  return generatedTech;
	}

    protected:	
      Ogre::RTShader::ShaderGenerator*	mShaderGenerator;			// The shader generator instance.		
    };
#endif // USE_RTSHADER_SYSTEM

  /*=============================================================================
    | The AuraApplication interface :)
    =============================================================================*/
  class AuraApplication : public AuraContext
  {        
  public:

    AuraApplication(bool nograb = false) : AuraContext()
      {
	mIsShuttingDown = false;
	mNoGrabInput = nograb;
#if OGRE_PLATFORM == OGRE_PLATFORM_NACL
	mNaClInstance = 0;
	mNaClSwapCallback = 0;
	mOisFactory = 0;
	mInitWidth = 0;
	mInitHeight = 0;
#endif
		  
#if OGRE_PLATFORM == OGRE_PLATFORM_APPLE_IOS
	mGestureView = 0;
#endif
#ifdef USE_RTSHADER_SYSTEM
	mShaderGenerator	 = NULL;		
	mMaterialMgrListener = NULL;
#endif // USE_RTSHADER_SYSTEM
      }
	  
    /*-----------------------------------------------------------------------------
      | init data members needed only by WinRT
      -----------------------------------------------------------------------------*/
#if (OGRE_PLATFORM == OGRE_PLATFORM_WINRT)
    void initAppForWinRT( Windows::UI::Core::CoreWindow^ nativeWindow, InputContext inputContext)
    {
      mNativeWindow = nativeWindow;
#   if (OGRE_WINRT_TARGET_TYPE == DESKTOP_APP)
      mNativeControl = nullptr;
#	endif // (OGRE_WINRT_TARGET_TYPE == DESKTOP_APP)
      mInputContext = inputContext;
    }
#	if (OGRE_WINRT_TARGET_TYPE == DESKTOP_APP)
    void initAppForWinRT( Windows::UI::Xaml::Shapes::Rectangle ^ nativeControl, InputContext inputContext)
    {
      mNativeWindow = nullptr;
      mNativeControl = nativeControl;
      mInputContext = inputContext;
    }
#	endif // (OGRE_WINRT_TARGET_TYPE == DESKTOP_APP)
#endif // (OGRE_PLATFORM == OGRE_PLATFORM_WINRT)
    /*-----------------------------------------------------------------------------
      | init data members needed only by NaCl
      -----------------------------------------------------------------------------*/
#if OGRE_PLATFORM == OGRE_PLATFORM_NACL
    void initAppForNaCl( pp::Instance* naClInstance, pp::CompletionCallback* naClSwapCallback, OIS::FactoryCreator * oisFactory, Ogre::uint32 initWidth, Ogre::uint32 initHeight )
    {
      mNaClInstance = naClInstance;
      mNaClSwapCallback = naClSwapCallback;
      mOisFactory = oisFactory;
      mInitWidth = initWidth;
      mInitHeight = initHeight;
    }

    void createInputDevices()
    {
      mInputMgr->addFactoryCreator(mOisFactory);
      AuraContext::createInputDevices();
    }
#endif

    /*-----------------------------------------------------------------------------
      | init pre-created window for android
      -----------------------------------------------------------------------------*/
#if OGRE_PLATFORM == OGRE_PLATFORM_ANDROID
    void initAppForAndroid(Ogre::RenderWindow *window, struct android_app* app, OIS::MultiTouch *mouse, OIS::Keyboard *keyboard)
    {
      mWindow = window;
      mInputContext.mMultiTouch = mouse;
      mInputContext.mKeyboard = keyboard;
          
      if(app != NULL)
	{
	  mAssetMgr = app->activity->assetManager;
	  Ogre::ArchiveManager::getSingleton().addArchiveFactory( new Ogre::APKFileSystemArchiveFactory(app->activity->assetManager) );
	  Ogre::ArchiveManager::getSingleton().addArchiveFactory( new Ogre::APKZipArchiveFactory(app->activity->assetManager) );
	}
    }
#endif
	
#if OGRE_PLATFORM == OGRE_PLATFORM_APPLE_IOS
    virtual void motionBegan( void ) = 0;

    virtual void motionEnded( void ) = 0;
    virtual void motionCancelled( void ) = 0;
#endif
		
    /*-----------------------------------------------------------------------------
      | Extends windowResized to best fit menus on screen. 
      -----------------------------------------------------------------------------*/
    virtual void windowResized(Ogre::RenderWindow* rw) = 0;

    /*-----------------------------------------------------------------------------
      | Extends setup to create dummy scene and tray interface.
      -----------------------------------------------------------------------------*/
    virtual void setup()
    {
      if(mWindow == NULL)
	mWindow = createWindow();
		  
      setupInput(mNoGrabInput);
      locateResources();

#if	defined(ENABLE_SHADERS_CACHE_LOAD)
      // Load for a package version of the shaders.
      Ogre::String path = getShaderCacheFileName();
      FILE * inFile = NULL;
      inFile = fopen(path.c_str(), "rb");
      // If that does not exist, see if there is a version in the writable location.
      if (!inFile)
	{
	  path = mFSLayer->getWritablePath(getShaderCacheFileName());
	  inFile = fopen(path.c_str(), "rb");
	}
      if (inFile)
	{
	  Ogre::LogManager::getSingleton().logMessage("Loading shader cache from ");
	  Ogre::LogManager::getSingleton().logMessage(path.c_str());
	  Ogre::DataStreamPtr istream(new Ogre::FileHandleDataStream(path.c_str(), inFile, Ogre::DataStream::READ));
	  Ogre::GpuProgramManager::getSingleton().loadMicrocodeCache(istream);
	}
#endif
	    
      mWindow->removeAllViewports();
      mSceneManager = mRoot->createSceneManager(Ogre::ST_GENERIC, "SceneManager");
      mSceneManager->addRenderQueueListener(mOverlaySystem);
      mCamera = mSceneManager->createCamera("Camera");
      mWindow->addViewport(mCamera);

      createScene();

#ifdef USE_RTSHADER_SYSTEM
      if(mRoot->getRenderSystem()->getCapabilities()->hasCapability(Ogre::RSC_FIXED_FUNCTION) == false)
	{
	  Ogre::RTShader::ShaderGenerator::getSingletonPtr()->addSceneManager(mRoot->getSceneManager("SceneManager"));
	}
#endif // USE_RTSHADER_SYSTEM

      loadResources();

      Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);
            
      // adds context as listener to process context-level (above the sample level) events
      mRoot->addFrameListener(this);
      Ogre::WindowEventUtilities::addWindowEventListener(mWindow, this);
            
      windowResized(mWindow);   // adjust menus for resolution
	    
    }

    /*-----------------------------------------------------------------------------
      | Notify the window size changed or it was moved
      -----------------------------------------------------------------------------*/
    virtual void windowMovedOrResized()
    {
#if (OGRE_PLATFORM == OGRE_PLATFORM_WINRT) && (OGRE_WINRT_TARGET_TYPE == DESKTOP_APP)

      if(mNativeControl)
	{
	  // in WinRT.Xaml case Ogre::RenderWindow is actually brush
	  // applied to native control and we need resize this brush manually
	  mWindow->resize(mNativeControl->ActualWidth, mNativeControl->ActualHeight);
	}
#endif // (OGRE_PLATFORM == OGRE_PLATFORM_WINRT) && (OGRE_WINRT_TARGET_TYPE == DESKTOP_APP)
      mWindow->windowMovedOrResized();	// notify window
      windowResized(mWindow);				// notify window event listeners
    }
        
  protected:

    /*-----------------------------------------------------------------------------
      | Restores config instead of using a dialog to save time.
      | If that fails, the config dialog is shown.
      -----------------------------------------------------------------------------*/
    virtual bool oneTimeConfig()
    {
      if (!mRoot->restoreConfig()) return mRoot->showConfigDialog();
      return true;
    }		

    /*-----------------------------------------------------------------------------
      | Overrides the default window title.
      -----------------------------------------------------------------------------*/
    virtual Ogre::RenderWindow* createWindow()
      {
#if OGRE_PLATFORM == OGRE_PLATFORM_NACL
	Ogre::RenderWindow* res = mRoot->initialise(false, "Aura Application");
	Ogre::NameValuePairList miscParams;
	miscParams["pp::Instance"] = Ogre::StringConverter::toString((unsigned long)mNaClInstance);
	miscParams["SwapCallback"] = Ogre::StringConverter::toString((unsigned long)mNaClSwapCallback);
	// create 1x1 window - we will resize later
	return mRoot->createRenderWindow("Aura Application", mInitWidth, mInitHeight, false, &miscParams);

#elif (OGRE_PLATFORM == OGRE_PLATFORM_WINRT)
	Ogre::RenderWindow* res = mRoot->initialise(false, "Aura Application");
	Ogre::NameValuePairList miscParams;
	if(mNativeWindow.Get())
	  {
	    miscParams["externalWindowHandle"] = Ogre::StringConverter::toString((size_t)reinterpret_cast<void*>(mNativeWindow.Get()));
	    res = mRoot->createRenderWindow("Aura Application", mNativeWindow->Bounds.Width, mNativeWindow->Bounds.Height, false, &miscParams);
	  }
#	if (OGRE_WINRT_TARGET_TYPE == DESKTOP_APP)
	else if(mNativeControl)
	  {
	    miscParams["windowType"] = "SurfaceImageSource";
	    res = mRoot->createRenderWindow("Aura Application", mNativeControl->ActualWidth, mNativeControl->ActualHeight, false, &miscParams);
	    void* pUnk = NULL;
	    res->getCustomAttribute("ImageBrush", &pUnk);
	    mNativeControl->Fill = reinterpret_cast<Windows::UI::Xaml::Media::ImageBrush^>(pUnk);
	  }
#	endif // (OGRE_WINRT_TARGET_TYPE == DESKTOP_APP)

	return res;

#elif OGRE_PLATFORM == OGRE_PLATFORM_ANDROID
	return NULL;
#else
	Ogre::RenderWindow* res = mRoot->initialise(true, "Aura Application");


#if OGRE_PLATFORM == OGRE_PLATFORM_APPLE_IOS
	mGestureView = [[SampleBrowserGestureView alloc] init];
	mGestureView.mBrowser = this;
            
	[[[UIApplication sharedApplication] keyWindow] addSubview:mGestureView];
#endif
			
	return res;
#endif
      }


    virtual void createScene() = 0;


 public:
  /*-----------------------------------------------------------------------------
    | Extends shutdown to destroy dummy scene and tray interface.
    -----------------------------------------------------------------------------*/
  virtual void shutdown()
  {
#if defined(ENABLE_SHADERS_CACHE_SAVE) 
    if (Ogre::GpuProgramManager::getSingleton().isCacheDirty())
      {
	Ogre::String path = mFSLayer->getWritablePath(getShaderCacheFileName());
	FILE * outFile = fopen(path.c_str(), "wb");
	if (outFile)
	  {
	    Ogre::LogManager::getSingleton().logMessage("Writing shader cache to ");
	    Ogre::LogManager::getSingleton().logMessage(path.c_str());
	    Ogre::DataStreamPtr ostream(new Ogre::FileHandleDataStream(path.c_str(), outFile, Ogre::DataStream::WRITE));
	    Ogre::GpuProgramManager::getSingleton().saveMicrocodeCache(ostream);
	    ostream->close();
	  }
      }
#endif

#if OGRE_PLATFORM == OGRE_PLATFORM_APPLE_IOS
    [mGestureView release];
#endif


    
    appShutdown();
    
    mWindow = 0;

    // remove window event listener before shutting down OIS
    Ogre::WindowEventUtilities::removeWindowEventListener(mWindow, this);
    
    shutdownInput();
    
    //unloadSamples();

#ifdef USE_RTSHADER_SYSTEM
    // Finalize the RT Shader System.
    finalizeRTShaderSystem();
#endif // USE_RTSHADER_SYSTEM

  }
 protected:

  virtual void appShutdown() = 0;

  /*-----------------------------------------------------------------------------
    | Finalize the RT Shader system.	
    -----------------------------------------------------------------------------*/
  virtual Ogre::String getShaderCacheFileName()
    {
#if OGRE_DEBUG_MODE
      return "cache_d.bin";
#else
      return "cache.bin";
#endif
    }

#ifdef USE_RTSHADER_SYSTEM

  /*-----------------------------------------------------------------------------
    | Initialize the RT Shader system.	
    -----------------------------------------------------------------------------*/
  virtual bool initializeRTShaderSystem(Ogre::SceneManager* sceneMgr)
  {			
    if (Ogre::RTShader::ShaderGenerator::initialize())
      {
	mShaderGenerator = Ogre::RTShader::ShaderGenerator::getSingletonPtr();

	mShaderGenerator->addSceneManager(sceneMgr);

#if OGRE_PLATFORM != OGRE_PLATFORM_ANDROID && OGRE_PLATFORM != OGRE_PLATFORM_NACL && OGRE_PLATFORM != OGRE_PLATFORM_WINRT
	// Setup core libraries and shader cache path.
	Ogre::StringVector groupVector = Ogre::ResourceGroupManager::getSingleton().getResourceGroups();
	Ogre::StringVector::iterator itGroup = groupVector.begin();
	Ogre::StringVector::iterator itGroupEnd = groupVector.end();
	Ogre::String shaderCoreLibsPath;
	Ogre::String shaderCachePath;
			
	for (; itGroup != itGroupEnd; ++itGroup)
	  {
	    Ogre::ResourceGroupManager::LocationList resLocationsList = Ogre::ResourceGroupManager::getSingleton().getResourceLocationList(*itGroup);
	    Ogre::ResourceGroupManager::LocationList::iterator it = resLocationsList.begin();
	    Ogre::ResourceGroupManager::LocationList::iterator itEnd = resLocationsList.end();
	    bool coreLibsFound = false;

	    // Try to find the location of the core shader lib functions and use it
	    // as shader cache path as well - this will reduce the number of generated files
	    // when running from different directories.
	    for (; it != itEnd; ++it)
	      {
		if ((*it)->archive->getName().find("RTShaderLib") != Ogre::String::npos)
		  {
		    shaderCoreLibsPath = (*it)->archive->getName() + "/cache/";
		    shaderCachePath = shaderCoreLibsPath;
		    coreLibsFound = true;
		    break;
		  }
	      }
	    // Core libs path found in the current group.
	    if (coreLibsFound) 
	      break; 
	  }

	// Core shader libs not found -> shader generating will fail.
	if (shaderCoreLibsPath.empty())			
	  return false;			
								
#ifdef _RTSS_WRITE_SHADERS_TO_DISK
	// Set shader cache path.
#if OGRE_PLATFORM == OGRE_PLATFORM_APPLE_IOS
	shaderCachePath = Ogre::macCachePath();
#elif OGRE_PLATFORM == OGRE_PLATFORM_APPLE
	shaderCachePath = Ogre::macCachePath() + "/org.ogre3d.RTShaderCache";
#endif
	mShaderGenerator->setShaderCachePath(shaderCachePath);		
#endif
#endif
	// Create and register the material manager listener if it doesn't exist yet.
	if (mMaterialMgrListener == NULL) {
	  mMaterialMgrListener = new ShaderGeneratorTechniqueResolverListener(mShaderGenerator);
	  Ogre::MaterialManager::getSingleton().addListener(mMaterialMgrListener);
	}
      }

    return true;
  }

  /*-----------------------------------------------------------------------------
    | Finalize the RT Shader system.	
    -----------------------------------------------------------------------------*/
  virtual void finalizeRTShaderSystem()
  {
    // Restore default scheme.
    Ogre::MaterialManager::getSingleton().setActiveScheme(Ogre::MaterialManager::DEFAULT_SCHEME_NAME);

    // Unregister the material manager listener.
    if (mMaterialMgrListener != NULL)
      {			
	Ogre::MaterialManager::getSingleton().removeListener(mMaterialMgrListener);
	delete mMaterialMgrListener;
	mMaterialMgrListener = NULL;
      }

    // Finalize RTShader system.
    if (mShaderGenerator != NULL)
      {				
	Ogre::RTShader::ShaderGenerator::finalize();
	mShaderGenerator = NULL;
      }
  }
#endif // USE_RTSHADER_SYSTEM

  bool mNoGrabInput;                             // don't grab input devices


#if (OGRE_PLATFORM == OGRE_PLATFORM_WINRT)
  Platform::Agile<Windows::UI::Core::CoreWindow> mNativeWindow;
#	if (OGRE_WINRT_TARGET_TYPE == DESKTOP_APP)
  Windows::UI::Xaml::Shapes::Rectangle^ mNativeControl;
#	endif // (OGRE_WINRT_TARGET_TYPE == DESKTOP_APP)
#endif // (OGRE_PLATFORM == OGRE_PLATFORM_WINRT)
#if OGRE_PLATFORM == OGRE_PLATFORM_NACL
  pp::Instance* mNaClInstance;
  pp::CompletionCallback* mNaClSwapCallback;
  OIS::FactoryCreator * mOisFactory;
  Ogre::uint32 mInitWidth;
  Ogre::uint32 mInitHeight;
#endif
#ifdef USE_RTSHADER_SYSTEM
  Ogre::RTShader::ShaderGenerator*			mShaderGenerator;			// The Shader generator instance.
  ShaderGeneratorTechniqueResolverListener*	mMaterialMgrListener;		// Shader generator material manager listener.	
#endif // USE_RTSHADER_SYSTEM
 public:
#if OGRE_PLATFORM == OGRE_PLATFORM_APPLE_IOS
  AuraApplicationGestureView *mGestureView;
#endif
  bool mIsShuttingDown;
};
}

#if OGRE_PLATFORM == OGRE_PLATFORM_APPLE_IOS

@implementation AuraApplicationGestureView

@synthesize mBrowser;

- (BOOL)canBecomeFirstResponder
{
  return YES;
}

- (void)dealloc {
  [super dealloc];
}

- (void)motionBegan:(UIEventSubtype)motion withEvent:(UIEvent *)event {
  if(mBrowser && event.type == UIEventTypeMotion && event.subtype == UIEventSubtypeMotionShake)
    mBrowser->motionBegan();
        
  if ([super respondsToSelector:@selector(motionBegan:withEvent:)]) {
    [super motionBegan:motion withEvent:event];
  }
}

- (void)motionEnded:(UIEventSubtype)motion withEvent:(UIEvent *)event {
  if(mBrowser && event.type == UIEventTypeMotion && event.subtype == UIEventSubtypeMotionShake)
    mBrowser->motionEnded();
        
  if ([super respondsToSelector:@selector(motionEnded:withEvent:)]) {
    [super motionEnded:motion withEvent:event];
  }
}

- (void)motionCancelled:(UIEventSubtype)motion withEvent:(UIEvent *)event {
  if(mBrowser && event.type == UIEventTypeMotion && event.subtype == UIEventSubtypeMotionShake)
    mBrowser->motionCancelled();
        
  if ([super respondsToSelector:@selector(motionCancelled:withEvent:)]) {
    [super motionCancelled:motion withEvent:event];
  }
}
@end

#endif
