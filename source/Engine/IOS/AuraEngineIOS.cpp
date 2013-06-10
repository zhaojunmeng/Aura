#include "AuraEngineIOS.h"

namespace Aura{

  AuraEngineIOS::AuraEngineIOS(): AuraEngine(){
      mGestureView = 0;
    }

  void AuraEngineIOS::start(AuraApplication* app) {
    mAuraApp = app;

    // We init QCAR here, before Ogre
    AuraQCARController::getInstance()->setScreenWidth([[UIScreen mainScreen] bounds].size.width);
    AuraQCARController::getInstance()->setScreenHeight([[UIScreen mainScreen] bounds].size.height);

    //AuraQCARController::getInstance()->setScreenWidth(640);
    //AuraQCARController::getInstance()->setScreenHeight(960);
    
    AuraQCARController::getInstance()->initQCAR_iOS();


    // Init the images from the application
    mAuraApp->initTracker();
    
    // Start camera
    AuraQCARController::getInstance()->startCamera();

    init();
  }

  void AuraEngineIOS::createWindow() {
    mWindow = mRoot->initialise(true, "AuraWindow");
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
