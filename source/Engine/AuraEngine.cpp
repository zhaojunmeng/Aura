#include "AuraEngine.h"

namespace Aura {

  AuraEngine::AuraEngine() {
    mFSLayer = OGRE_NEW_T(Ogre::FileSystemLayer, Ogre::MEMCATEGORY_GENERAL)(OGRE_VERSION_NAME);
    mRoot = 0;
    mWindow = 0;
    mOverlaySystem = 0;
    mInit = false;
    mSceneCreated = false;
#ifdef USE_RTSHADER_SYSTEM
    mShaderController = 0;
#endif

    // Init the audio before everything :)
    AuraAudioController::getInstance()->initialize();
  }

  AuraEngine::~AuraEngine() {
    OGRE_DELETE_T(mFSLayer, FileSystemLayer, Ogre::MEMCATEGORY_GENERAL);
  }

  void AuraEngine::init() {    
    // This method is not used, just a model of what the guys should do! :)
    _initEngine();
    _initResources();
  }

  void AuraEngine::_initEngine() {
    // We load the sounds (to give them time)
    mAuraApp->initAudio();

    // Init Ogre :)
    createRoot();
   
    if (mWindow == NULL) createWindow();
   
    setupInput();
    mIOEngine->setIOCallback(mAuraApp);
 
    // Creating the scene manager
    mSceneManager = mRoot->createSceneManager(Ogre::ST_GENERIC, "SceneManager");
    mSceneManager->addRenderQueueListener(mOverlaySystem);
    
    Ogre::Root::getSingleton().getRenderSystem()->_initRenderTargets();
    Ogre::Root::getSingleton().clearEventTimes();
    
    // Create shader controller
#ifdef USE_RTSHADER_SYSTEM
    mShaderController = new ShaderController(mFSLayer);
#endif    

    // Locate resources
    locateResources();
  
#ifdef USE_RTSHADER_SYSTEM
    mShaderController->init();
#endif

#if OGRE_PLATFORM != OGRE_PLATFORM_ANDROID
    Ogre::WindowEventUtilities::addWindowEventListener(mWindow, this);
#endif


    
    // Scene nodes
    AuraQCARController::getInstance()->createImageSceneNodes();
    createBackground();

    // ------ Creating app specific stuff :) ---------
// Creating the camera
    mCamera = mSceneManager->createCamera("Camera");       
    //Ogre::Viewport* viewport = mWindow->addViewport(mCamera);
    //viewport->setBackgroundColour(Ogre::ColourValue(0.0, 1.0 , 0.0));
    mCamera->setPosition(Ogre::Vector3(0, 60, 60));
    mCamera->lookAt(Ogre::Vector3(0, 0, 0));
    mCamera->setNearClipDistance(1);
    mCamera->setFarClipDistance(1000);

    //mCamera->setAspectRatio(Ogre::Real(viewport->getActualWidth()) / Ogre::Real(viewport->getActualHeight()));
    //viewport->setCamera(mCamera);

    /* 
    QCAR::Matrix44F projMat = AuraQCARController::getInstance()->getProjectionMatrix();    
    Ogre::Matrix4 ogreProjMat(projMat.data[0], projMat.data[4],  projMat.data[8],  projMat.data[12],
    			      projMat.data[1], projMat.data[5], projMat.data[9],  projMat.data[13],
     			      projMat.data[2], projMat.data[6], projMat.data[10], projMat.data[14],
     			      projMat.data[3], projMat.data[7], projMat.data[11], projMat.data[15]);
    mCamera->setCustomProjectionMatrix(true, ogreProjMat);
    */

    // We have to ajust the aspect ratio :)
    const QCAR::VideoBackgroundConfig& config = AuraQCARController::getInstance()->getVideoBackgroundConfig(); 
    int screenWidth = AuraQCARController::getInstance()->getScreenWidth();
    int screenHeight = AuraQCARController::getInstance()->getScreenHeight();
    float vZoom = config.mSize.data[1] / (float) screenHeight;
    float vOffset = ((vZoom * screenHeight) - screenHeight) / (2 * screenHeight);
    float uZoom = config.mSize.data[0] / (float) screenWidth;
    float uOffset = ((uZoom * screenWidth) - screenWidth) / (2 * screenWidth);

    //Ogre::Viewport* viewport = mWindow->addViewport(mCamera, 0, -uOffset, -vOffset, uZoom, vZoom);
    Ogre::Viewport* viewport = mWindow->addViewport(mCamera);
    

    //mCamera->setAspectRatio(Ogre::Real(viewport->getActualWidth()) / Ogre::Real(viewport->getActualHeight()));
    //viewport->setCamera(mCamera);

    // Game!
    mAuraApp->setupAuraInterface();
   
    mInit = true;

  }


