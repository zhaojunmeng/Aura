#include "ShaderController.h"

namespace Aura{

  ShaderController::ShaderController(Ogre::FileSystemLayer* fsLayer){
    mFSLayer = fsLayer;
    mMaterialMgrListener = NULL;
    mShaderGenerator = NULL;		
  }


  void ShaderController::init(){
#if defined(ENABLE_SHADERS_CACHE_LOAD)
    AuraLog::info("Loading shaders...");
    // Load for a package version of the shaders.
    Ogre::String path = getShaderCacheFileName();
    FILE * inFile = NULL;
    inFile = fopen(path.c_str(), "rb");
    // If that does not exist, see if there is a version in the writable location.
    if (!inFile){
      path = mFSLayer->getWritablePath(getShaderCacheFileName());
      inFile = fopen(path.c_str(), "rb");
    }
    if (inFile){
      Ogre::LogManager::getSingleton().logMessage("Loading shader cache from ");
      Ogre::LogManager::getSingleton().logMessage(path.c_str());
      Ogre::DataStreamPtr istream(new Ogre::FileHandleDataStream(path.c_str(), inFile, Ogre::DataStream::READ));
      Ogre::GpuProgramManager::getSingleton().loadMicrocodeCache(istream);
    }
#endif

    // Initialize shader generator.
    // Must be before resource loading in order to allow parsing extended material attributes.
    Ogre::Root& mRoot = Ogre::Root::getSingleton();
    Ogre::SceneManager* mSceneManager = mRoot.getSceneManager("SceneManager");

    bool success = initializeRTShaderSystem(mSceneManager);
    if (!success){
      OGRE_EXCEPT(Ogre::Exception::ERR_FILE_NOT_FOUND, "Shader Generator Initialization failed - Core shader libs path not found", "AuraApplication");
    }
    
      // Assuming that it is a mobile device (no Fixed capabilities)
    //if(mRoot.getRenderSystem()->getCapabilities()->hasCapability(Ogre::RSC_FIXED_FUNCTION) == false){
    //  Ogre::RTShader::ShaderGenerator::getSingletonPtr()->addSceneManager(mSceneManager);
    //}
  }


  void ShaderController::shutdown(){
#if defined(ENABLE_SHADERS_CACHE_SAVE) 
    AuraLog::info("Writting shaders...");
    if (Ogre::GpuProgramManager::getSingleton().isCacheDirty()){
      Ogre::String path = mFSLayer->getWritablePath(getShaderCacheFileName());
      FILE * outFile = fopen(path.c_str(), "wb");
      AuraLog::info("Actually writting :)");
      if (outFile) {
	Ogre::LogManager::getSingleton().logMessage("Writing shader cache to ");
	Ogre::LogManager::getSingleton().logMessage(path.c_str());
	Ogre::DataStreamPtr ostream(new Ogre::FileHandleDataStream(path.c_str(), outFile, Ogre::DataStream::WRITE));
	Ogre::GpuProgramManager::getSingleton().saveMicrocodeCache(ostream);
	ostream->close();
      }
    }
#endif


    // Finalize the RT Shader System.
    finalizeRTShaderSystem();
  }


