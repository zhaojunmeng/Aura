#include "AuraApplication.h"

namespace Aura {

#if OGRE_PLATFORM == OGRE_PLATFORM_ANDROID
  AuraApplication::AuraApplication() {
    mEngine = new AuraEngineAndroid();
     _setup();
  }
#else
  AuraApplication::AuraApplication() {
    mEngine = new AuraEngine();
     _setup();
  }
#endif

  void AuraApplication::go() {
    // Init the Engine
    mEngine->init();

    // Right before calling the custom create scene
    _setupAuraInterface();

    // Create the nodes for the AR :(
    mQCARController->createImageSceneNodes();

    // Create the scene
    createScene();

    // Run the loop! (Just the loop)
    while (mRunning) {

      if (!mEngine->auraFrameStarted())
	break;

      // Draw the frame
      mQCARController->update();

      QCAR::Frame frame = mQCARController->getFrame();

      // Update trackable positions
      if (!mEngine->auraRenderOneFrame())
	break;

      mEngine->auraFrameEnded();
    }

    // Shutting down :)
    mEngine->shutdown();

  }

  void AuraApplication::_setupAuraInterface(){
    // Retrieve the main objects
    mRoot = mEngine->mRoot;
    mSceneManager = mEngine->mSceneManager;
    mCamera = mEngine->mCamera;
    mWindow = mEngine->mWindow;
    mQCARController = AuraQCARController::getInstance();    
  }

  void AuraApplication::finish() {
    mRunning = false;
  }

  void AuraApplication::_setup() {

    mRunning = true;
  }

}

/* Lets put here the interface with the Java VM */
extern "C" {
  JNIEXPORT void JNICALL
  Java_com_cesardev_aura_Aura_initQCARNative(JNIEnv*, jobject, int width, int height) {
    Aura::AuraQCARController::getInstance()->setScreenWidth(width);
    Aura::AuraQCARController::getInstance()->setScreenHeight(height);
    Aura::AuraJNIUtils::getInstance()->getAuraApp()->initTracker();
    Aura::AuraQCARController::getInstance()->startCamera();
  }

} // extern "C"

