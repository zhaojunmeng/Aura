#include "AuraOgreEngine.h"

namespace Aura{

  AuraOgreEngine::AuraOgreEngine()
  {
    mFSLayer = OGRE_NEW_T(Ogre::FileSystemLayer, Ogre::MEMCATEGORY_GENERAL)(OGRE_VERSION_NAME);
    mRoot = 0;
    mWindow = 0;
    mOverlaySystem = 0;
#ifdef USE_RTSHADER_SYSTEM
    mShaderController = 0;
#endif
  }

  AuraOgreEngine::~AuraOgreEngine() 
  {
    OGRE_DELETE_T(mFSLayer, FileSystemLayer, Ogre::MEMCATEGORY_GENERAL);
  }

  void AuraOgreEngine::init( )
  {
    createRoot();
    Ogre::String nextRenderer = mRoot->getAvailableRenderers()[0]->getName();
    mRoot->setRenderSystem(mRoot->getRenderSystemByName(nextRenderer));
    setup();
  }

  Ogre::RenderWindow* AuraOgreEngine::createWindow()
  {
    Ogre::RenderWindow* res = mRoot->initialise(true, "AuraWindow");
    return res;
  }


  void AuraOgreEngine::setup()
  {
    if(mWindow == NULL)  mWindow = createWindow();
  
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

	
  void AuraOgreEngine::shutdown()
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
	

  void AuraOgreEngine::createRoot()
  {
    Ogre::String pluginsPath = Ogre::StringUtil::BLANK;
    mRoot = OGRE_NEW Ogre::Root(pluginsPath, mFSLayer->getWritablePath("ogre.cfg"), 
				mFSLayer->getWritablePath("ogre.log"));
    mStaticPluginLoader.load();
    mOverlaySystem = OGRE_NEW Ogre::OverlaySystem();
  }

  void AuraOgreEngine::loadConfigFile(Ogre::ConfigFile& cf){
    cf.load(mFSLayer->getConfigFilePath("resources.cfg"));	  
  }

  void AuraOgreEngine::locateResources()
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
