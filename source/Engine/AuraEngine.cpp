#include "AuraEngine.h"

namespace Aura{

  AuraEngine::AuraEngine()
  {
    mFSLayer = OGRE_NEW_T(Ogre::FileSystemLayer, Ogre::MEMCATEGORY_GENERAL)(OGRE_VERSION_NAME);
    mRoot = 0;
    mWindow = 0;
    mOverlaySystem = 0;
#ifdef USE_RTSHADER_SYSTEM
    mShaderController = 0;
#endif
  }

  AuraEngine::~AuraEngine() 
  {
    OGRE_DELETE_T(mFSLayer, FileSystemLayer, Ogre::MEMCATEGORY_GENERAL);
  }

  void AuraEngine::init( )
  {
    createRoot();
    Ogre::String nextRenderer = mRoot->getAvailableRenderers()[0]->getName();
    mRoot->setRenderSystem(mRoot->getRenderSystemByName(nextRenderer));
    setup();
  }

  Ogre::RenderWindow* AuraEngine::createWindow()
  {
    Ogre::RenderWindow* res = mRoot->initialise(true, "AuraWindow");
    return res;
  }


  void AuraEngine::setup()
  {
    if(mWindow == NULL)  mWindow = createWindow();
  
    mScreenWidth = mWindow->getWidth();
    mScreenHeight = mWindow->getHeight();

    mSceneManager = mRoot->createSceneManager(Ogre::ST_GENERIC, "SceneManager");
    mSceneManager->addRenderQueueListener(mOverlaySystem);
    mCamera = mSceneManager->createCamera("Camera");
  
    // Load shader!!
#ifdef USE_RTSHADER_SYSTEM
    mShaderController = new ShaderController(mFSLayer);
#endif
  
    locateResources();
    loadResources();
  
#ifdef USE_RTSHADER_SYSTEM
    mShaderController->init();
#endif
  
    Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);
  
    createBackground();

    // adds context as listener to process context-level (above the sample level) events
    mRoot->addFrameListener(this);
  
#if OGRE_PLATFORM != OGRE_PLATFORM_ANDROID
    Ogre::WindowEventUtilities::addWindowEventListener(mWindow, this);
#endif
    windowResized(mWindow);   // adjust menus for resolution
  
    // add a bright light above the scene
    Ogre::Light* light = mSceneManager->createLight();
    light->setType(Ogre::Light::LT_POINT);
    light->setPosition(-10, 40, 20);
    light->setSpecularColour(Ogre::ColourValue::White);

