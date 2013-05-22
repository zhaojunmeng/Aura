#include "AuraOgreEngineAndroid.h"

namespace Aura{

  AuraOgreEngineAndroid::AuraOgreEngineAndroid(struct android_app* state, AuraIOEngineAndroid* ioEngine): AuraOgreEngine(), mState(state), mIOEngine(ioEngine){
      
    AuraOgreEngineAndroid::mInstance = this;

    mState->onAppCmd = &Aura::AuraOgreEngineAndroid::handleCmd;
    mState->onInputEvent = &Aura::AuraOgreEngineAndroid::handleInput;
      
    mRoot = new Ogre::Root("");
    mStaticPluginLoader.load();
    mRoot->setRenderSystem(mRoot->getAvailableRenderers().at(0));
    mRoot->initialise(false);
    mOverlaySystem = OGRE_NEW Ogre::OverlaySystem();

    mInit = true;
    mWindow = 0;
  }
    
  void AuraOgreEngineAndroid::init()
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

  void AuraOgreEngineAndroid::shutdown()
  {
    if(!mInit)
      return;
                
    mInit = false;
            
    OGRE_DELETE mRoot;
    mRoot = NULL;
    mWindow = NULL;
            
            
    mStaticPluginLoader.unload();
    //delete mStaticPluginLoader;
    //mStaticPluginLoader = NULL;

    Ogre::WindowEventUtilities::removeWindowEventListener(mWindow, this);

    ANativeActivity_finish(mState->activity);
  }

  int32_t AuraOgreEngineAndroid::handleInput(struct android_app* app, AInputEvent* event) 
  {
    if (AuraOgreEngineAndroid::mInstance->mIOEngine)
      {
	if (AInputEvent_getType(event) == AINPUT_EVENT_TYPE_MOTION)
	  {
	    int action = (int)(AMOTION_EVENT_ACTION_MASK & AMotionEvent_getAction(event));
                    
	    if(action == 0)
	      AuraOgreEngineAndroid::mInstance->mIOEngine->injectTouchEvent(2, AMotionEvent_getRawX(event, 0), AMotionEvent_getRawY(event, 0) );
                    
	    AuraOgreEngineAndroid::mInstance->mIOEngine->injectTouchEvent(action, AMotionEvent_getRawX(event, 0), AMotionEvent_getRawY(event, 0) );
	  }
	else
	  {
	    AuraOgreEngineAndroid::mInstance->mIOEngine->injectKeyEvent(AKeyEvent_getAction(event), AKeyEvent_getKeyCode(event));
	  }

	return 1;
      }
    return 0;
  }
        
  void AuraOgreEngineAndroid::handleCmd(struct android_app* app, int32_t cmd)
  {

    switch (cmd)
      {
      case APP_CMD_SAVE_STATE:
	break;
      case APP_CMD_INIT_WINDOW:{
	if(app->window)
	  {
	    AConfiguration* config = AConfiguration_new();
	    AConfiguration_fromAssetManager(config, AuraOgreEngineAndroid::mInstance->mState->activity->assetManager);
                        
	    if (!AuraOgreEngineAndroid::mInstance->mWindow)
	      {
		Ogre::NameValuePairList opt;
		opt["externalWindowHandle"] = Ogre::StringConverter::toString((int)AuraOgreEngineAndroid::mInstance->mState->window);
		opt["androidConfig"] = Ogre::StringConverter::toString((int)config);
		AuraOgreEngineAndroid::mInstance->mWindow = AuraOgreEngineAndroid::mInstance->mRoot->createRenderWindow("AuraWindow", 0, 0, false, &opt);
   
		if(AuraOgreEngineAndroid::mInstance->mState != NULL)
		  {
		    AuraOgreEngineAndroid::mInstance->mAssetMgr = AuraOgreEngineAndroid::mInstance->mState->activity->assetManager;
		    Ogre::ArchiveManager::getSingleton().addArchiveFactory( new Ogre::APKFileSystemArchiveFactory(AuraOgreEngineAndroid::mInstance->mState->activity->assetManager));
		    Ogre::ArchiveManager::getSingleton().addArchiveFactory( new Ogre::APKZipArchiveFactory(AuraOgreEngineAndroid::mInstance->mState->activity->assetManager) );
		  }

		AuraOgreEngineAndroid::mInstance->initApp();
	      }
	    else
	      {
		static_cast<Ogre::AndroidEGLWindow*>(AuraOgreEngineAndroid::mInstance->mWindow)->_createInternalResources(AuraOgreEngineAndroid::mInstance->mState->window, config);
	      }
	  
	    AConfiguration_delete(config);
	  }
      }
	break;
      case APP_CMD_TERM_WINDOW:
	if(AuraOgreEngineAndroid::mInstance->mRoot && AuraOgreEngineAndroid::mInstance->mWindow)
	  static_cast<Ogre::AndroidEGLWindow*>(AuraOgreEngineAndroid::mInstance->mWindow)->_destroyInternalResources();
	break;
      case APP_CMD_GAINED_FOCUS:
	break;
      case APP_CMD_LOST_FOCUS:
	break;
      case APP_CMD_CONFIG_CHANGED:
	break;
      }
  }


  bool AuraOgreEngineAndroid::auraFrameStarted(){
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

  bool AuraOgreEngineAndroid::auraRenderOneFrame(){
    if(mWindow != NULL && mWindow->isActive())
      {
	mWindow->windowMovedOrResized();
	return mRoot->renderOneFrame();
      }
    return true;
  }
  

  void AuraOgreEngineAndroid::initApp( )
  {
    setup();
    Ogre::Root::getSingleton().getRenderSystem()->_initRenderTargets();
    Ogre::Root::getSingleton().clearEventTimes();
  }

  void AuraOgreEngineAndroid::loadConfigFile(Ogre::ConfigFile& cf){
    cf.load(openAPKFile(mFSLayer->getConfigFilePath("resources.cfg")));
  }

  Ogre::DataStreamPtr AuraOgreEngineAndroid::openAPKFile(const Ogre::String& fileName)
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
