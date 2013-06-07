#ifndef _AuraJNIUtils_H_
#define _AuraJNIUtils_H_

#include <jni.h>
#include <android_native_app_glue.h>
#include <AuraLog.h>
#include "Singleton.h"

namespace Aura{

  class AuraApplication;

  class AuraJNIUtils: public Singleton<AuraJNIUtils>{
    
  public:
    // High-level Engine functions
    void finishActivity();
    //void initResourcesJava();

    // Getters and setters
    void setVM(JavaVM* vm);
    void setState(struct android_app* state);

    struct android_app* getState();
    JNIEnv* getEnv();
    JavaVM* getVM();

    void attachCurrentThread();
    void detachCurrentThread();
    
  private:
    JavaVM* mVm;
    JNIEnv* mEnv;
    struct android_app* mState;
    AuraApplication* mApp;
  };

}
#endif //_AuraJNIUtils_H_
