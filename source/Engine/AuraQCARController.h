#ifndef _AuraQCARController_H_
#define _AuraQCARController_H_

#include "Ogre.h"

#include "AuraLog.h"
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
#include <QCAR/UpdateCallback.h>
#include <QCAR/Tracker.h>
#include <QCAR/ImageTracker.h>
#include <QCAR/Trackable.h>
#include <QCAR/TrackableResult.h>
#include <QCAR/TrackerManager.h>
#include <QCAR/DataSet.h>

namespace Aura{

  class AuraQCARController: public Singleton<AuraQCARController>{//, public QCAR::UpdateCallback{

  public:  
    AuraQCARController();
    ~AuraQCARController();

    void update();

    // Image targets loader
    void loadImageData(const std::string& name, const std::string& filename);
    void createImageSceneNodes();

    //    virtual void QCAR_onUpdate(QCAR::State& state);

    void setScreenWidth(int screenWidth){ mScreenWidth = screenWidth; }
    void setScreenHeight(int screenHeight){ mScreenHeight = screenHeight; }

    int getScreenWidth(){ return mScreenWidth; }
    int getScreenHeight(){ return mScreenHeight; }

    void startTracker();
    
    const QCAR::VideoBackgroundConfig& getVideoBackgroundConfig(){ return mVideoBackgroundConfig; }
    const QCAR::VideoMode& getVideoMode(){ return mVideoMode; }
    QCAR::Matrix44F getProjectionMatrix() { return mProjectionMatrix; }
    QCAR::Frame& getFrame();
    int getOpenGlVersion();
    

    void setProjectionMatrix();
    void configureVideoBackground();

    void stopCamera();
    bool startCamera();

    void shutdown();
    
  private:
    QCAR::Frame mFrame;
    Ogre::SceneNode* mQCARNode;
    //QCAR::ImageTracker* mImageTracker;
    unsigned int mScreenWidth;
    unsigned int mScreenHeight;
    bool mPortraitOrientation;
    QCAR::Matrix44F mProjectionMatrix;
    QCAR::VideoBackgroundConfig mVideoBackgroundConfig;
    QCAR::VideoMode mVideoMode;
  };

}
#endif // _AuraQCARController_H_
