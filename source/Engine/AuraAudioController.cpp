#include "AuraAudioController.h"

namespace Aura{

  AuraAudioController::AuraAudioController(){
  }

  void AuraAudioController::initialize(){
    // Android initialization
#if OGRE_PLATFORM == OGRE_PLATFORM_ANDROID
    CkConfig config(AuraJNIUtils::getInstance()->getEnv(), AuraJNIUtils::getInstance()->getState()->activity->clazz);
#else 
    CkConfig config;

#endif
    CkInit(&config);
  }

  void AuraAudioController::loadAudioFile(std::string& file){

  }

  void AuraAudioController::play(std::string& sound){

  }

  void AuraAudioController::pause(){
    CkSuspend();
  }

  void AuraAudioController::resume(){
    CkResume();
  }

  void AuraAudioController::update(){
    CkUpdate();
  }

  void AuraAudioController::shutdown(){
    CkShutdown();
  }
  
  AuraAudioController::~AuraAudioController(){
  }

} // Aura
