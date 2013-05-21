#ifndef _SHADERGENERATORTECHNIQUERESOLVERLISTENER_H_
#define _SHADERGENERATORTECHNIQUERESOLVERLISTENER_H_

#include "OgreRTShaderSystem.h"
// Remove the comment below in order to make the RTSS use valid path for writing down the generated shaders.
// If cache path is not set - all shaders are generated to system memory.
//#define _RTSS_WRITE_SHADERS_TO_DISK

/** This class demonstrates basic usage of the RTShader system.
    It sub class the material manager listener class and when a target scheme callback
    is invoked with the shader generator scheme it tries to create an equivalent shader
    based technique based on the default technique of the given material.
*/


namespace Aura{

  class ShaderGeneratorTechniqueResolverListener : public Ogre::MaterialManager::Listener
    {
    public:

      ShaderGeneratorTechniqueResolverListener(Ogre::RTShader::ShaderGenerator* pShaderGenerator)
	{
	  mShaderGenerator = pShaderGenerator;			
	}

      /** This is the hook point where shader based technique will be created.
	  It will be called whenever the material manager won't find appropriate technique
	  that satisfy the target scheme name. If the scheme name is out target RT Shader System
	  scheme name we will try to create shader generated technique for it. 
      */
      virtual Ogre::Technique* handleSchemeNotFound(unsigned short schemeIndex, 
						    const Ogre::String& schemeName, Ogre::Material* originalMaterial, unsigned short lodIndex, 
						    const Ogre::Renderable* rend)
	{	
	  Ogre::Technique* generatedTech = NULL;

	  // Case this is the default shader generator scheme.
	  if (schemeName == Ogre::RTShader::ShaderGenerator::DEFAULT_SCHEME_NAME)
	    {
	      bool techniqueCreated;

	      // Create shader generated technique for this material.
	      techniqueCreated = mShaderGenerator->createShaderBasedTechnique(
									      originalMaterial->getName(), 
									      Ogre::MaterialManager::DEFAULT_SCHEME_NAME, 
									      schemeName);	

	      // Case technique registration succeeded.
	      if (techniqueCreated)
		{
		  // Force creating the shaders for the generated technique.
		  mShaderGenerator->validateMaterial(schemeName, originalMaterial->getName());
				
		  // Grab the generated technique.
		  Ogre::Material::TechniqueIterator itTech = originalMaterial->getTechniqueIterator();

		  while (itTech.hasMoreElements())
		    {
		      Ogre::Technique* curTech = itTech.getNext();

		      if (curTech->getSchemeName() == schemeName)
			{
			  generatedTech = curTech;
			  break;
			}
		    }				
		}
	    }

	  return generatedTech;
	}

    protected:	
      Ogre::RTShader::ShaderGenerator*	mShaderGenerator;			// The shader generator instance.		
    };


  class ShaderController{

  public:
    ShaderController(Ogre::FileSystemLayer* fsLayer){
      mFSLayer = fsLayer;
      mMaterialMgrListener = NULL;
      mShaderGenerator = NULL;		
    }


