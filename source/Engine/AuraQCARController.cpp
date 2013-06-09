#include "AuraQCARController.h"

namespace Aura {

  AuraQCARController::AuraQCARController() :
    mScreenWidth(0), mScreenHeight(0), mPortraitOrientation(false) {
  }

  AuraQCARController::~AuraQCARController() {
  }

#if OGRE_PLATFORM == OGRE_PLATFORM_APPLE_IOS
  void AuraQCARController::initQCAR_iOS(){
    // :)
    // Init QCAR
    QCAR::setInitParameters(getOpenGlVersion());
    int retval = QCAR::init();
    if(retval < -1){
      AuraLog::error("Error initializing QCAR");
    }

    // Store screen dimensions
    // Engine IOS does it!
    //setScreenWidth([[UIScreen mainScreen] bounds].size.width);
    //setScreenHeight([[UIScreen mainScreen] bounds].size.height);
    
    // Init tracker
    //myApp->initTracker();
    
    // Start camera
    startCamera();

  }
#endif


  bool AuraQCARController::startCamera(){
    // Select the camera to open, set this to QCAR::CameraDevice::CAMERA_FRONT
    // to activate the front camera instead.
    QCAR::CameraDevice::CAMERA camera = QCAR::CameraDevice::CAMERA_DEFAULT;

    // Initialize the camera:
    if (!QCAR::CameraDevice::getInstance().init(camera)) {
      AuraLog::error("Cant init camera!");
      return false;
    }

    // Configure the video background
    Aura::AuraQCARController::getInstance()->configureVideoBackground();

    // Select the default mode:
    if (!QCAR::CameraDevice::getInstance().selectVideoMode(QCAR::CameraDevice::MODE_DEFAULT)) {
      AuraLog::error("Cant set video mode!");
      return false;
    }

    // Set image format
    if (!QCAR::setFrameFormat(QCAR::RGB888, true)) {
      AuraLog::error("ERROR setting camera format");
      return false;
    }

    // Start the camera:
    if (!QCAR::CameraDevice::getInstance().start()) {
      AuraLog::error("Cant start camera");
      return false;
    }

    Aura::AuraQCARController::getInstance()->setProjectionMatrix();

    return true;
  }

  void AuraQCARController::startTracker(){
    QCAR::TrackerManager& trackerManager = QCAR::TrackerManager::getInstance();
    QCAR::Tracker* imageTracker = trackerManager.getTracker(QCAR::Tracker::IMAGE_TRACKER);
    if(imageTracker != 0){
      imageTracker->start();
    }else{
      AuraLog::error("Error starting the tracker!");
    }
  }

  int AuraQCARController::getOpenGlVersion(){
#ifdef USE_OPENGL_ES_1_1
    return 1;
#else 
#ifdef USE_OPENGL_ES_2_0
    return 2;
#else
#error "Error choosing the OpenGL Version, constant not well defined?"
#endif
#endif
  }

  void AuraQCARController::update(){
    // Retrieve a frame
    QCAR::State state = QCAR::Renderer::getInstance().begin();	  
    mFrame = state.getFrame();
    QCAR::Renderer::getInstance().end();

    //mQCARNode->setVisible(false);
    mQCARNode->setVisible(true);

    // Inspect the trackables
    for(size_t tr = 0; tr < state.getNumTrackableResults(); tr++){
      const QCAR::TrackableResult* result = state.getTrackableResult(tr);
      const QCAR::Trackable& trackable = result->getTrackable();

      Ogre::SceneNode* node = Ogre::Root::getSingleton().getSceneManager("SceneManager")->getSceneNode(trackable.getName());
      
      QCAR::Matrix44F pose = QCAR::Tool::convertPose2GLMatrix(result->getPose());
      Ogre::Matrix3 rotMat( pose.data[0], pose.data[4], pose.data[8],
			    pose.data[1], pose.data[5], pose.data[9],
			    pose.data[2], pose.data[6], pose.data[10]);

      node->setOrientation(Ogre::Quaternion(rotMat));
      node->setPosition(Ogre::Vector3(pose.data[12], pose.data[13], pose.data[14]));
      node->setVisible(true);
    }
  }