  /*-----------------------------------------------------------------------------
    | Initialize the RT Shader system.	
    -----------------------------------------------------------------------------*/
  bool ShaderController::initializeRTShaderSystem(Ogre::SceneManager* sceneMgr){			
    if (Ogre::RTShader::ShaderGenerator::initialize()){
      mShaderGenerator = Ogre::RTShader::ShaderGenerator::getSingletonPtr();
      mShaderGenerator->addSceneManager(sceneMgr);

#if OGRE_PLATFORM != OGRE_PLATFORM_ANDROID && OGRE_PLATFORM != OGRE_PLATFORM_WINRT
      // Setup core libraries and shader cache path.
      Ogre::StringVector groupVector = Ogre::ResourceGroupManager::getSingleton().getResourceGroups();
      Ogre::StringVector::iterator itGroup = groupVector.begin();
      Ogre::StringVector::iterator itGroupEnd = groupVector.end();
      Ogre::String shaderCoreLibsPath;
      Ogre::String shaderCachePath;
			
      for (; itGroup != itGroupEnd; ++itGroup){
	Ogre::ResourceGroupManager::LocationList resLocationsList = Ogre::ResourceGroupManager::getSingleton().getResourceLocationList(*itGroup);
	Ogre::ResourceGroupManager::LocationList::iterator it = resLocationsList.begin();
	Ogre::ResourceGroupManager::LocationList::iterator itEnd = resLocationsList.end();
	bool coreLibsFound = false;

	// Try to find the location of the core shader lib functions and use it
	// as shader cache path as well - this will reduce the number of generated files
	// when running from different directories.
	for (; it != itEnd; ++it){
	  if ((*it)->archive->getName().find("RTShaderLib") != Ogre::String::npos)
	    {
	      shaderCoreLibsPath = (*it)->archive->getName() + "/cache/";
	      shaderCachePath = shaderCoreLibsPath;
	      coreLibsFound = true;
	      break;
	    }
	}
	// Core libs path found in the current group.
	if (coreLibsFound) 
	  break; 
      }

      // Core shader libs not found -> shader generating will fail.
      if (shaderCoreLibsPath.empty())			
	return false;			
								
# ifdef _RTSS_WRITE_SHADERS_TO_DISK
      // Set shader cache path.
#  if OGRE_PLATFORM == OGRE_PLATFORM_APPLE_IOS
      shaderCachePath = Ogre::macCachePath();
#  elif OGRE_PLATFORM == OGRE_PLATFORM_APPLE
      shaderCachePath = Ogre::macCachePath() + "/org.ogre3d.RTShaderCache";
#  endif
      AuraLog::info("Setting shader cache dir :)");
      mShaderGenerator->setShaderCachePath(shaderCachePath);		
# endif
#endif
      // Create and register the material manager listener if it doesn't exist yet.
      if (mMaterialMgrListener == NULL) {
	mMaterialMgrListener = new ShaderGeneratorTechniqueResolverListener(mShaderGenerator);
	Ogre::MaterialManager::getSingleton().addListener(mMaterialMgrListener);
      }
    }
    return true;
  }

  /*-----------------------------------------------------------------------------
    | Finalize the RT Shader system.	
    -----------------------------------------------------------------------------*/
  void ShaderController::finalizeRTShaderSystem() {
    // Restore default scheme.
    Ogre::MaterialManager::getSingleton().setActiveScheme(Ogre::MaterialManager::DEFAULT_SCHEME_NAME);

    // Unregister the material manager listener.
    if (mMaterialMgrListener != NULL) {			
      Ogre::MaterialManager::getSingleton().removeListener(mMaterialMgrListener);
      delete mMaterialMgrListener;
      mMaterialMgrListener = NULL;
    }

    // Finalize RTShader system.
    if (mShaderGenerator != NULL){				
      Ogre::RTShader::ShaderGenerator::finalize();
      mShaderGenerator = NULL;
    }
  }


  void ShaderController::locateShaderResources(){
    Ogre::String sec, type, arch;

    sec = "General";

#if OGRE_PLATFORM == OGRE_PLATFORM_APPLE
    arch = Ogre::macBundlePath() + "/Contents/Resources/";
    type = "FileSystem";
#elif OGRE_PLATFORM == OGRE_PLATFORM_APPLE_IOS
    arch = Ogre::macBundlePath() + "/";
    type = "FileSystem";
#elif OGRE_PLATFORM == OGRE_PLATFORM_ANDROID
    arch = "/";
    type = "APKFileSystem";
#endif
    
#ifdef USE_RTSHADER_SYSTEM
    if(Ogre::GpuProgramManager::getSingleton().isSyntaxSupported("glsles")) {
      Ogre::ResourceGroupManager::getSingleton().addResourceLocation(arch + "RTShaderLib/GLSLES", type, sec);
    }else if(Ogre::GpuProgramManager::getSingleton().isSyntaxSupported("glsl")){
      Ogre::ResourceGroupManager::getSingleton().addResourceLocation(arch + "RTShaderLib/GLSL", type, sec);
      if(Ogre::GpuProgramManager::getSingleton().isSyntaxSupported("glsl150")) {
	Ogre::ResourceGroupManager::getSingleton().addResourceLocation(arch + "RTShaderLib/GLSL150", type, sec);
      }
    }else if(Ogre::GpuProgramManager::getSingleton().isSyntaxSupported("hlsl")){
      Ogre::ResourceGroupManager::getSingleton().addResourceLocation(arch + "RTShaderLib/HLSL", type, sec);
    }
# ifdef OGRE_BUILD_PLUGIN_CG
    Ogre::ResourceGroupManager::getSingleton().addResourceLocation(arch + "RTShaderLib/Cg", type, sec);
# endif
#endif /* USE_RTSHADER_SYSTEM */
  }

  Ogre::String ShaderController::getShaderCacheFileName() {
#if OGRE_DEBUG_MODE
    return "cache_d.bin";
#else
    return "cache.bin";
#endif
  }

}
