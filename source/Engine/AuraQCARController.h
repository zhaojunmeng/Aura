#ifndef _AuraQCARController_H_
#define _AuraQCARController_H_

#include "Ogre.h"
#include <jni.h>
#include <android/log.h>
#include <android/native_activity.h>
#include <android_native_app_glue.h>
#include <vector>

#include "AuraJNIUtils.h"
#include "Singleton.h"

#ifdef USE_OPENGL_ES_1_1
#include <GLES/gl.h>
#include <GLES/glext.h>
#else
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#endif

#include <QCAR/QCAR.h>
#include <QCAR/CameraDevice.h>
#include <QCAR/Renderer.h>
#include <QCAR/VideoBackgroundConfig.h>
#include <QCAR/Tool.h>
#include <QCAR/CameraCalibration.h>
#include <QCAR/Frame.h>
#include <QCAR/Image.h>
#include <QCAR/Tracker.h>
#include <QCAR/ImageTracker.h>
#include <QCAR/Trackable.h>
#include <QCAR/TrackableResult.h>
#include <QCAR/TrackerManager.h>
#include <QCAR/DataSet.h>


#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, "Ogre", __VA_ARGS__))
#define LOGW(...) ((void)__android_log_print(ANDROID_LOG_WARN, "Ogre", __VA_ARGS__))


namespace Aura{

  class AuraQCARController: public Singleton<AuraQCARController>{

  public:  
    AuraQCARController();
    ~AuraQCARController();
  
    QCAR::Frame& getFrame();

    void update();

    void loadImageData(const std::string& name, const std::string& filename);
    void createImageSceneNodes();

    //QCAR::DataSet* getDataSet(const std::string& name);

    void setScreenWidth(int screenWidth){ mScreenWidth = screenWidth; }
    void setScreenHeight(int screenHeight){ mScreenHeight = screenHeight; }
    void configureVideoBackground();

    int getScreenWidth(){ return mScreenWidth; }
    int getScreenHeight(){ return mScreenHeight; }

    void setProjectionMatrix();

    void stopCamera();
    void startCamera();
    int getOpenGlVersion();

    
  private:
    std::vector<QCAR::DataSet*> mDataSets;

    QCAR::Frame mFrame;

    QCAR::Tracker::TYPE mTrackerType;
    unsigned int mScreenWidth;
    unsigned int mScreenHeight;
    bool mPortraitOrientation;
    QCAR::Matrix44F projectionMatrix;

  };

}
#endif // _AuraQCARController_H_
