# ---------------------------------------------------------
cmake_minimum_required(VERSION 2.6)

#SET(CMAKE_SUPPRESS_REGENERATION  1)
#SET(CMAKE_USE_RELATIVE_PATHS 1)
#SET(INTERNAL_CREATE_DISTRIBUTABLE_MSVC_PROJECTFILES 1)

set(CMAKE_XCODE_EFFECTIVE_PLATFORMS "-iphoneos;-iphonesimulator")

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
include(OgreAddTargets)
include(PreprocessorUtils)


# Include ogre directories and other dependencies directories :)
# Configure Apps build
include(OgreConfigTargets)

# Include directories :)
include_directories(${AURA_SOURCE_DIR}/Ogre-1.9a/OgreMain/include)
include_directories(${AURA_SOURCE_DIR}/Engine)
include_directories(${AURA_SOURCE_DIR}/Engine/IOS)
include_directories(${AURA_SOURCE_DIR}/vuforia-2.0/include)
include_directories(${AURA_SOURCE_DIR}/cricket-1.0.31/inc)
include_directories(${AURA_SOURCE_DIR}/Dependencies/iosDependencies/include)

# Set dependencies dir
set(AURA_DEPENDENCIES_DIR ${AURA_SOURCE_DIR}/Dependencies/iOSDependencies/lib/)

# Make sure all plugins are built
# Configure the PLUGINS in APPS_DEPENDENCIES
if (OGRE_BUILD_PLUGIN_OCTREE)
#  set(APPS_DEPENDENCIES ${APPS_DEPENDENCIES} Plugin_OctreeSceneManager)
  set(APPS_DEPENDENCIES_LIBS ${APPS_DEPENDENCIES_LIBS} -lPlugin_OctreeSceneManagerStatic)
endif ()
if (OGRE_BUILD_PLUGIN_BSP)
#  set(APPS_DEPENDENCIES ${APPS_DEPENDENCIES} Plugin_BSPSceneManager)
  set(APPS_DEPENDENCIES_LIBS ${APPS_DEPENDENCIES_LIBS} -lPlugin_BSPSceneManagerStatic)
endif ()
if (OGRE_BUILD_PLUGIN_CG)
#  set(APPS_DEPENDENCIES ${APPS_DEPENDENCIES} Plugin_CgProgramManager)
  set(APPS_DEPENDENCIES_LIBS ${APPS_DEPENDENCIES_LIBS} -lPlugin_CgProgramManagerStatic)
endif (OGRE_BUILD_PLUGIN_CG)
if (OGRE_BUILD_PLUGIN_PFX)
#  set(APPS_DEPENDENCIES ${APPS_DEPENDENCIES} Plugin_ParticleFX)
  set(APPS_DEPENDENCIES_LIBS ${APPS_DEPENDENCIES_LIBS} -lPlugin_ParticleFXStatic)
endif ()
if (OGRE_BUILD_PLUGIN_PCZ)
 # set(APPS_DEPENDENCIES ${APPS_DEPENDENCIES} Plugin_PCZSceneManager)
 # set(APPS_DEPENDENCIES ${APPS_DEPENDENCIES} Plugin_OctreeZone)
  set(APPS_DEPENDENCIES_LIBS ${APPS_DEPENDENCIES_LIBS} -lPlugin_PCZSceneManagerStatic)
  set(APPS_DEPENDENCIES_LIBS ${APPS_DEPENDENCIES_LIBS} -lPlugin_OctreeZoneStatic)
endif ()

if (OGRE_BUILD_COMPONENT_RTSHADERSYSTEM)	
  #set(AURA_LIBRARIES ${AURA_LIBRARIES} OgreRTShaderSystem)
  set(APPS_DEPENDENCIES_LIBS ${APPS_DEPENDENCIES_LIBS} -lOgreRTShaderSystemStatic)
endif () 
if (OGRE_BUILD_COMPONENT_OVERLAY)	
  set(APPS_DEPENDENCIES_LIBS ${APPS_DEPENDENCIES_LIBS} -lOgreOverlayStatic)
endif () 

if (OGRE_BUILD_RENDERSYSTEM_GL)
  #set(APPS_DEPENDENCIES ${APPS_DEPENDENCIES} RenderSystem_GL)
  set(APPS_DEPENDENCIES_LIBS ${APPS_DEPENDENCIES_LIBS} -lRenderSystem_GLStatic)
endif ()
if (OGRE_BUILD_RENDERSYSTEM_GL3PLUS)
  #set(APPS_DEPENDENCIES ${APPS_DEPENDENCIES} RenderSystem_GL3Plus)
  set(APPS_DEPENDENCIES_LIBS ${APPS_DEPENDENCIES_LIBS} -lRenderSystem_GL3PlusStatic)