  void AuraEngine::_initResources(){
    // I would say that from here, we paralelice it!! :)
    loadResources();

    mAuraApp->createScene();
    mSceneCreated = true;

    // Lets start the tracker! :)
    //AuraQCARController::getInstance()->startTracker();

  }

  void AuraEngine::setupInput(){
    mIOEngine = new AuraIOEngine();
    mIOEngine->setupInput(mWindow);
  }

  void AuraEngine::loadResources(){ 
    Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
  }


  void AuraEngine::createRoot() {
    //Ogre::String pluginsPath = Ogre::StringUtil::BLANK;
    //mRoot = OGRE_NEW Ogre::Root(pluginsPath, mFSLayer->getWritablePath("ogre.cfg"), mFSLayer->getWritablePath("ogre.log"));
    mRoot = OGRE_NEW Ogre::Root();
    mRoot->addFrameListener(this);
    mStaticPluginLoader.load();
    mOverlaySystem = OGRE_NEW Ogre::OverlaySystem();
    Ogre::String nextRenderer = mRoot->getAvailableRenderers()[0]->getName();
    mRoot->setRenderSystem(mRoot->getRenderSystemByName(nextRenderer));
  }

  void AuraEngine::loadConfigFile(Ogre::ConfigFile& cf) {
    cf.load(mFSLayer->getConfigFilePath("resources.cfg"));
  }

  void AuraEngine::locateResources() {
    Ogre::ConfigFile cf;
    loadConfigFile(cf);

    Ogre::ConfigFile::SectionIterator seci = cf.getSectionIterator();
    Ogre::String sec, type, arch;

    // go through all specified resource groups
    while (seci.hasMoreElements()) {
      sec = seci.peekNextKey();
      Ogre::ConfigFile::SettingsMultiMap* settings = seci.getNext();
      Ogre::ConfigFile::SettingsMultiMap::iterator i;

      // go through all resource paths
      for (i = settings->begin(); i != settings->end(); i++) {
	type = i->first;
	arch = i->second;

#if OGRE_PLATFORM == OGRE_PLATFORM_APPLE_IOS
	// OS X does not set the working directory relative to the app,
	// In order to make things portable on OS X we need to provide
	// the loading with it's own bundle path location
      	if (!Ogre::StringUtil::startsWith(arch, "/", false))// only adjust relative dirs
	    arch = Ogre::String(Ogre::macBundlePath() + "/" + arch);
#endif
	Ogre::ResourceGroupManager::getSingleton().addResourceLocation(arch, type, sec);
      }
    }

#ifdef USE_RTSHADER_SYSTEM
    mShaderController->locateShaderResources();
#endif

  }

  void AuraEngine::_freeEngine() {
    // Free the resources!
    mAuraApp->destroyScene();

    CkShutdown();

    //#if OGRE_PLATFORM == OGRE_PLATFORM_APPLE_IOS
    //[mGestureView release];
    //#endif
    // Shutdown input
    mIOEngine->shutdownInput();


#ifdef USE_RTSHADER_SYSTEM
    mShaderController->shutdown();
#endif

    // remove window event listener before shutting down OIS
    Ogre::WindowEventUtilities::removeWindowEventListener(mWindow, this);
           
    if (mRoot) {
      OGRE_DELETE mOverlaySystem;
      OGRE_DELETE mRoot;
    }
	
    mStaticPluginLoader.unload();

    mRoot = NULL;
    mWindow = NULL;

    mInit = false;
  }

  void AuraEngine::engineRenderOneFrame(Ogre::Real differenceInSeconds){
    if(mInit) {
      try{
#if OGRE_PLATFORM == OGRE_PLATFORM_ANDROID
	mIOEngine->capture(); 
#endif
	AuraQCARController::getInstance()->update();
	AuraAudioController::getInstance()->update();
	updateBackground();

	//mWindow->windowMovedOrResized(); // Esto no parece funcionar muy bien..no de momento
#if OGRE_PLATFORM == OGRE_PLATFORM_ANDROID
	Ogre::WindowEventUtilities::messagePump();
#endif
	if(!mRoot->renderOneFrame(differenceInSeconds)) finish();
      }catch(Ogre::RenderingAPIException e){}
    }
  }

