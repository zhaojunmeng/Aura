#ifndef _AuraOgreEngineIOS_H_
#define _AuraOgreEngineIOS_H_

#if  OGRE_PLATFORM == OGRE_PLATFORM_APPLE_IOS
#include "macUtils.h"
#   ifdef __OBJC__
#       import <UIKit/UIKit.h>
#   endif
#endif

#include "AuraEngine.h"

@interface AuraApplicationGestureView : UIView
{
  Aura::AuraEngine *mEngine;
}
@property (assign) Aura::AuraEngine *mEngine;
		   
@end

namespace Aura{

  class AuraEngineIOS: public AuraEngine
  {
  public:
    
    AuraEngineIOS();

    virtual void init();
    virtual void createWindow();
    
  private:
    AuraApplicationGestureView *mGestureView;
  };
} // Aura

#endif //_AuraOgreEngineIOS_H_