    //mWindow->removeAllViewports();
    Ogre::Viewport* viewport = mWindow->addViewport(mCamera);
    viewport->setBackgroundColour(Ogre::ColourValue(1.0,0.0,0.0));
    double width = viewport->getActualWidth();
    double height = viewport->getActualHeight();
    mCamera->setAspectRatio(width / height);
  }

	
  void AuraEngine::shutdown()
  {
#if OGRE_PLATFORM == OGRE_PLATFORM_APPLE_IOS
    [mGestureView release];
#endif
    // Shutdown input
    mWindow = 0;
    // remove window event listener before shutting down OIS
    Ogre::WindowEventUtilities::removeWindowEventListener(mWindow, this);
	  
    if (mRoot)
      {
	OGRE_DELETE mOverlaySystem;
	OGRE_DELETE mRoot;
      }
    mStaticPluginLoader.unload();

#ifdef USE_RTSHADER_SYSTEM
    mShaderController->shutdown();
#endif
  }


  void AuraEngine::drawBackground(const QCAR::Frame& frame){

    Ogre::TexturePtr texture = Ogre::TextureManager::getSingleton().getByName("BackgroundTex",Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
    
    Ogre::HardwarePixelBufferSharedPtr pixelBuffer = texture->getBuffer();
    
    pixelBuffer->lock(Ogre::HardwareBuffer::HBL_DISCARD);
    const Ogre::PixelBox& pixelBox = pixelBuffer->getCurrentLock();
    
    Ogre::uint8* pDest = static_cast<Ogre::uint8*>(pixelBox.data);
    
     for(int j=0;j<mScreenHeight;j++) {
      for(int i=0;i<mScreenWidth;i++) {
    	//int idx = ((frame->rows - 1 - j) * pixelBox.rowPitch + i )*4; //Use pixelBox.rowPitch instead of "width"
    	 int idx = ((j) * pixelBox.rowPitch + i )*4; //Use pixelBox.rowPitch instead of "width"
    	 //pDest[idx] = frame.getImage(1)->getPixels() + (j*mScreenWidth + i)*3;
    	 //pDest[idx + 1] = frame.getImage(1)->getPixels() + (j*mScreenWidth + i)*3 + 1;
    	 //pDest[idx + 2] = frame.getImage(1)->getPixels() + (j*mScreenWidth + i)*3 + 2;
    	 //pDest[idx + 3] = 255;
	 pDest[idx] = 0;
    	 pDest[idx + 1] = 255;
    	 pDest[idx + 2] = 0;
    	 pDest[idx + 3] = 255;
      
      }
    }
    
    pixelBuffer->unlock();
    

    Ogre::Rectangle2D* rect = static_cast<Ogre::Rectangle2D*>(mSceneManager->getSceneNode("BackgroundNode")->getAttachedObject(0));
    Ogre::MaterialPtr material = rect->getMaterial();
}

  void AuraEngine::createBackground(){
  
  /* Ogre code */
  Ogre::TexturePtr texture=Ogre::TextureManager::getSingleton().createManual(
            "BackgroundTex",// name
	    Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
            Ogre::TEX_TYPE_2D,// texture type
	    mScreenWidth,
	    mScreenHeight,
            0,// number of mipmaps
            //Ogre::PF_B8G8R8,// pixel format
	    Ogre::PF_BYTE_BGRA,
	    //Ogre::TU_DYNAMIC_WRITE_ONLY_DISCARDABLE
	    //Ogre::TU_DYNAMIC_WRITE
	    Ogre::HardwareBuffer::HBU_DYNAMIC_WRITE_ONLY_DISCARDABLE
            );



  Ogre::MaterialPtr material = Ogre::MaterialManager::getSingleton().create("Background", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME); 
  material->getTechnique(0)->getPass(0)->createTextureUnitState(); 
  material->getTechnique(0)->getPass(0)->setSceneBlending(Ogre::SBT_TRANSPARENT_ALPHA);
  material->getTechnique(0)->getPass(0)->setDepthCheckEnabled(false); 
  material->getTechnique(0)->getPass(0)->setDepthWriteEnabled(false); 
  material->getTechnique(0)->getPass(0)->setLightingEnabled(false);   
  material->getTechnique(0)->getPass(0)->getTextureUnitState(0)->setTextureName("BackgroundTex");

  // Create background rectangle covering the whole screen 
  Ogre::Rectangle2D* rect = new Ogre::Rectangle2D(true); 
  rect->setCorners(-1.0, 1.0, 1.0, -1.0); 
  rect->setMaterial("Background"); 
  
  // Render the background before everything else 
  rect->setRenderQueueGroup(Ogre::RENDER_QUEUE_BACKGROUND);   
  
  // Hacky, but we need to set the bounding box to something big 
  // NOTE: If you are using Eihort (v1.4), please see the note below on setting the bounding box 
  rect->setBoundingBox(Ogre::AxisAlignedBox(-100000.0*Ogre::Vector3::UNIT_SCALE, 100000.0*Ogre::Vector3::UNIT_SCALE));   
  
  // Attach background to the scene 
  Ogre::SceneNode* node = mSceneManager->getRootSceneNode()->createChildSceneNode("BackgroundNode"); 
  node->attachObject(rect);   
  
 }



  void AuraEngine::createRoot()
  {
    Ogre::String pluginsPath = Ogre::StringUtil::BLANK;
    mRoot = OGRE_NEW Ogre::Root(pluginsPath, mFSLayer->getWritablePath("ogre.cfg"), 
				mFSLayer->getWritablePath("ogre.log"));
    mStaticPluginLoader.load();
    mOverlaySystem = OGRE_NEW Ogre::OverlaySystem();
  }

  void AuraEngine::loadConfigFile(Ogre::ConfigFile& cf){
    cf.load(mFSLayer->getConfigFilePath("resources.cfg"));	  
  }

  void AuraEngine::locateResources()
  {
    Ogre::ConfigFile cf;
    loadConfigFile(cf);

    Ogre::ConfigFile::SectionIterator seci = cf.getSectionIterator();
    Ogre::String sec, type, arch;

    // go through all specified resource groups
    while (seci.hasMoreElements())
      {
	sec = seci.peekNextKey();
	Ogre::ConfigFile::SettingsMultiMap* settings = seci.getNext();
	Ogre::ConfigFile::SettingsMultiMap::iterator i;

	// go through all resource paths
	for (i = settings->begin(); i != settings->end(); i++)
	  {
	    type = i->first;
	    arch = i->second;

#if OGRE_PLATFORM == OGRE_PLATFORM_APPLE || OGRE_PLATFORM == OGRE_PLATFORM_APPLE_IOS
	    // OS X does not set the working directory relative to the app,
	    // In order to make things portable on OS X we need to provide
	    // the loading with it's own bundle path location
	    if (!Ogre::StringUtil::startsWith(arch, "/", false)) // only adjust relative dirs
	      arch = Ogre::String(Ogre::macBundlePath() + "/" + arch);
#endif
	    Ogre::ResourceGroupManager::getSingleton().addResourceLocation(arch, type, sec);
	  }
      }

#ifdef USE_RTSHADER_SYSTEM
    mShaderController->locateShaderResources();
#endif

  }
}
