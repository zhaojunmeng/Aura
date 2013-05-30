#include "AuraEngineAndroid.h"

namespace Aura{

  AuraEngineAndroid* AuraEngineAndroid::mInstance = NULL;

  AuraEngineAndroid::AuraEngineAndroid(): AuraEngine(){
      
    AuraEngineAndroid::mInstance = this;
    mState = AuraJNIUtils::getInstance()->getState();
    mState->onAppCmd = &Aura::AuraEngineAndroid::handleCmd;
    mState->onInputEvent = &Aura::AuraEngineAndroid::handleInput;

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


  void AuraEngineAndroid::createWindow(){

    mRoot->initialise(false);    
    AConfiguration* config = AConfiguration_new();
    AConfiguration_fromAssetManager(config, AuraEngineAndroid::mInstance->mState->activity->assetManager);
    
    if (!AuraEngineAndroid::mInstance->mWindow)
      {	
	Ogre::NameValuePairList opt;
	opt["externalWindowHandle"] = Ogre::StringConverter::toString((int)AuraEngineAndroid::mInstance->mState->window);
	opt["androidConfig"] = Ogre::StringConverter::toString((int)config);
	AuraEngineAndroid::mInstance->mWindow = AuraEngineAndroid::mInstance->mRoot->createRenderWindow("AuraWindow", 0, 0, false, &opt);
   
	AuraEngineAndroid::mInstance->mAssetMgr = AuraEngineAndroid::mInstance->mState->activity->assetManager;
	Ogre::ArchiveManager::getSingleton().addArchiveFactory( new Ogre::APKFileSystemArchiveFactory(AuraEngineAndroid::mInstance->mState->activity->assetManager));
	Ogre::ArchiveManager::getSingleton().addArchiveFactory( new Ogre::APKZipArchiveFactory(AuraEngineAndroid::mInstance->mState->activity->assetManager) );

      }
       
    else
      {
	static_cast<Ogre::AndroidEGLWindow*>(AuraEngineAndroid::mInstance->mWindow)->_createInternalResources(AuraEngineAndroid::mInstance->mState->window, config);
      }

	  
    AConfiguration_delete(config);

  }

  void AuraEngineAndroid::setupInput(){
    mIOEngine = new AuraIOEngineAndroid();
    mIOEngine->setupInput(mWindow);
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


  void AuraEngineAndroid::handleCmd(struct android_app* app, int32_t cmd)
  {
    switch (cmd)
      {
      case APP_CMD_SAVE_STATE:
	AuraLog::info("APP_CMD_SAVE_STATE");
	break;
      case APP_CMD_INIT_WINDOW:{
	AuraLog::info("APP_CMD_INIT_WINDOW");
	if(app->window)
	  {
	    AuraEngineAndroid::mInstance->_initEngine();
	  }
      }
	break;
      case APP_CMD_TERM_WINDOW:
	AuraLog::info("APP_TERM_WINDOW");

	//if(AuraEngineAndroid::mInstance->mRoot && AuraEngineAndroid::mInstance->mWindow){
	//  AuraLog::info("Destroying internal resources :)");
	//  static_cast<Ogre::AndroidEGLWindow*>(AuraEngineAndroid::mInstance->mWindow)->_destroyInternalResources();
	//}

	AuraEngineAndroid::mInstance->_freeResources();
	AuraQCARController::getInstance()->shutdown();
	break;
      case APP_CMD_GAINED_FOCUS:
	AuraLog::info("APP_CMD_GAINED_FOCUS");
	break;
      case APP_CMD_LOST_FOCUS:
	AuraLog::info("APP_CMD_LOST_FOCUS");
	break;
      case APP_CMD_CONFIG_CHANGED:
	AuraLog::info("APP_CMD_CONFIG_CHANGED");
	break;
      case APP_CMD_INPUT_CHANGED:
	AuraLog::info("APP_CMD_INPUT_CHANGED");
	break;
      case APP_CMD_WINDOW_RESIZED:
	AuraLog::info("APP_CMD_WINDOW_RESIZED");
	break;
      case APP_CMD_WINDOW_REDRAW_NEEDED:
	AuraLog::info("APP_CMD_REDRAW_NEEDED");
	break;
      case APP_CMD_CONTENT_RECT_CHANGED:
	AuraLog::info("APP_CMD_RECT_CHANGED");
	break;
      case APP_CMD_LOW_MEMORY:
	AuraLog::info("APP_CMD_LOW_MEMORY");
	break;
      case APP_CMD_START:
	AuraLog::info("APP_CMD_START");
	break;
      case APP_CMD_RESUME:
	AuraLog::info("APP_CMD_RESUME");
	//Aura::AuraQCARController::getInstance()->startCamera();
	//QCAR::onResume();
	//Aura::AuraJNIUtils::getInstance()->getAuraApp()->setPause(false);
	break;
      case APP_CMD_PAUSE:
	AuraLog::info("APP_CMD_PAUSE");
	//Aura::AuraQCARController::getInstance()->stopCamera();
	//QCAR::onPause();
	//Aura::AuraJNIUtils::getInstance()->getAuraApp()->setPause(true);
	break;
      case APP_CMD_STOP:
	AuraLog::info("APP_CMD_STOP");
	break;
      case APP_CMD_DESTROY:
	AuraLog::info("APP_CMD_DESTORY");
	break;
      }
  }


  int32_t AuraEngineAndroid::handleInput(struct android_app* app, AInputEvent* event){

    if(!AuraEngineAndroid::mInstance->mInit) return 0;

    if (AuraEngineAndroid::mInstance->mIOEngine){
      if (AInputEvent_getType(event) == AINPUT_EVENT_TYPE_MOTION){
	int action = (int)(AMOTION_EVENT_ACTION_MASK & AMotionEvent_getAction(event));
                    
	if(action == 0)
	  static_cast<AuraIOEngineAndroid*>(AuraEngineAndroid::mInstance->mIOEngine)->injectTouchEvent(2, AMotionEvent_getRawX(event, 0), AMotionEvent_getRawY(event, 0) );
	
	static_cast<AuraIOEngineAndroid*>(AuraEngineAndroid::mInstance->mIOEngine)->injectTouchEvent(action, AMotionEvent_getRawX(event, 0), AMotionEvent_getRawY(event, 0) );
      }else {
	static_cast<AuraIOEngineAndroid*>(AuraEngineAndroid::mInstance->mIOEngine)->injectKeyEvent(AKeyEvent_getAction(event), AKeyEvent_getKeyCode(event));
      }
      return 1;
    }

    return 0;
  }
        





  void AuraEngineAndroid::shutdown(){
    // Officially finish it :)
    ANativeActivity_finish(AuraJNIUtils::getInstance()->getState()->activity);

    int ident, events;
    struct android_poll_source* source;
    while(true){
      while ((ident = ALooper_pollAll(0, NULL, &events, (void**)&source)) >= 0)
	{
	  if (source != NULL)
	    source->process(mState, source);
	  
	  if (mState->destroyRequested != 0){
	    return;
	  }
	}
    }
  }


  bool AuraEngineAndroid::engineFrameStarted(){
    int ident, events;
    struct android_poll_source* source;

    while ((ident = ALooper_pollAll(0, NULL, &events, (void**)&source)) >= 0)
      {
	if (source != NULL)
	  source->process(mState, source);
                    
	if (mState->destroyRequested != 0){
	  return false;
	}
      }

    return true;
  }
}
