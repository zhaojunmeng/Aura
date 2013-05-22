#ifndef _AuraQCARController_H_
#define _AuraQCARController_H_

#include <jni.h>
#include <string.h>
#include <assert.h>
#include <android/log.h>
#include <stdio.h>


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


// Does all the initialization part!

class AuraQCARController{
  
  AuraQCARController(){
  }

  ~AuraQCARController(){
  }

  
  // Main function!
  void init(){


  }


 int getOpenGlEsVersion(){
#ifdef USE_OPENGL_ES_1_1        
   return 1;
#else
   return 2;
#endif
 }


 void setActivityPortraitMode(bool isPortrait){
   mActivityInPortraitMode = isPortrait;
 }

 void renderFrame(){
   // Clear color and depth buffer 
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   QCAR::State state = QCAR::Renderer::getInstance().begin();
   QCAR::Renderer::getInstance().drawVideoBackground();
   QCAR::Renderer::getInstance().end();
 }


 void configureVideoBackground()
 {
   // Get the default video mode:
   QCAR::CameraDevice& cameraDevice = QCAR::CameraDevice::getInstance();
   QCAR::VideoMode videoMode = cameraDevice.
                                getVideoMode(QCAR::CameraDevice::MODE_DEFAULT);
   
   // Configure the video background
   QCAR::VideoBackgroundConfig config;
   config.mEnabled = true;
   config.mSynchronous = true;
   config.mPosition.data[0] = 0.0f;
   config.mPosition.data[1] = 0.0f;
   
   if (isActivityInPortraitMode)
     {
       config.mSize.data[0] = videoMode.mHeight
	 * (screenHeight / (float)videoMode.mWidth);
       config.mSize.data[1] = screenHeight;

       if(config.mSize.data[0] < screenWidth)
	 {
	   config.mSize.data[0] = screenWidth;
	   config.mSize.data[1] = screenWidth * 
	     (videoMode.mWidth / (float)videoMode.mHeight);
	 }

     }
   else
     {
       config.mSize.data[0] = screenWidth;
       config.mSize.data[1] = videoMode.mHeight
	 * (screenWidth / (float)videoMode.mWidth);

       if(config.mSize.data[1] < screenHeight)
	 {
	   config.mSize.data[0] = screenHeight
	     * (videoMode.mWidth / (float)videoMode.mHeight);
	   config.mSize.data[1] = screenHeight;
	 }
     }


   // Set the config:
   QCAR::Renderer::getInstance().setVideoBackgroundConfig(config);
}


 void initApplicationNative(int width, int height){
   mScreenWidth = width;
   mScreenHeight = height;
}


 void startCamera(){
   // Select the camera to open, set this to QCAR::CameraDevice::CAMERA_FRONT 
   // to activate the front camera instead.
   QCAR::CameraDevice::CAMERA camera = QCAR::CameraDevice::CAMERA_DEFAULT;

   // Initialize the camera:
   if (!QCAR::CameraDevice::getInstance().init(camera))
     return;

   // Configure the video background
   configureVideoBackground();

   // Select the default mode:
   if (!QCAR::CameraDevice::getInstance().selectVideoMode(
							  QCAR::CameraDevice::MODE_DEFAULT))
     return;

   // Start the camera:
   if (!QCAR::CameraDevice::getInstance().start())
     return;
 }


 void stopCamera(){
   QCAR::CameraDevice::getInstance().stop();
   QCAR::CameraDevice::getInstance().deinit();
 }


 void setProjectionMatrix{
   // Cache the projection matrix:
   const QCAR::CameraCalibration& cameraCalibration =
     QCAR::CameraDevice::getInstance().getCameraCalibration();
   projectionMatrix = QCAR::Tool::getProjectionGL(cameraCalibration, 2.0f, 2500.0f);
 }
 
 
 void initRendering(){
   // Define clear color
   glClearColor(0.0f, 0.0f, 0.0f, QCAR::requiresAlpha() ? 0.0f : 1.0f);
 }
 

 void updateRendering(int width, int height){
   // Update screen dimensions
   mScreenWidth = width;
   mScreenHeight = height;
   
   // Reconfigure the video background
   configureVideoBackground();
 }
 
 
 private:
 unsigned int mScreenWidth        = 0;
 unsigned int mScreenHeight       = 0;
 bool mActivityInPortraitMode   = false;
 QCAR::Matrix44F projectionMatrix;
 

 // Tracker
 // Targets
 // Camera
};

#endif // _AuraQCARController_H_
