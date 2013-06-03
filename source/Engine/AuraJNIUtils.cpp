#include "AuraJNIUtils.h"

namespace Aura{

  void AuraJNIUtils::setVM(JavaVM* vm){
    mVm = vm;
  }

  void AuraJNIUtils::setState(struct android_app* state){
    mState = state;
  }

  void AuraJNIUtils::setAuraApp(AuraApplication* app){
    mApp = app;
  }

  struct android_app* AuraJNIUtils::getState(){
    return mState;
  }

  void AuraJNIUtils::getEnv(JNIEnv** env){ 
    mVm->GetEnv((void**)env, JNI_VERSION_1_6);
  }

  JavaVM* AuraJNIUtils::getVM(){ 
    return mVm; 
  }

  AuraApplication* AuraJNIUtils::getAuraApp(){
    return mApp;
  }

  void AuraJNIUtils::attachCurrentThread(JNIEnv* env){
    mVm->AttachCurrentThread(&env, NULL);
  }

  void AuraJNIUtils::detachCurrentThread(){
    mVm->DetachCurrentThread();
  }


}