  void AuraQCARController::configureVideoBackground() {
    // Get the default video mode:
    QCAR::CameraDevice& cameraDevice = QCAR::CameraDevice::getInstance();
    mVideoMode = cameraDevice.getVideoMode(QCAR::CameraDevice::MODE_DEFAULT);

    // Configure the video background    
    mVideoBackgroundConfig.mEnabled = false;
    mVideoBackgroundConfig.mSynchronous = true;
    mVideoBackgroundConfig.mPosition.data[0] = 0.0f;
    mVideoBackgroundConfig.mPosition.data[1] = 0.0f;

    if (mPortraitOrientation) {
      mVideoBackgroundConfig.mSize.data[0] = mVideoMode.mHeight	* (mScreenHeight / (float) mVideoMode.mWidth);
      mVideoBackgroundConfig.mSize.data[1] = mScreenHeight;

      if (mVideoBackgroundConfig.mSize.data[0] < mScreenWidth) {
	mVideoBackgroundConfig.mSize.data[0] = mScreenWidth;
	mVideoBackgroundConfig.mSize.data[1] = mScreenWidth  * (mVideoMode.mWidth / (float) mVideoMode.mHeight);
      }

    } else {
      mVideoBackgroundConfig.mSize.data[0] = mScreenWidth;
      mVideoBackgroundConfig.mSize.data[1] = mVideoMode.mHeight * (mScreenWidth / (float) mVideoMode.mWidth);

      if (mVideoBackgroundConfig.mSize.data[1] < mScreenHeight) {
	mVideoBackgroundConfig.mSize.data[0] = mScreenHeight * (mVideoMode.mWidth / (float) mVideoMode.mHeight);
	mVideoBackgroundConfig.mSize.data[1] = mScreenHeight;
      }
    }

    // Set the mVideoBackgroundConfig:
    QCAR::Renderer::getInstance().setVideoBackgroundConfig(mVideoBackgroundConfig);
  }

  void AuraQCARController::loadImageData(const std::string& name, const std::string& filename){

    QCAR::ImageTracker* imTracker = reinterpret_cast<QCAR::ImageTracker*>(QCAR::TrackerManager::getInstance().initTracker(QCAR::Tracker::IMAGE_TRACKER));

    if(!imTracker){
      AuraLog::info("Could not initialize Image Tracker. Probably the camera is already running");
      QCAR::TrackerManager& trackerManager = QCAR::TrackerManager::getInstance();
      imTracker = reinterpret_cast<QCAR::ImageTracker*>(trackerManager.getTracker(QCAR::Tracker::IMAGE_TRACKER));
      if(imTracker != 0){

      }else{
	AuraLog::error("Error getting the tracker to load de data!");
	return;
      }
    }

    QCAR::DataSet* dataset = imTracker->createDataSet();

    if(dataset == 0){
      AuraLog::error("Error creating a new dataset");
      return;
    }

    if(!dataset->load(filename.c_str(), QCAR::DataSet::STORAGE_APPRESOURCE)){
      AuraLog::error("Error loading the image data");
      return;
    }

    if(!imTracker->activateDataSet(dataset)){
      AuraLog::error("Error activating the data set");
      return;
    }

    
  }


  void AuraQCARController::createImageSceneNodes(){

    mQCARNode = Ogre::Root::getSingleton().getSceneManager("SceneManager")->getRootSceneNode()->createChildSceneNode("QCARNode");

    QCAR::ImageTracker* imTracker = static_cast<QCAR::ImageTracker*>(QCAR::TrackerManager::getInstance().getTracker(QCAR::Tracker::IMAGE_TRACKER));
    if(!imTracker){
      AuraLog::error("Error creating the image scene nodes");
      return;
    }

    for(int i = 0; i< imTracker->getActiveDataSetCount(); i++){

      QCAR::DataSet* dataset = imTracker->getActiveDataSet(i);
      if(!dataset){
	AuraLog::error("Error trying to get the dataset to create the scene nodes!");
	return;
      }

      for(int i=0; i < dataset->getNumTrackables(); i++){
	QCAR::Trackable* trackable = dataset->getTrackable(i);
	Ogre::SceneNode* node = mQCARNode->createChildSceneNode(trackable->getName());
      }
    }
  }

  void AuraQCARController::shutdown(){
    QCAR::ImageTracker* imTracker = static_cast<QCAR::ImageTracker*>(QCAR::TrackerManager::getInstance().getTracker(QCAR::Tracker::IMAGE_TRACKER));

    // Destroy tracker data
    if(imTracker){
      QCAR::DataSet* dataset = imTracker->getActiveDataSet();
      if(dataset && imTracker->deactivateDataSet(dataset)){
	imTracker->destroyDataSet(dataset);
      }else{
	AuraLog::error("Error while trying to destroy image dataset.");
      }

      // Deinit tracker
      if(!QCAR::TrackerManager::getInstance().deinitTracker(QCAR::Tracker::IMAGE_TRACKER)){
	AuraLog::error("Error deinitializing the image tracker");
      }
    }
  }
  
  QCAR::Frame& AuraQCARController::getFrame() {
    return mFrame;
  }

  void AuraQCARController::stopCamera() {

    // Stop the tracker:
    QCAR::TrackerManager& trackerManager = QCAR::TrackerManager::getInstance();
    QCAR::Tracker* imageTracker = trackerManager.getTracker(QCAR::Tracker::IMAGE_TRACKER);
    if(imageTracker != 0){
      imageTracker->stop();
    }else{
      AuraLog::error("Error stopping the image tracker.");
    }
    QCAR::CameraDevice::getInstance().stop();
    QCAR::CameraDevice::getInstance().deinit();
  }

  void AuraQCARController::setProjectionMatrix() {
    // Cache the projection matrix:
    const QCAR::CameraCalibration& cameraCalibration = QCAR::CameraDevice::getInstance().getCameraCalibration();
    mProjectionMatrix = QCAR::Tool::getProjectionGL(cameraCalibration, 2.0f, 2500.0f);
  }
}


