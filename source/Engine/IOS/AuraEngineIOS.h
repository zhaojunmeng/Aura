#ifndef _AuraOgreEngineIOS_H_
#define _AuraOgreEngineIOS_H_

#if  OGRE_PLATFORM == OGRE_PLATFORM_APPLE_IOS
#include "macUtils.h"
#   ifdef __OBJC__
#       import <UIKit/UIKit.h>
#   endif
#endif

#include "AuraEngine.h"

#import <UIKit/UIKit.h> 
#import <QuartzCore/QuartzCore.h>

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

    virtual void start(AuraApplication* app);
    //virtual void init();
    virtual void createWindow();
        
    AuraApplicationGestureView *mGestureView;
};
} // Aura

#endif //_AuraOgreEngineIOS_H_
