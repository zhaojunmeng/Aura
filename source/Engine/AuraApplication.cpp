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

    LOGI("Creating scene noces and stuff");
    // Right before calling the custom create scene
    _setupAuraInterface();

    // Create the nodes for the AR (after initializing Ogre)
    mQCARController->createImageSceneNodes();

    // Create the scene
    createScene();

    // Run the loop! (Just the loop)
    while (mRunning) {
      // This guy controls the exit :)
      mEngine->auraFrameStarted();

      // Draw the frame and update scene nodes
      mQCARController->update();

      // Update trackable positions
      mEngine->auraRenderOneFrame();

      mEngine->auraFrameEnded();
    }


    mEngine->finish();

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

  JNIEXPORT bool JNICALL
  Java_com_cesardev_aura_Aura_initQCARNative(JNIEnv*, jobject, int width, int height) {
    Aura::AuraQCARController::getInstance()->setScreenWidth(width);
    Aura::AuraQCARController::getInstance()->setScreenHeight(height);

    if(Aura::AuraJNIUtils::getInstance()->getAuraApp()){
      QCAR::registerCallback(Aura::AuraJNIUtils::getInstance()->getAuraApp());
      Aura::AuraJNIUtils::getInstance()->getAuraApp()->initTracker();
      if(!Aura::AuraQCARController::getInstance()->startCamera()) return false;
      return true;
    }
    return false;
  }

} // extern "C"

