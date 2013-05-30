#include "AuraEngineAndroid.h"

namespace Aura{

  AuraEngineAndroid* AuraEngineAndroid::mInstance = NULL;

  AuraEngineAndroid::AuraEngineAndroid(): AuraEngine(){
      
    AuraEngineAndroid::mInstance = this;
    mState = AuraJNIUtils::getInstance()->getState();
    mState->onAppCmd = &Aura::AuraEngineAndroid::handleCmd;
    mState->onInputEvent = &Aura::AuraEngineAndroid::handleInput;
    mWindow = 0;

    mIOEngine = new AuraIOEngineAndroid();
    mIOEngine->setupInput(mWindow);
    mInit = false;
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

    // Shutdown input
    mIOEngine->shutdownInput();
  
#ifdef USE_RTSHADER_SYSTEM
    mShaderController->shutdown();
#endif
	
    Ogre::WindowEventUtilities::removeWindowEventListener(mWindow, this);

    if(mRoot){
      OGRE_DELETE mOverlaySystem;
      OGRE_DELETE mRoot;
    }

    mStaticPluginLoader.unload();

    mRoot = NULL;
    mWindow = NULL;
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
        
  void AuraEngineAndroid::handleCmd(struct android_app* app, int32_t cmd)
  {
    switch (cmd)
      {
      case APP_CMD_SAVE_STATE:
	//LOGI("APP_CMD_SAVE_STATE");
	break;
      case APP_CMD_INIT_WINDOW:{
	//LOGI("APP_CMD_INIT_WINDOW");
	if(app->window)
	  {
	    AuraEngineAndroid::mInstance->setupAndroid();
	  }
      }
	break;
      case APP_CMD_TERM_WINDOW:
	//if(AuraEngineAndroid::mInstance->mRoot && AuraEngineAndroid::mInstance->mWindow){
	//  LOGI("Destroying internal resources :)");
	//  static_cast<Ogre::AndroidEGLWindow*>(AuraEngineAndroid::mInstance->mWindow)->_destroyInternalResources();
	//}

	AuraEngineAndroid::mInstance->shutdown();
	AuraQCARController::getInstance()->shutdown();
	break;
      case APP_CMD_GAINED_FOCUS:
	//	   LOGI("APP_CMD_GAINED_FOCUS");
	break;
      case APP_CMD_LOST_FOCUS:
	// LOGI("APP_CMD_LOST_FOCUS");
	break;
      case APP_CMD_CONFIG_CHANGED:
	// LOGI("APP_CMD_CONFIG_CHANGED");
	break;
      case APP_CMD_INPUT_CHANGED:
	//LOGI("APP_CMD_INPUT_CHANGED");
	break;
      case APP_CMD_WINDOW_RESIZED:
	//LOGI("APP_CMD_WINDOW_RESIZED");
	break;
      case APP_CMD_WINDOW_REDRAW_NEEDED:
	//LOGI("APP_CMD_REDRAW_NEEDED");
	break;
      case APP_CMD_CONTENT_RECT_CHANGED:
	//LOGI("APP_CMD_RECT_CHANGED");
	break;
      case APP_CMD_LOW_MEMORY:
	//LOGI("APP_CMD_LOW_MEMORY");
	break;
      case APP_CMD_START:
	//LOGI("APP_CMD_START");
	break;
      case APP_CMD_RESUME:
	break;
      case APP_CMD_PAUSE:
	//LOGI("APP_CMD_PAUSe");
	break;
      case APP_CMD_STOP:
	break;
      case APP_CMD_DESTROY:
	break;
      }
  }


  bool AuraEngineAndroid::auraFrameStarted(){
    int ident, events;
    struct android_poll_source* source;

    mIOEngine->capture();

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

  void AuraEngineAndroid::finish(){
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


  bool AuraEngineAndroid::auraRenderOneFrame(){
    if(mWindow != NULL && mWindow->isActive())
      {
	try{
	  updateBackground();
	  mWindow->windowMovedOrResized();
	  return mRoot->renderOneFrame();
	}catch(Ogre::RenderingAPIException e){}
	
      }
    return true;
  }
  

  void AuraEngineAndroid::setupAndroid( )
  {
    
    mRoot = new Ogre::Root();
    mStaticPluginLoader.load();
    mRoot->setRenderSystem(mRoot->getAvailableRenderers().at(0));
    mRoot->initialise(false);
    mOverlaySystem = OGRE_NEW Ogre::OverlaySystem();
    
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

    // Rest of the initialization
    setup();
    Ogre::Root::getSingleton().getRenderSystem()->_initRenderTargets();
    Ogre::Root::getSingleton().clearEventTimes();

    mInit = true;
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
