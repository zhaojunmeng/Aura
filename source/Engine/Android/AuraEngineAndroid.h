#ifndef _AURAOGREENGINEANDROID_H_
#define _AURAOGREENGINEANDROID_H_

#include <android_native_app_glue.h>
#include <EGL/egl.h>

#include "OgrePlatform.h"
#include "Android/OgreAndroidEGLWindow.h"
#include "Android/OgreAPKFileSystemArchive.h"
#include "Android/OgreAPKZipArchive.h"
#include "AuraEngine.h"
#include "AuraIOEngineAndroid.h"
#include "AuraApplication.h"
#include "AuraJNIUtils.h"

namespace Aura{

  class AuraEngineAndroid:  public AuraEngine
  {
  public:

    AuraEngineAndroid(struct android_app* state);
      
    virtual void init();
    void start(AuraApplication* app);

    virtual void createWindow();
    virtual void setupInput();
    virtual void loadConfigFile(Ogre::ConfigFile& cf);
    Ogre::DataStreamPtr openAPKFile(const Ogre::String& fileName);
    static int32_t handleInput(struct android_app* app, AInputEvent* event); 
    static void handleCmd(struct android_app* app, int32_t cmd);

    static AuraEngineAndroid* mInstance;
    struct android_app* mState;
    AAssetManager* mAssetMgr;       // Android asset manager to access files inside apk

    // To get the events
    int ident, events;
    struct android_poll_source* source;
  };

} // Aura

#endif //_AURAOGREENGINEANDROID_H_
