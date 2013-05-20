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


#if OGRE_PLATFORM == OGRE_PLATFORM_ANDROID
#include <android_native_app_glue.h>
#include "Android/OgreAPKFileSystemArchive.h"
#include "Android/OgreAPKZipArchive.h"
#endif

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
		

  protected:
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

#endif // Iphone
#endif // Aura application
