#ifndef _AuraQCARController_H_
#define _AuraQCARController_H_

#include <jni.h>
#include <android/log.h>
//#include <string.h>
//#include <assert.h>
//#include <stdio.h>

#ifdef USE_OPENGL_ES_1_1
#include <GLES/gl.h>W
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


// Does all the initialization part!

class AuraQCARController{

 public:  
  AuraQCARController();
  ~AuraQCARController();
  
  // Main function!
  void init();

  int getOpenGlEsVersion();
  void setDisplayOrientation(bool isPortrait);
  void renderFrame();
  void configureVideoBackground();
  void initApplicationNative(int width, int height);
  void startCamera();
  void stopCamera();
  void setProjectionMatrix();
  void initRendering();
  void updateRendering(int width, int height);
 
 private:
  unsigned int mScreenWidth;
  unsigned int mScreenHeight;
  bool mPortraitOrientation;
  QCAR::Matrix44F projectionMatrix;
 
  // Tracker
  // Targets
  // Camera
};

#endif // _AuraQCARController_H_
