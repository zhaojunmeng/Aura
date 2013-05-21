#ifndef _AuraOgreEngineIOS_H_
#define _AuraOgreEngineIOS_H_

#if OGRE_PLATFORM == OGRE_PLATFORM_APPLE || OGRE_PLATFORM == OGRE_PLATFORM_APPLE_IOS
#include "macUtils.h"
#if OGRE_PLATFORM == OGRE_PLATFORM_APPLE_IOS
#   ifdef __OBJC__
#       import <UIKit/UIKit.h>
#   endif
#endif
#endif

#if OGRE_PLATFORM == OGRE_PLATFORM_APPLE || OGRE_PLATFORM == OGRE_PLATFORM_APPLE_IOS
#include "macUtils.h"
#endif


class AuraApplication;

#if OGRE_PLATFORM == OGRE_PLATFORM_APPLE_IOS
#   ifdef __OBJC__
#       import <UIKit/UIKit.h>
#   endif

@interface AuraApplicationGestureView : UIView
{
  Aura::AuraApplication *mApp;
}
@property (assign) Aura::AuraApplication *mApp;
		   
@end
#endif

		   

namespace Aura{

  class AuraOgreEngineIOS: public AuraOgreEngine
  {
  public:
    
  AuraOgreEngineIOS(): AuraOgreEngine(){
      mGestureView = 0;

    }


    virtual void init( )
    {
      createRoot();
      Ogre::String nextRenderer = mRoot->getAvailableRenderers()[0]->getName();
      mRoot->setRenderSystem(mRoot->getRenderSystemByName(nextRenderer));
      setup();
      Ogre::Root::getSingleton().getRenderSystem()->_initRenderTargets();
      Ogre::Root::getSingleton().clearEventTimes();
    }


    virtual Ogre::RenderWindow* createWindow()
      {
	Ogre::RenderWindow* res = mRoot->initialise(true, "Aura Application");
	mGestureView = [[SampleBrowserGestureView alloc] init];
	mGestureView.mBrowser = this;
	[[[UIApplication sharedApplication] keyWindow] addSubview:mGestureView];
	return res;
      }


  private:
    AuraApplicationGestureView *mGestureView;

  };
} // Aura



/* Iphone  Objective C binding */
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

#endif //_AuraOgreEngineIOS_H_
