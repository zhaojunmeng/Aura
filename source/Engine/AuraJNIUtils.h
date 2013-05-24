#ifndef _AuraJNIUtils_H_
#define _AuraJNIUtils_H_

#include <jni.h>
#include <android_native_app_glue.h>
#include "Singleton.h"

namespace Aura{

  class AuraJNIUtils: public Singleton<AuraJNIUtils>{
    
  public:

    // In the future, this could be a generic funtion!
    // We pass the name of the class, and store it in a map
    void loadAndCacheQCARClass();

    void setVM(JavaVM* vm);
    void setState(struct android_app* state);

    struct android_app* getState();
    void getEnv(JNIEnv** env);
    JavaVM* getVM();
    jclass getQCARClass();

    void attachCurrentThread(JNIEnv* env);
    void detachCurrentThread();
    
  private:
    JavaVM* mVm;
    struct android_app* mState;
    jclass mQCARClass;
  };

}
#endif //_AuraJNIUtils_H_
