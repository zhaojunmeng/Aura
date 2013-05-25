#include "AuraApplication.h"

namespace Aura{

#if OGRE_PLATFORM == OGRE_PLATFORM_ANDROID
  AuraApplication::AuraApplication(struct android_app* state, bool nograb): mState(state){
    mIOEngine = new AuraIOEngineAndroid(nograb); // Closely related to Android Ogre Engine
    mEngine = new AuraEngineAndroid(state, static_cast<AuraIOEngineAndroid*>(mIOEngine));
    _setup();
  }
#else
  AuraApplication::AuraApplication(bool nograb){
    mEngine = new AuraEngine();
    mIOEngine = new AuraIOEngine(nograb);
    _setup();
  }
#endif

  void AuraApplication::go(){
    // Init the Engine
    mEngine->init();
    
    // Retrieve the main objects
    mRoot = mEngine->mRoot;
    mSceneManager = mEngine->mSceneManager;
    mCamera = mEngine->mCamera;
    mWindow = mEngine->mWindow;
    
    // Init the IO
    mIOEngine->setupInput(mWindow);
    
    // Create the scene
     createScene();
    
    // Run the loop! (Just the loop)
    while (mRunning)
      {

	// Get the frame
	LOGI("----- Starting frame ------");
	QCAR::Frame frame = mQCARController->getFrame();

	char str[100];
	sprintf(str,"Timestamp %d",frame.getTimeStamp());
	LOGI(str);
	LOGI("Number of images and their format:");
	sprintf(str,"N images: %d",frame.getNumImages());
	LOGI(str);
	for(int i=0; i<frame.getNumImages();i++){
	  sprintf(str,"format: %d", frame.getImage(i)->getFormat());
	  LOGI(str);

	}

	mIOEngine->capture();
	if(!mEngine->auraFrameStarted()) break;
	
	mEngine->drawBackground(frame);

	if(!mEngine->auraRenderOneFrame()) break;
	
	mEngine->auraFrameEnded();
      }
    
    // Shutting down :)
    mEngine->shutdown();
    
  }
  
  void AuraApplication::finish(){
    mRunning = false;
  }


  void AuraApplication::_setup(){
    mQCARController = AuraQCARController::getInstance();
    mRunning = true;
  }

}


