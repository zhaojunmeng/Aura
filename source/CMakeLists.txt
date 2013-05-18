# ---------------------------------------------------------
cmake_minimum_required(VERSION 2.6)

#SET(CMAKE_SUPPRESS_REGENERATION  1)
#SET(CMAKE_USE_RELATIVE_PATHS 1)
#SET(INTERNAL_CREATE_DISTRIBUTABLE_MSVC_PROJECTFILES 1)



project(AURA)
SET(AURA 1.0)
set(AURA TRUE)

if(COMMAND cmake_policy)
   cmake_policy(SET CMP0003 NEW)
endif(COMMAND cmake_policy)

set(CMAKE_MODULE_PATH
  "${AURA_SOURCE_DIR}/CMake"
  "${AURA_SOURCE_DIR}/CMake/Utils"
  "${AURA_SOURCE_DIR}/CMake/Packages"
)

# Include necessary submodules

include(CMakeDependentOption)
include(CheckCXXCompilerFlag)
include(MacroLogFeature)
include(PreprocessorUtils)


# Ogre
subdirs(Ogre-1.9a)



# Engine
#subdirs(Engine)

# Some variables to build the apps
set(OGRE_TEMPLATES_DIR "${CMAKE_CURRENT_SOURCE_DIR}/CMake/Templates")
set(AURA_SOURCE_FILE ${CMAKE_CURRENT_SOURCE_DIR})

# Engine configuration
set (AURA_HEADER_FILES
  #include/SampleBrowser.h
  #${OGRE_SOURCE_DIR}/Samples/Common/include/Sample.h
  #${OGRE_SOURCE_DIR}/Samples/Common/include/SampleContext.h
  #${OGRE_SOURCE_DIR}/Samples/Common/include/SamplePlugin.h
  #${OGRE_SOURCE_DIR}/Samples/Common/include/SdkCameraMan.h
  #${OGRE_SOURCE_DIR}/Samples/Common/include/SdkSample.h
  #${OGRE_SOURCE_DIR}/Samples/Common/include/SdkTrays.h
  #${OGRE_SOURCE_DIR}/Samples/Common/include/OgreStaticPluginLoader.h
  ${AURA_SOURCE_DIR}/Engine/AuraApplication.h	
  )

set(AURA_SOURCE_FILES 
#  main.cpp
)

# Get the list of configured samples
# get_property(OGRE_SAMPLES_LIST GLOBAL PROPERTY "OGRE_SAMPLES_LIST")

if (OGRE_BUILD_PLATFORM_APPLE_IOS)
  set_source_files_properties(${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp PROPERTIES COMPILE_FLAGS "-x objective-c++")

  #if(OGRE_BUILD_RENDERSYSTEM_GLES AND NOT OGRE_BUILD_RENDERSYSTEM_GLES2)
  #  list(REMOVE_ITEM OGRE_SAMPLES_LIST Sample_BSP Sample_Compositor Sample_CelShading Sample_CubeMapping Sample_Dot3Bump Sample_Fresnel Sample_Instancing Sample_Lighting Sample_ShaderSystem Sample_ShaderSystemTexturedFog Sample_ShaderSystemMultiLight Sample_VolumeTex Sample_Water)
  #endif()

  #if(NOT OGRE_BUILD_COMPONENT_TERRAIN AND NOT OGRE_SDK_BUILD)
  #  list(REMOVE_ITEM OGRE_SAMPLES_LIST Sample_Terrain)
  #  list(REMOVE_ITEM OGRE_SAMPLES_LIST Sample_EndlessWorld)
  #endif()

  #if(NOT OGRE_BUILD_COMPONENT_RTSHADERSYSTEM AND NOT OGRE_SDK_BUILD)
  #  list(REMOVE_ITEM OGRE_SAMPLES_LIST Sample_ShaderSystem)
  #  list(REMOVE_ITEM OGRE_SAMPLES_LIST Sample_ShaderSystemMultiLight)
  #  list(REMOVE_ITEM OGRE_SAMPLES_LIST Sample_ShaderSystemTexturedFog)
  #endif()
endif ()

# Platform specific headers
if (APPLE AND OGRE_BUILD_PLATFORM_APPLE_IOS)
  set(AURA_HEADER_FILES ${HEADER_FILES}
    ${AURA_SOURCE_DIR}/Engine/AuraApplication_iOS.h
    )
elseif (OGRE_BUILD_PLATFORM_NACL)
  set(AURA_HEADER_FILES ${HEADER_FILES}
    ${AURA_SOURCE_DIR}/Engine/AuraApplication_NaCl.h
    )
else ()
  set(AURA_HEADER_FILES ${HEADER_FILES}
    ${AURA_SOURCE_DIR}/Engine/AuraApplication_OSX.h
    ${AURA_SOURCE_DIR}/Engine/misc/AuraApplication_OSX.icns
    )
endif (APPLE AND OGRE_BUILD_PLATFORM_APPLE_IOS)

if(ANDROID)
  set(AURA_HEADER_FILES ${HEADER_FILES} 
    ${AURA_SOURCE_DIR}/Engine/AuraApplication_Android.h
    )
endif(ANDROID)


# Apps
subdirs(Apps)

# Install CMake modules
add_subdirectory(${AURA_SOURCE_DIR}/CMake)