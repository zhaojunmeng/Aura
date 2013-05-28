#include "AuraQCARController.h"

namespace Aura {

  AuraQCARController::AuraQCARController() :
    mScreenWidth(0), mScreenHeight(0), mPortraitOrientation(false) {
  }

  AuraQCARController::~AuraQCARController() {
  }

  void AuraQCARController::startCamera(){

    // Select the camera to open, set this to QCAR::CameraDevice::CAMERA_FRONT
    // to activate the front camera instead.
    QCAR::CameraDevice::CAMERA camera = QCAR::CameraDevice::CAMERA_DEFAULT;

    // Initialize the camera:
    if (!QCAR::CameraDevice::getInstance().init(camera)) {
      LOGI("Cant init camera!");
      return;
    }

    // Configure the video background
    Aura::AuraQCARController::getInstance()->configureVideoBackground();

    // Select the default mode:
    if (!QCAR::CameraDevice::getInstance().selectVideoMode(
							   QCAR::CameraDevice::MODE_DEFAULT)) {
      LOGI("Cant set video mode!");
      return;
    }

    // Set image format
    if (!QCAR::setFrameFormat(QCAR::RGB888, true)) {
      LOGI("ERROR setting camera format");
      return;
    }

    // Start the camera:
    if (!QCAR::CameraDevice::getInstance().start()) {
      LOGI("Cant start camera");
      return;
    }

    Aura::AuraQCARController::getInstance()->setProjectionMatrix();

    QCAR::TrackerManager& trackerManager = QCAR::TrackerManager::getInstance();
    QCAR::Tracker* imageTracker = trackerManager.getTracker(QCAR::Tracker::IMAGE_TRACKER);
    if(imageTracker != 0)
      imageTracker->start();
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
    /* Begin - end */
    QCAR::State QCARState = QCAR::Renderer::getInstance().begin();

    // Retrieve a frame
    QCAR::Renderer::getInstance().drawVideoBackground();
    mFrame = QCARState.getFrame();

    // Inspect the trackables
    for(size_t tr = 0; tr < QCARState.getNumTrackableResults(); tr++){
      LOGI("Result found!");
      const QCAR::TrackableResult* result = QCARState.getTrackableResult(tr);
      const QCAR::Trackable& trackable = result->getTrackable();

      QCAR::Matrix44F pose = QCAR::Tool::convertPose2GLMatrix(result->getPose());
      
      Ogre::Matrix4 matPose(pose.data[0], pose.data[4], pose.data[8], pose.data[12], 
			    -pose.data[1], -pose.data[5], -pose.data[9], -pose.data[13],
			    -pose.data[2], -pose.data[6], -pose.data[10], -pose.data[14],
			    pose.data[3], pose.data[7], pose.data[11], pose.data[15]);

      Ogre::SceneNode* node = Ogre::Root::getSingleton().getSceneManager("SceneManager")->getSceneNode("sinbad");
      node->setOrientation(matPose.extractQuaternion());
      node->setPosition(matPose.getTrans());
      

    }

    QCAR::Renderer::getInstance().end();


  }

  void AuraQCARController::configureVideoBackground() {
    // Get the default video mode:
    QCAR::CameraDevice& cameraDevice = QCAR::CameraDevice::getInstance();
    QCAR::VideoMode videoMode = cameraDevice.getVideoMode(
							  QCAR::CameraDevice::MODE_DEFAULT);

    // Configure the video background
    QCAR::VideoBackgroundConfig config;
    config.mEnabled = false;
    config.mSynchronous = true;
    config.mPosition.data[0] = 0.0f;
    config.mPosition.data[1] = 0.0f;

    if (mPortraitOrientation) {
      config.mSize.data[0] = videoMode.mHeight
	* (mScreenHeight / (float) videoMode.mWidth);
      config.mSize.data[1] = mScreenHeight;

      if (config.mSize.data[0] < mScreenWidth) {
	config.mSize.data[0] = mScreenWidth;
	config.mSize.data[1] = mScreenWidth
	  * (videoMode.mWidth / (float) videoMode.mHeight);
      }

    } else {
      config.mSize.data[0] = mScreenWidth;
      config.mSize.data[1] = videoMode.mHeight
	* (mScreenWidth / (float) videoMode.mWidth);

      if (config.mSize.data[1] < mScreenHeight) {
	config.mSize.data[0] = mScreenHeight
	  * (videoMode.mWidth / (float) videoMode.mHeight);
	config.mSize.data[1] = mScreenHeight;
      }
    }

    // Set the config:
    QCAR::Renderer::getInstance().setVideoBackgroundConfig(config);
  }




  void AuraQCARController::loadImageData(const std::string& name, const std::string& filename){

    LOGI("Loading an image");
    QCAR::ImageTracker* imTracker = static_cast<QCAR::ImageTracker*>(QCAR::TrackerManager::getInstance().initTracker(QCAR::Tracker::IMAGE_TRACKER));
    //QCAR::ImageTracker* imTracker = static_cast<QCAR::ImageTracker*>(QCAR::TrackerManager::getInstance().getTracker(QCAR::Tracker::IMAGE_TRACKER));
        
    QCAR::DataSet* dataset = imTracker->createDataSet();

    if(dataset == 0){
      LOGI("Error creating a new dataset");
      return;
    }

    if(!dataset->load(filename.c_str(), QCAR::DataSet::STORAGE_APPRESOURCE)){
      LOGI("Error loading the image data");
      return;
    }

    if(!imTracker->activateDataSet(dataset)){
      LOGI("Error activating the data set");
      return;
    }

    LOGI("Adding the dataset");

    mDataSets.push_back(dataset);
    //mDataSets.insert(std::pair<std::string,QCAR::DataSet*>(name, dataset));

  }

  void AuraQCARController::createImageSceneNodes(){
    LOGI("Creating scene nodes for the images :)");
    QCAR::DataSet* dataset;
    for(unsigned int i=0; i < mDataSets.size(); i++){
      LOGI("One dataset");
      dataset = mDataSets.at(i);

      for(size_t tr=0; tr<dataset->getNumTrackables(); tr++){
	LOGI("One trackable");
	QCAR::Trackable* trackable = dataset->getTrackable(tr);
	Ogre::Root::getSingleton().getSceneManager("SceneManager")->getRootSceneNode()->createChildSceneNode(trackable->getName());
	LOGI("Creating AR Scene Node: ");
	LOGI(trackable->getName());
      }
    }
  }

  //  QCAR::DataSet* AuraQCARController::getDataSet(const std::string& name){
  //  return mDataSets.atname];
  //}

  QCAR::Frame& AuraQCARController::getFrame() {
    return mFrame;
  }

  void AuraQCARController::stopCamera() {
    QCAR::CameraDevice::getInstance().stop();
    QCAR::CameraDevice::getInstance().deinit();
  }

  void AuraQCARController::setProjectionMatrix() {
    // Cache the projection matrix:
    const QCAR::CameraCalibration& cameraCalibration =
      QCAR::CameraDevice::getInstance().getCameraCalibration();
    projectionMatrix = QCAR::Tool::getProjectionGL(cameraCalibration, 2.0f,
						   2500.0f);
  }

}

