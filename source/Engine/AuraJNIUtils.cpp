#include "AuraJNIUtils.h"

namespace Aura{

  void AuraJNIUtils::loadAndCacheQCARClass(){
    JNIEnv* env;
    getEnv(&env);
    jclass QCARClass_local = env->FindClass("com/qualcomm/QCAR/QCAR");  
    mQCARClass = reinterpret_cast<jclass>(env->NewGlobalRef(QCARClass_local));
  }

  void AuraJNIUtils::setVM(JavaVM* vm){
    mVm = vm;
  }

  void AuraJNIUtils::setState(struct android_app* state){
    mState = state;
  }
  struct android_app* AuraJNIUtils::getState(){
    return mState;
  }

  void AuraJNIUtils::getEnv(JNIEnv** env){ 
    mVm->GetEnv((void**)env, JNI_VERSION_1_6);
  }
  JavaVM* AuraJNIUtils::getVM(){ return mVm; }
  jclass AuraJNIUtils::getQCARClass(){ return mQCARClass; }

  void AuraJNIUtils::attachCurrentThread(JNIEnv* env){
    mVm->AttachCurrentThread(&env, NULL);
  }

  void AuraJNIUtils::detachCurrentThread(){
    mVm->DetachCurrentThread();
  }


}