    void init(){
#if defined(ENABLE_SHADERS_CACHE_LOAD)
      // Load for a package version of the shaders.
      Ogre::String path = getShaderCacheFileName();
      FILE * inFile = NULL;
      inFile = fopen(path.c_str(), "rb");
      // If that does not exist, see if there is a version in the writable location.
      if (!inFile)
	{
	  path = mFSLayer->getWritablePath(getShaderCacheFileName());
	  inFile = fopen(path.c_str(), "rb");
	}
      if (inFile)
	{
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
      if (!success) 
	{
	  OGRE_EXCEPT(Ogre::Exception::ERR_FILE_NOT_FOUND, 
		      "Shader Generator Initialization failed - Core shader libs path not found", 
		      "AuraApplication");
	}

      if(mRoot.getRenderSystem()->getCapabilities()->hasCapability(Ogre::RSC_FIXED_FUNCTION) == false)
      	{
	  // creates shaders for base material BaseWhite using the RTSS
	  Ogre::MaterialPtr baseWhite = Ogre::MaterialManager::getSingleton().getByName("BaseWhite", Ogre::ResourceGroupManager::INTERNAL_RESOURCE_GROUP_NAME);
	  baseWhite->setLightingEnabled(false);
	  mShaderGenerator->createShaderBasedTechnique(
						       "BaseWhite",
						       Ogre::MaterialManager::DEFAULT_SCHEME_NAME,
						       Ogre::RTShader::ShaderGenerator::DEFAULT_SCHEME_NAME);
	  mShaderGenerator->validateMaterial(Ogre::RTShader::ShaderGenerator::DEFAULT_SCHEME_NAME,
					     "BaseWhite");
	  if(baseWhite->getNumTechniques() > 1)
	    {
	      baseWhite->getTechnique(0)->getPass(0)->setVertexProgram(
								       baseWhite->getTechnique(1)->getPass(0)->getVertexProgram()->getName());
	      baseWhite->getTechnique(0)->getPass(0)->setFragmentProgram(
									 baseWhite->getTechnique(1)->getPass(0)->getFragmentProgram()->getName());
	    }

	  // creates shaders for base material BaseWhiteNoLighting using the RTSS
	  mShaderGenerator->createShaderBasedTechnique(
						       "BaseWhiteNoLighting",
						       Ogre::MaterialManager::DEFAULT_SCHEME_NAME,
						       Ogre::RTShader::ShaderGenerator::DEFAULT_SCHEME_NAME);
	  mShaderGenerator->validateMaterial(Ogre::RTShader::ShaderGenerator::DEFAULT_SCHEME_NAME,
					     "BaseWhiteNoLighting");
	  Ogre::MaterialPtr baseWhiteNoLighting = Ogre::MaterialManager::getSingleton().getByName("BaseWhiteNoLighting", Ogre::ResourceGroupManager::INTERNAL_RESOURCE_GROUP_NAME);
	  if(baseWhite->getNumTechniques() > 1)
	    {
	      baseWhiteNoLighting->getTechnique(0)->getPass(0)->setVertexProgram(
										 baseWhiteNoLighting->getTechnique(1)->getPass(0)->getVertexProgram()->getName());
	      baseWhiteNoLighting->getTechnique(0)->getPass(0)->setFragmentProgram(
										   baseWhiteNoLighting->getTechnique(1)->getPass(0)->getFragmentProgram()->getName());
	    }
      	 }

      if(mRoot.getRenderSystem()->getCapabilities()->hasCapability(Ogre::RSC_FIXED_FUNCTION) == false)
      	{
       Ogre::RTShader::ShaderGenerator::getSingletonPtr()->addSceneManager(mSceneManager);
      	}
    }


    void shutdown(){
#if defined(ENABLE_SHADERS_CACHE_SAVE) 
      if (Ogre::GpuProgramManager::getSingleton().isCacheDirty())
	{
	  Ogre::String path = mFSLayer->getWritablePath(getShaderCacheFileName());
	  FILE * outFile = fopen(path.c_str(), "wb");
	  if (outFile)
	    {
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
    bool initializeRTShaderSystem(Ogre::SceneManager* sceneMgr)
    {			
      if (Ogre::RTShader::ShaderGenerator::initialize())
	{
	  mShaderGenerator = Ogre::RTShader::ShaderGenerator::getSingletonPtr();

	  mShaderGenerator->addSceneManager(sceneMgr);

#if OGRE_PLATFORM != OGRE_PLATFORM_ANDROID && OGRE_PLATFORM != OGRE_PLATFORM_WINRT
	  // Setup core libraries and shader cache path.
	  Ogre::StringVector groupVector = Ogre::ResourceGroupManager::getSingleton().getResourceGroups();
	  Ogre::StringVector::iterator itGroup = groupVector.begin();
	  Ogre::StringVector::iterator itGroupEnd = groupVector.end();
	  Ogre::String shaderCoreLibsPath;
	  Ogre::String shaderCachePath;
			
	  for (; itGroup != itGroupEnd; ++itGroup)
	    {
	      Ogre::ResourceGroupManager::LocationList resLocationsList = Ogre::ResourceGroupManager::getSingleton().getResourceLocationList(*itGroup);
	      Ogre::ResourceGroupManager::LocationList::iterator it = resLocationsList.begin();
	      Ogre::ResourceGroupManager::LocationList::iterator itEnd = resLocationsList.end();
	      bool coreLibsFound = false;

	      // Try to find the location of the core shader lib functions and use it
	      // as shader cache path as well - this will reduce the number of generated files
	      // when running from different directories.
	      for (; it != itEnd; ++it)
		{
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
								
#ifdef _RTSS_WRITE_SHADERS_TO_DISK
	  // Set shader cache path.
#if OGRE_PLATFORM == OGRE_PLATFORM_APPLE_IOS
	  shaderCachePath = Ogre::macCachePath();
#elif OGRE_PLATFORM == OGRE_PLATFORM_APPLE
	  shaderCachePath = Ogre::macCachePath() + "/org.ogre3d.RTShaderCache";
#endif
	  mShaderGenerator->setShaderCachePath(shaderCachePath);		
#endif
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
    void finalizeRTShaderSystem()
    {
      // Restore default scheme.
      Ogre::MaterialManager::getSingleton().setActiveScheme(Ogre::MaterialManager::DEFAULT_SCHEME_NAME);

      // Unregister the material manager listener.
      if (mMaterialMgrListener != NULL)
	{			
	  Ogre::MaterialManager::getSingleton().removeListener(mMaterialMgrListener);
	  delete mMaterialMgrListener;
	  mMaterialMgrListener = NULL;
	}

      // Finalize RTShader system.
      if (mShaderGenerator != NULL)
	{				
	  Ogre::RTShader::ShaderGenerator::finalize();
	  mShaderGenerator = NULL;
	}
    }


	virtual void locateShaderResources()
	{
	  Ogre::String sec, type, arch;

#	if OGRE_PLATFORM != OGRE_PLATFORM_ANDROID 
/* #		if OGRE_PLATFORM == OGRE_PLATFORM_APPLE */
/* 	  arch = Ogre::macBundlePath() + "/Contents/Resources/"; */
/* #		elif OGRE_PLATFORM == OGRE_PLATFORM_APPLE_IOS */
/* 	  arch = Ogre::macBundlePath() + "/"; */
/* #		else        */
/* 	  arch = Ogre::StringUtil::replaceAll(arch, "Media/../../Tests/Media", "");   */
/* 	  arch = Ogre::StringUtil::replaceAll(arch, "media/../../Tests/Media", "");  */
/* #		endif */
	  type = "FileSystem";
	  sec = "Popular";

	  // Add locations for supported shader languages
	  if(Ogre::GpuProgramManager::getSingleton().isSyntaxSupported("glsles"))
            {
	      Ogre::ResourceGroupManager::getSingleton().addResourceLocation(arch + "materials/programs/GLSLES", type, sec);
            }
	  else if(Ogre::GpuProgramManager::getSingleton().isSyntaxSupported("glsl"))
            {
	      if(Ogre::GpuProgramManager::getSingleton().isSyntaxSupported("glsl150"))
                {
		  Ogre::ResourceGroupManager::getSingleton().addResourceLocation(arch + "materials/programs/GLSL150", type, sec);
                }
	      else
                {
		  Ogre::ResourceGroupManager::getSingleton().addResourceLocation(arch + "materials/programs/GLSL", type, sec);
                }

	      if(Ogre::GpuProgramManager::getSingleton().isSyntaxSupported("glsl400"))
                {
		  Ogre::ResourceGroupManager::getSingleton().addResourceLocation(arch + "materials/programs/GLSL400", type, sec);
                }
            }
	  else if(Ogre::GpuProgramManager::getSingleton().isSyntaxSupported("hlsl"))
            {
	      Ogre::ResourceGroupManager::getSingleton().addResourceLocation(arch + "materials/programs/HLSL", type, sec);
            }
#		ifdef OGRE_BUILD_PLUGIN_CG
	  Ogre::ResourceGroupManager::getSingleton().addResourceLocation(arch + "materials/programs/Cg", type, sec);
#		endif

#		ifdef USE_RTSHADER_SYSTEM
	  if(Ogre::GpuProgramManager::getSingleton().isSyntaxSupported("glsles"))
            {
	      Ogre::ResourceGroupManager::getSingleton().addResourceLocation(arch + "RTShaderLib/GLSLES", type, sec);
            }
	  else if(Ogre::GpuProgramManager::getSingleton().isSyntaxSupported("glsl"))
            {
	      Ogre::ResourceGroupManager::getSingleton().addResourceLocation(arch + "RTShaderLib/GLSL", type, sec);
	      if(Ogre::GpuProgramManager::getSingleton().isSyntaxSupported("glsl150"))
                {
		  Ogre::ResourceGroupManager::getSingleton().addResourceLocation(arch + "RTShaderLib/GLSL150", type, sec);
                }
            }
	  else if(Ogre::GpuProgramManager::getSingleton().isSyntaxSupported("hlsl"))
            {
	      Ogre::ResourceGroupManager::getSingleton().addResourceLocation(arch + "RTShaderLib/HLSL", type, sec);
            }
#			ifdef OGRE_BUILD_PLUGIN_CG
	  Ogre::ResourceGroupManager::getSingleton().addResourceLocation(arch + "RTShaderLib/Cg", type, sec);
#			endif
#		endif /* USE_RTSHADER_SYSTEM */
#	endif /* OGRE_PLATFORM != OGRE_PLATFORM_ANDROID */
	}




    Ogre::String getShaderCacheFileName()
      {
#if OGRE_DEBUG_MODE
	return "cache_d.bin";
#else
	return "cache.bin";
#endif
      }

  private:
    Ogre::RTShader::ShaderGenerator* mShaderGenerator;      	// The Shader generator instance.
    ShaderGeneratorTechniqueResolverListener*	mMaterialMgrListener;		// Shader generator material manager listener.	
    Ogre::FileSystemLayer* mFSLayer;
  };

} //Aura

#endif
