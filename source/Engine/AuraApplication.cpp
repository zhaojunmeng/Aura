#include "AuraApplication.h"

namespace Aura {

  AuraApplication::AuraApplication() {
  }

  void AuraApplication::setupAuraInterface(){
    // Retrieve the main objects
    mRoot = &Ogre::Root::getSingleton();
    mSceneManager = mRoot->getSceneManager("SceneManager");
    mQCARController = AuraQCARController::getInstance();    
  }
}


