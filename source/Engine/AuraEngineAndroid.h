#ifndef _AURAOGREENGINEANDROID_H_
#define _AURAOGREENGINEANDROID_H_

#include <android_native_app_glue.h>
#include <android/log.h>
#include <EGL/egl.h>

#include "OgrePlatform.h"
#include "Android/OgreAndroidEGLWindow.h"
#include "Android/OgreAPKFileSystemArchive.h"
#include "Android/OgreAPKZipArchive.h"
#include "AuraEngine.h"
#include "AuraIOEngineAndroid.h"
#include "AuraApplication.h"
#include "AuraJNIUtils.h"

#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, "Ogre", __VA_ARGS__))
#define LOGW(...) ((void)__android_log_print(ANDROID_LOG_WARN, "Ogre", __VA_ARGS__))


namespace Aura{

  class AuraEngineAndroid:  public AuraEngine
  {
  public:

    AuraEngineAndroid();
      
    virtual void init();
    virtual void shutdown();
    static int32_t handleInput(struct android_app* app, AInputEvent* event); 
    static void handleCmd(struct android_app* app, int32_t cmd);
    virtual bool auraFrameStarted();
    virtual bool auraRenderOneFrame();
    void setupAndroid();
    virtual void loadConfigFile(Ogre::ConfigFile& cf);
    Ogre::DataStreamPtr openAPKFile(const Ogre::String& fileName);

    virtual void finish();

  private:
    static AuraEngineAndroid* mInstance;
    struct android_app* mState;
    AAssetManager* mAssetMgr;       // Android asset manager to access files inside apk
    bool mInit;
  };

} // Aura

#endif //_AURAOGREENGINEANDROID_H_
