#include "AuraEngineIOS.h"

namespace Aura{

  AuraEngineIOS::AuraEngineIOS(): AuraEngine(){
      mGestureView = 0;
    }

  void AuraEngineIOS::init( ){
    createRoot();
    Ogre::String nextRenderer = mRoot->getAvailableRenderers()[0]->getName();
    mRoot->setRenderSystem(mRoot->getRenderSystemByName(nextRenderer));
    //setup();
    Ogre::Root::getSingleton().getRenderSystem()->_initRenderTargets();
    Ogre::Root::getSingleton().clearEventTimes();
  }

  void AuraEngineIOS::createWindow() {
    mWindow = mRoot->initialise(true, "Aura Application");
    mGestureView = [[AuraApplicationGestureView alloc] init];
    mGestureView.mEngine = this;
    [[[UIApplication sharedApplication] keyWindow] addSubview:mGestureView];
    
  }
} // Aura



/* Iphone  Objective C binding */
@implementation AuraApplicationGestureView

@synthesize mEngine;

- (BOOL)canBecomeFirstResponder
{
  return YES;
}

- (void)dealloc {
  [super dealloc];
}

- (void)motionBegan:(UIEventSubtype)motion withEvent:(UIEvent *)event {
  if(mEngine && event.type == UIEventTypeMotion && event.subtype == UIEventSubtypeMotionShake)
    mEngine->mAuraApp->motionBegan();
        
  if ([super respondsToSelector:@selector(motionBegan:withEvent:)]) {
    [super motionBegan:motion withEvent:event];
  }
}

- (void)motionEnded:(UIEventSubtype)motion withEvent:(UIEvent *)event {
  if(mEngine && event.type == UIEventTypeMotion && event.subtype == UIEventSubtypeMotionShake)
    mEngine->mAuraApp->motionEnded();
        
  if ([super respondsToSelector:@selector(motionEnded:withEvent:)]) {
    [super motionEnded:motion withEvent:event];
  }
}

- (void)motionCancelled:(UIEventSubtype)motion withEvent:(UIEvent *)event {
  if(mEngine && event.type == UIEventTypeMotion && event.subtype == UIEventSubtypeMotionShake)
    mEngine->mAuraApp->motionCancelled();
        
  if ([super respondsToSelector:@selector(motionCancelled:withEvent:)]) {
    [super motionCancelled:motion withEvent:event];
  }
}
@end
