#include "AuraQCARController.h"



AuraQCARController::AuraQCARController(): mScreenWidth(0), mScreenHeight(0), mPortraitOrientation(false){
  }

  AuraQCARController::~AuraQCARController(){
  }

  
  // Main function!
  void AuraQCARController::init(){


  }


 int AuraQCARController::getOpenGlEsVersion(){
#ifdef USE_OPENGL_ES_1_1        
   return 1;
#else
   return 2;
#endif
 }


 void AuraQCARController::setDisplayOrientation(bool isPortrait){
   mPortraitOrientation = isPortrait;
 }

 void AuraQCARController::renderFrame(){
   // Clear color and depth buffer 
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   QCAR::State state = QCAR::Renderer::getInstance().begin();
   QCAR::Renderer::getInstance().drawVideoBackground();
   QCAR::Renderer::getInstance().end();
 }


 void AuraQCARController::configureVideoBackground()
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
   
   if (mPortraitOrientation)
     {
       config.mSize.data[0] = videoMode.mHeight
	 * (mScreenHeight / (float)videoMode.mWidth);
       config.mSize.data[1] = mScreenHeight;

       if(config.mSize.data[0] < mScreenWidth)
	 {
	   config.mSize.data[0] = mScreenWidth;
	   config.mSize.data[1] = mScreenWidth * 
	     (videoMode.mWidth / (float)videoMode.mHeight);
	 }

     }
   else
     {
       config.mSize.data[0] = mScreenWidth;
       config.mSize.data[1] = videoMode.mHeight
	 * (mScreenWidth / (float)videoMode.mWidth);

       if(config.mSize.data[1] < mScreenHeight)
	 {
	   config.mSize.data[0] = mScreenHeight
	     * (videoMode.mWidth / (float)videoMode.mHeight);
	   config.mSize.data[1] = mScreenHeight;
	 }
     }


   // Set the config:
   QCAR::Renderer::getInstance().setVideoBackgroundConfig(config);
}


 void AuraQCARController::initApplicationNative(int width, int height){
   mScreenWidth = width;
   mScreenHeight = height;
}


 void AuraQCARController::startCamera(){
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


 void AuraQCARController::stopCamera(){
   QCAR::CameraDevice::getInstance().stop();
   QCAR::CameraDevice::getInstance().deinit();
 }


void AuraQCARController::setProjectionMatrix(){
   // Cache the projection matrix:
   const QCAR::CameraCalibration& cameraCalibration =
     QCAR::CameraDevice::getInstance().getCameraCalibration();
   projectionMatrix = QCAR::Tool::getProjectionGL(cameraCalibration, 2.0f, 2500.0f);
 }
 
 
 void AuraQCARController::initRendering(){
   // Define clear color
   glClearColor(0.0f, 0.0f, 0.0f, QCAR::requiresAlpha() ? 0.0f : 1.0f);
 }
 

 void AuraQCARController::updateRendering(int width, int height){
   // Update screen dimensions
   mScreenWidth = width;
   mScreenHeight = height;
   
   // Reconfigure the video background
   configureVideoBackground();
 }