endif ()
if (OGRE_BUILD_RENDERSYSTEM_GLES)
  #set(APPS_DEPENDENCIES ${APPS_DEPENDENCIES} RenderSystem_GLES)
  set(APPS_DEPENDENCIES_LIBS ${APPS_DEPENDENCIES_LIBS} -lRenderSystem_GLESStatic)
endif ()
if (OGRE_BUILD_RENDERSYSTEM_GLES2)
  #set(APPS_DEPENDENCIES ${APPS_DEPENDENCIES} RenderSystem_GLES2)
  set(APPS_DEPENDENCIES_LIBS ${APPS_DEPENDENCIES_LIBS} -lRenderSystem_GLES2Static)
endif ()


if (APPLE)
  if (OGRE_BUILD_PLATFORM_APPLE_IOS)
    set(AURA_LIBRARIES ${AURA_LIBRARIES})
    include_directories("${AURA_SOURCE_DIR}/Ogre-1.9a/OgreMain/include/iOS")
  #else ()
  #  set(AURA_LIBRARIES ${AURA_LIBRARIES} IOKit)
  endif (OGRE_BUILD_PLATFORM_APPLE_IOS)
endif ()

# Last but not least, Ogre Main static :)
#set(APPS_DEPENDENCIES ${APPS_DEPENDENCIES} OgreMainStatic)
set(APPS_DEPENDENCIES_LIBS ${APPS_DEPENDENCIES_LIBS} -lOgreMainStatic)




# Static linking means we need to directly use plugins
include_directories(${AURA_SOURCE_DIR}/Ogre-1.9a/PlugIns/BSPSceneManager/include)
include_directories(${AURA_SOURCE_DIR}/Ogre-1.9a/PlugIns/CgProgramManager/include)
include_directories(${AURA_SOURCE_DIR}/Ogre-1.9a/PlugIns/OctreeSceneManager/include)
include_directories(${AURA_SOURCE_DIR}/Ogre-1.9a/PlugIns/OctreeZone/include)
include_directories(${AURA_SOURCE_DIR}/Ogre-1.9a/PlugIns/ParticleFX/include)
include_directories(${AURA_SOURCE_DIR}/Ogre-1.9a/PlugIns/PCZSceneManager/include)
include_directories(${AURA_SOURCE_DIR}/Ogre-1.9a/Components/Overlay/include)
include_directories(${AURA_SOURCE_DIR}/Ogre-1.9a/Components/RTShaderSystem/include)
include_directories(${AURA_SOURCE_DIR}/Ogre-1.9a/RenderSystems/GLES/include)
include_directories(${AURA_SOURCE_DIR}/Ogre-1.9a/RenderSystems/GLES2/include)
include_directories(
 ${AURA_SOURCE_DIR}/Ogre-1.9a/RenderSystems/GL/include
 ${AURA_SOURCE_DIR}/Ogre-1.9a/RenderSystems/GL/src/GLSL/include
 ${AURA_SOURCE_DIR}/Ogre-1.9a/RenderSystems/GL/src/atifs/include
 ${AURA_SOURCE_DIR}/Ogre-1.9a/RenderSystems/GL/src/nvparse
)
include_directories(
 ${AURA_SOURCE_DIR}/Ogre-1.9a/RenderSystems/GL3Plus/include
 ${AURA_SOURCE_DIR}/Ogre-1.9a/RenderSystems/GL3Plus/src/GLSL/include
)


if(ANDROID)
  include_directories(${AURA_SOURCE_DIR}/Ogre-1.9a/build_android/include)
else()
  include_directories(${AURA_SOURCE_DIR}/Ogre-1.9a/build_ios/include)
endif(ANDROID)

# Link to all enabled plugins
# Link the PLUGINS and LIBRARIES
set(AURA_LIBRARIES ${AURA_LIBRARIES} ${APPS_DEPENDENCIES_LIBS} AuraEngine)

# Config the render system
#if (OGRE_BUILD_RENDERSYSTEM_GLES)
#  set(FLAG_RENDERSYSTEM "-DUSE_OPENGL_ES_1_1=1")
#endif ()
#if (OGRE_BUILD_RENDERSYSTEM_GLES2)
#  set(FLAG_RENDERSYSTEM "-DUSE_OPENGL_ES_2_0=1")
#gendif ()

# Ogre
# subdirs(Ogre-1.9a)

# Engine
subdirs(Engine)

# Some variables to build the apps
set(OGRE_TEMPLATES_DIR "${CMAKE_CURRENT_SOURCE_DIR}/CMake/Templates")

#if (OGRE_BUILD_PLATFORM_APPLE_IOS)
  #set_source_files_properties(${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp PROPERTIES COMPILE_FLAGS "-x objective-c++")
#endif ()

# Apps
subdirs(Apps)

# Install CMake modules
#add_subdirectory(${AURA_SOURCE_DIR}/CMake)
