#ifndef _AuraJNIUtils_H_
#define _AuraJNIUtils_H_

#include <jni.h>
#include <android_native_app_glue.h>
#include "Singleton.h"

namespace Aura{

  class AuraApplication;

  class AuraJNIUtils: public Singleton<AuraJNIUtils>{
    
  public:

    void setVM(JavaVM* vm);
    void setState(struct android_app* state);
    void setAuraApp(AuraApplication* app);

    struct android_app* getState();
    void getEnv(JNIEnv** env);
    JavaVM* getVM();
    AuraApplication* getAuraApp();

    void attachCurrentThread(JNIEnv* env);
    void detachCurrentThread();
    
  private:
    JavaVM* mVm;
    struct android_app* mState;
    AuraApplication* mApp;
  };

}
#endif //_AuraJNIUtils_H_
