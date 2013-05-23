#include "AuraEngineAndroid.h"

namespace Aura{

  AuraEngineAndroid* AuraEngineAndroid::mInstance = NULL;

  AuraEngineAndroid::AuraEngineAndroid(struct android_app* state, AuraIOEngineAndroid* ioEngine): AuraEngine(), mState(state), mIOEngine(ioEngine){
      
    AuraEngineAndroid::mInstance = this;

    mState->onAppCmd = &Aura::AuraEngineAndroid::handleCmd;
    mState->onInputEvent = &Aura::AuraEngineAndroid::handleInput;
      
    mRoot = new Ogre::Root("");
    mStaticPluginLoader.load();
    mRoot->setRenderSystem(mRoot->getAvailableRenderers().at(0));
    mRoot->initialise(false);
    mOverlaySystem = OGRE_NEW Ogre::OverlaySystem();

    mInit = true;
    mWindow = 0;
  }
    
  void AuraEngineAndroid::init()
  {
    // Loop to wait until the window is created :)
    int ident, events;
    struct android_poll_source* source;
      
    while (!mWindow)
      {
	while ((ident = ALooper_pollAll(0, NULL, &events, (void**)&source)) >= 0)
	  {
	    if (source != NULL)
	      source->process(mState, source);
     
	    if (mState->destroyRequested != 0)
	      return;
	  }
      }
  }

  void AuraEngineAndroid::shutdown()
  {
    if(!mInit)
      return;
                
    mInit = false;
            
    OGRE_DELETE mRoot;
    mRoot = NULL;
    mWindow = NULL;
            
            
    mStaticPluginLoader.unload();

    Ogre::WindowEventUtilities::removeWindowEventListener(mWindow, this);

    ANativeActivity_finish(mState->activity);
  }

  int32_t AuraEngineAndroid::handleInput(struct android_app* app, AInputEvent* event){
    if (AuraEngineAndroid::mInstance->mIOEngine){
      if (AInputEvent_getType(event) == AINPUT_EVENT_TYPE_MOTION){
	int action = (int)(AMOTION_EVENT_ACTION_MASK & AMotionEvent_getAction(event));
                    
	if(action == 0)
	  AuraEngineAndroid::mInstance->mIOEngine->injectTouchEvent(2, AMotionEvent_getRawX(event, 0), AMotionEvent_getRawY(event, 0) );
                    
	AuraEngineAndroid::mInstance->mIOEngine->injectTouchEvent(action, AMotionEvent_getRawX(event, 0), AMotionEvent_getRawY(event, 0) );
      }else {
	AuraEngineAndroid::mInstance->mIOEngine->injectKeyEvent(AKeyEvent_getAction(event), AKeyEvent_getKeyCode(event));
      }
      return 1;
    }
    return 0;
  }
        
