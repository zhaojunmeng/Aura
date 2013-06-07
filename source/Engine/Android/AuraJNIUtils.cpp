#include "AuraJNIUtils.h"

namespace Aura{

  void AuraJNIUtils::finishActivity(){
    ANativeActivity_finish(AuraJNIUtils::getInstance()->getState()->activity);
  }

  // void AuraJNIUtils::initResourcesJava(){
  //   AuraLog::info("Calling in JNI utils to init resources java");
  //   JNIEnv* env;    
  //   attachCurrentThread(&env);
  //   jclass clazz = env->GetObjectClass(mState->activity->clazz);
  //   jmethodID initResourcesJavaID = env->GetMethodID(clazz, "initResourcesJava", "()V");
  //   env->CallObjectMethod(mState->activity->clazz, initResourcesJavaID);
  //   detachCurrentThread();
  // }

  void AuraJNIUtils::setState(struct android_app* state){
    mState = state;
  }

  void AuraJNIUtils::setVM(JavaVM* vm){
    mVm = vm;
  }

  struct android_app* AuraJNIUtils::getState(){
    return mState;
  }

  JNIEnv* AuraJNIUtils::getEnv(){ 
    return mEnv;
    //mVm->GetEnv((void**)env, JNI_VERSION_1_6);
  }

  JavaVM* AuraJNIUtils::getVM(){ 
    return mVm; 
  }

  void AuraJNIUtils::attachCurrentThread(){
    mVm->AttachCurrentThread(&mEnv, NULL);
  }

  void AuraJNIUtils::detachCurrentThread(){
    mVm->DetachCurrentThread();
  }


}


