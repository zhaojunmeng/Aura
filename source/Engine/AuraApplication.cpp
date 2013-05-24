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
    mQCARController->init();
        
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
	
	mIOEngine->capture();
	if(!mEngine->auraFrameStarted()) break;
	
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
    mQCARController = new AuraQCARController();
    mRunning = true;
  }

}