  void AuraEngineAndroid::handleCmd(struct android_app* app, int32_t cmd)
  {

    switch (cmd)
      {
      case APP_CMD_SAVE_STATE:
	break;
      case APP_CMD_INIT_WINDOW:{
	if(app->window)
	  {
	    AConfiguration* config = AConfiguration_new();
	    AConfiguration_fromAssetManager(config, AuraEngineAndroid::mInstance->mState->activity->assetManager);
                        
	    if (!AuraEngineAndroid::mInstance->mWindow)
	      {
		Ogre::NameValuePairList opt;
		opt["externalWindowHandle"] = Ogre::StringConverter::toString((int)AuraEngineAndroid::mInstance->mState->window);
		opt["androidConfig"] = Ogre::StringConverter::toString((int)config);
		AuraEngineAndroid::mInstance->mWindow = AuraEngineAndroid::mInstance->mRoot->createRenderWindow("AuraWindow", 0, 0, false, &opt);
   
		if(AuraEngineAndroid::mInstance->mState != NULL)
		  {
		    AuraEngineAndroid::mInstance->mAssetMgr = AuraEngineAndroid::mInstance->mState->activity->assetManager;
		    Ogre::ArchiveManager::getSingleton().addArchiveFactory( new Ogre::APKFileSystemArchiveFactory(AuraEngineAndroid::mInstance->mState->activity->assetManager));
		    Ogre::ArchiveManager::getSingleton().addArchiveFactory( new Ogre::APKZipArchiveFactory(AuraEngineAndroid::mInstance->mState->activity->assetManager) );
		  }

		AuraEngineAndroid::mInstance->initApp();
	      }
	    else
	      {
		static_cast<Ogre::AndroidEGLWindow*>(AuraEngineAndroid::mInstance->mWindow)->_createInternalResources(AuraEngineAndroid::mInstance->mState->window, config);
	      }
	  
	    AConfiguration_delete(config);
	  }
      }
	break;
      case APP_CMD_TERM_WINDOW:
	if(AuraEngineAndroid::mInstance->mRoot && AuraEngineAndroid::mInstance->mWindow)
	  static_cast<Ogre::AndroidEGLWindow*>(AuraEngineAndroid::mInstance->mWindow)->_destroyInternalResources();
	break;
      case APP_CMD_GAINED_FOCUS:
	break;
      case APP_CMD_LOST_FOCUS:
	break;
      case APP_CMD_CONFIG_CHANGED:
	break;
      // case APP_CMD_INPUT_CHANGED:
      // 	break;
      // case APP_CMD_WINDOW_RESIZED:
      // 	break;
      // case APP_CMD_WINDOW_REDRAW_NEEDED:
      // 	break;
      // case APP_CMD_CONTENT_RECT_CHANGED:
      // 	break;
      // case APP_CMD_LOW_MEMORY:
      // 	break;
      // case APP_CMD_START:
      // 	AuraEngineAndroid::mInstance->onStart();
      // 	AuraEngineAndroid::mInstance->mAppCallback->onStart();
      // 	break;
      // case APP_CMD_RESUME:
      // 	AuraEngineAndroid::mInstance->onResume();
      // 	AuraEngineAndroid::mInstance->mAppCallback->onResume();
      // 	break;
      // case APP_CMD_PAUSE:
      // 	AuraEngineAndroid::mInstance->onPause();
      // 	AuraEngineAndroid::mInstance->mAppCallback->onPause();
      // 	break;
      // case APP_CMD_STOP:
      // 	AuraEngineAndroid::mInstance->onStop();
      // 	AuraEngineAndroid::mInstance->mAppCallback->onStop();
      // 	break;
      // case APP_CMD_DESTROY:
      // 	AuraEngineAndroid::mInstance->onDestroy();
      // 	AuraEngineAndroid::mInstance->mAppCallback->onDestroy();
      // 	break;
      }
  }


  bool AuraEngineAndroid::auraFrameStarted(){
    int ident, events;
    struct android_poll_source* source;

    while ((ident = ALooper_pollAll(0, NULL, &events, (void**)&source)) >= 0)
      {
	if (source != NULL)
	  source->process(mState, source);
                    
	if (mState->destroyRequested != 0)
	  return false;
      }

    return true;
  }

  bool AuraEngineAndroid::auraRenderOneFrame(){
    if(mWindow != NULL && mWindow->isActive())
      {
	mWindow->windowMovedOrResized();
	return mRoot->renderOneFrame();
      }
    return true;
  }
  

  void AuraEngineAndroid::initApp( )
  {
    setup();
    Ogre::Root::getSingleton().getRenderSystem()->_initRenderTargets();
    Ogre::Root::getSingleton().clearEventTimes();
  }

  void AuraEngineAndroid::loadConfigFile(Ogre::ConfigFile& cf){
    cf.load(openAPKFile(mFSLayer->getConfigFilePath("resources.cfg")));
  }

  Ogre::DataStreamPtr AuraEngineAndroid::openAPKFile(const Ogre::String& fileName)
  {
    Ogre::DataStreamPtr stream;
    AAsset* asset = AAssetManager_open(mAssetMgr, fileName.c_str(), AASSET_MODE_BUFFER);
    if(asset)
      {
	off_t length = AAsset_getLength(asset);
	void* membuf = OGRE_MALLOC(length, Ogre::MEMCATEGORY_GENERAL);
	memcpy(membuf, AAsset_getBuffer(asset), length);
	AAsset_close(asset);
                
	stream = Ogre::DataStreamPtr(new Ogre::MemoryDataStream(membuf, length, true, true));
      }
    return stream;
  }
}
