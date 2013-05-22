#include "AuraApplication.h"

namespace Aura{

#if OGRE_PLATFORM == OGRE_PLATFORM_ANDROID
  AuraApplication::AuraApplication(struct android_app* state, bool nograb){
    mIOEngine = new AuraIOEngineAndroid(nograb); // Closely related to Android Ogre Engine
    mOgreEngine = new AuraOgreEngineAndroid(state, static_cast<AuraIOEngineAndroid*>(mIOEngine));
    mRunning = true;
  }
#else
  AuraApplication::AuraApplication(bool nograb){
    mOgreEngine = new AuraOgreEngine();
    mIOEngine = new AuraIOEngine(nograb);
    mRunning = true;
  }
#endif


  void AuraApplication::go(){
      
    // Init the Engine
    mOgreEngine->init();

    // Retrieve the main objects
    mRoot = mOgreEngine->mRoot;
    mSceneManager = mOgreEngine->mSceneManager;
    mCamera = mOgreEngine->mCamera;
    mWindow = mOgreEngine->mWindow;

    // Init the IO
    mIOEngine->setupInput(mWindow);
            
    // Create the scene
    setupApp();

    // Run the loop! (Just the loop)
    while (mRunning)
      {

	mIOEngine->capture();
	if(!mOgreEngine->auraFrameStarted()) break;
	  
	if(!mOgreEngine->auraRenderOneFrame()) break;
	  
	mOgreEngine->auraFrameEnded();
      }
      

    // Shutting down :)
    mOgreEngine->shutdown();
      
  }

  void AuraApplication::finish(){
    mRunning = false;
  }

}