  void AuraEngine::updateBackground() {
    
    QCAR::Frame& frame = AuraQCARController::getInstance()->getFrame();
    Ogre::uchar* framePixels = static_cast<Ogre::uchar*>(const_cast<void*>(frame.getImage(mFrameImageId)->getPixels()));
    Ogre::TexturePtr texture = Ogre::TextureManager::getSingleton().getByName("Aura/BackgroundTexture", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);

    Ogre::HardwarePixelBufferSharedPtr pixelBuffer = texture->getBuffer();

    pixelBuffer->lock(Ogre::HardwareBuffer::HBL_DISCARD);
    const Ogre::PixelBox& pixelBox = pixelBuffer->getCurrentLock();
    Ogre::uint8* pDest = static_cast<Ogre::uint8*>(pixelBox.data);


    int texPosRow = 0;
    int texPos = 0;
    for (int j = 0; j <  mFrameHeight; j++) {
      for (int i = 0; i <  mFrameWidth; i++) {
	pDest[texPos++] = *((Ogre::uchar*) (framePixels)++);
	pDest[texPos++] = *((Ogre::uchar*) (framePixels)++);
	pDest[texPos++] = *((Ogre::uchar*) (framePixels)++);
      }

      texPosRow += mTexBytesRow;
      texPos = texPosRow;
    }// End method 1

    pixelBuffer->unlock();

  }

  void AuraEngine::createBackground() {

    /* Ogre code */
    Ogre::TexturePtr texture =
      Ogre::TextureManager::getSingleton().createManual("Aura/BackgroundTexture", // name
							Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
							Ogre::TEX_TYPE_2D, // texture type
							QCAR::CameraDevice::getInstance().getVideoMode(0).mWidth,
							QCAR::CameraDevice::getInstance().getVideoMode(0).mHeight,
							0, 
							Ogre::PF_R8G8B8, // pixel format
							Ogre::HardwareBuffer::HBU_DYNAMIC_WRITE_ONLY_DISCARDABLE);

    // Create the dynamic image to fill out the texture :)
    

    // Get pixels per row in the texture :)
    Ogre::HardwarePixelBufferSharedPtr pixelBuffer = texture->getBuffer();
    pixelBuffer->lock(Ogre::HardwareBuffer::HBL_DISCARD);
    const Ogre::PixelBox& pixelBox = pixelBuffer->getCurrentLock();
    mTexBytesRow = pixelBox.rowPitch*3;
    pixelBuffer->unlock();

    // Get and store in the class the frame height :)
    mFrameHeight = QCAR::CameraDevice::getInstance().getVideoMode(0).mHeight;
    mFrameWidth = QCAR::CameraDevice::getInstance().getVideoMode(0).mWidth;

    // Get the id of the image that we are looking for :)
    AuraQCARController::getInstance()->update(); // We grab one frame :)
    QCAR::Frame& frame = AuraQCARController::getInstance()->getFrame(); // Just to store that id
    for (int img = 0; img < frame.getNumImages(); ++img) {
      if (frame.getImage(img)->getFormat() == QCAR::RGB888){
	mFrameImageId = img;
	break;
      }
    }

    Ogre::MaterialPtr material = Ogre::MaterialManager::getSingleton().create("Aura/BackgroundMaterial", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);

    material->getTechnique(0)->getPass(0)->createTextureUnitState();
    material->getTechnique(0)->getPass(0)->setSceneBlending(Ogre::SBT_TRANSPARENT_ALPHA);
    material->getTechnique(0)->getPass(0)->setDepthCheckEnabled(false);
    material->getTechnique(0)->getPass(0)->setDepthWriteEnabled(false);
    material->getTechnique(0)->getPass(0)->setLightingEnabled(false);
    material->getTechnique(0)->getPass(0)->getTextureUnitState(0)->setTextureName("Aura/BackgroundTexture");
    

    // Create background rectangle covering the whole screen
    Ogre::Rectangle2D* rect = new Ogre::Rectangle2D(true);

    // Not all the texture is frame, we have to adjust the u, v coordinates
    float u,v;
    const QCAR::VideoMode& videoMode = AuraQCARController::getInstance()->getVideoMode();

    // area of the texture with the frame :)
    u = videoMode.mWidth / (float)texture->getWidth();
    v = videoMode.mHeight / (float)texture->getHeight();

    rect->setUVs(Ogre::Vector2(0, 0),Ogre::Vector2(0, v),Ogre::Vector2(u, 0),Ogre::Vector2(u, v));
    rect->setCorners(-1.0, 1.0, 1.0, -1.0);
    rect->setMaterial("Aura/BackgroundMaterial");

    // Render the background before everything else
    rect->setRenderQueueGroup(Ogre::RENDER_QUEUE_BACKGROUND);
    rect->setBoundingBox(Ogre::AxisAlignedBox(-100000.0 * Ogre::Vector3::UNIT_SCALE,
					      100000.0 * Ogre::Vector3::UNIT_SCALE));

    // Attach background to the scene
    Ogre::SceneNode* node = mSceneManager->getRootSceneNode()->createChildSceneNode("Aura/BackgroundNode");
    node->attachObject(rect);

  }
}// Aura
