#ifndef _AuraQCARController_H_
#define _AuraQCARController_H_

#include <jni.h>
#include <android/log.h>
#include <android/native_activity.h>
#include <android_native_app_glue.h>

//#include "AuraJNIUtils.h"
#include "Singleton.h"

#ifdef USE_OPENGL_ES_1_1
#include <GLES/gl.h>
#include <GLES/glext.h>
#else
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#endif

#include <QCAR/QCAR.h>
#include <QCAR/CameraDevice.h>
#include <QCAR/Renderer.h>
#include <QCAR/VideoBackgroundConfig.h>
#include <QCAR/Tool.h>
#include <QCAR/CameraCalibration.h>
#include <QCAR/Frame.h>
#include <QCAR/Image.h>

namespace Aura{


  class AuraQCARController: public Singleton<AuraQCARController>{

  public:  
    AuraQCARController();
    ~AuraQCARController();
  
    QCAR::Frame getFrame();

    void setScreenWidth(int screenWidth){ mScreenWidth = screenWidth; }
    void setScreenHeight(int screenHeight){ mScreenHeight = screenHeight; }
    void configureVideoBackground();
    void stopCamera();
    //void startCamera();

  private:




    // void setDisplayOrientation(bool isPortrait);
    //void renderFrame();
    //void initApplicationNative(int width, int height);
    
    //void setProjectionMatrix();
    //void initRendering();
    //void updateRendering(int width, int height);

  private:
    // Tracker
    // Targets
    // Camera

    unsigned int mScreenWidth;
    unsigned int mScreenHeight;
    bool mPortraitOrientation;
    QCAR::Matrix44F projectionMatrix;

  };

}
#endif // _AuraQCARController_H_
