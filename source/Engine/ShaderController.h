#ifndef _ShaderController_H_
#define _ShaderController_H_

#include "Ogre.h"
#include "OgreRTShaderSystem.h"
#include "ShaderGeneratorTechniqueResolverListener.h"
// Remove the comment below in order to make the RTSS use valid path for writing down the generated shaders.
// If cache path is not set - all shaders are generated to system memory.
//#define _RTSS_WRITE_SHADERS_TO_DISK

namespace Aura{

  class ShaderController{

  public:
    ShaderController(Ogre::FileSystemLayer* fsLayer);

    void init();
    void shutdown();

    bool initializeRTShaderSystem(Ogre::SceneManager* sceneMgr);
    void finalizeRTShaderSystem();

    virtual void locateShaderResources();
    Ogre::String getShaderCacheFileName();

  private:
    Ogre::RTShader::ShaderGenerator* mShaderGenerator;      	// The Shader generator instance.
    ShaderGeneratorTechniqueResolverListener*	mMaterialMgrListener;		// Shader generator material manager listener.	
    Ogre::FileSystemLayer* mFSLayer;
  };




  
} //Aura

#endif
