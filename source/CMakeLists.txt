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
 if(CMAKE_BUILD_TYPE STREQUAL "Release")
  set(OGRE_LIBS ${OGRE_LIBS} -lPlugin_OctreeSceneManagerStatic)
 else()
  set(OGRE_LIBS ${OGRE_LIBS} -lPlugin_OctreeSceneManagerStatic_d)
 endif()
endif ()

if (OGRE_BUILD_PLUGIN_BSP)
 if(CMAKE_BUILD_TYPE STREQUAL "Release")
  set(OGRE_LIBS ${OGRE_LIBS} -lPlugin_BSPSceneManagerStatic)
 else()
   set(OGRE_LIBS ${OGRE_LIBS} -lPlugin_BSPSceneManagerStatic_d)
 endif()
endif ()

if (OGRE_BUILD_PLUGIN_PFX)
 if(CMAKE_BUILD_TYPE STREQUAL "Release")
  set(OGRE_LIBS ${OGRE_LIBS} -lPlugin_ParticleFXStatic)
 else()
   set(OGRE_LIBS ${OGRE_LIBS} -lPlugin_ParticleFXStatic_d)
 endif()
endif()

#if (OGRE_BUILD_PLUGIN_PCZ)
#  # set(APPS_DEPENDENCIES ${APPS_DEPENDENCIES} Plugin_PCZSceneManager)
#  # set(APPS_DEPENDENCIES ${APPS_DEPENDENCIES} Plugin_OctreeZone)
#  set(OGRE_LIBS ${OGRE_LIBS} -lPlugin_PCZSceneManagerStatic)
#  set(OGRE_LIBS ${OGRE_LIBS} -lPlugin_OctreeZoneStatic)
#endif ()

if (OGRE_BUILD_COMPONENT_RTSHADERSYSTEM)
 if(CMAKE_BUILD_TYPE STREQUAL "Release")	
  set(OGRE_LIBS ${OGRE_LIBS} -lOgreRTShaderSystemStatic)
 else()
   set(OGRE_LIBS ${OGRE_LIBS} -lOgreRTShaderSystemStatic_d)
 endif()
endif() 

if (OGRE_BUILD_COMPONENT_OVERLAY)	
 if(CMAKE_BUILD_TYPE STREQUAL "Release")	
  set(OGRE_LIBS ${OGRE_LIBS} -lOgreOverlayStatic)
 else()
  set(OGRE_LIBS ${OGRE_LIBS} -lOgreOverlayStatic_d)
 endif()
endif() 

if (OGRE_BUILD_RENDERSYSTEM_GL)
 if(CMAKE_BUILD_TYPE STREQUAL "Release")	
  set(OGRE_LIBS ${OGRE_LIBS} -lRenderSystem_GLStatic)
 else()
   set(OGRE_LIBS ${OGRE_LIBS} -lRenderSystem_GLStatic_d)
 endif()
endif()

if (OGRE_BUILD_RENDERSYSTEM_GL3PLUS)
 if(CMAKE_BUILD_TYPE STREQUAL "Release")	
  set(OGRE_LIBS ${OGRE_LIBS} -lRenderSystem_GL3PlusStatic)
 else()
  set(OGRE_LIBS ${OGRE_LIBS} -lRenderSystem_GL3PlusStatic_d)
 endif()
endif()

if(OGRE_BUILD_RENDERSYSTEM_GLES)
 if(CMAKE_BUILD_TYPE STREQUAL "Release")	
  set(OGRE_LIBS ${OGRE_LIBS} -lRenderSystem_GLESStatic)
 else()
   set(OGRE_LIBS ${OGRE_LIBS} -lRenderSystem_GLESStatic_d)
 endif()
endif()

if (OGRE_BUILD_RENDERSYSTEM_GLES2)
 if(CMAKE_BUILD_TYPE STREQUAL "Release")	
  set(OGRE_LIBS ${OGRE_LIBS} -lRenderSystem_GLES2Static)
 else()
   set(OGRE_LIBS ${OGRE_LIBS} -lRenderSystem_GLES2Static_d)
 endif()
endif ()

# Last but not least, Ogre Main static :)
if(CMAKE_BUILD_TYPE STREQUAL "Release")
 set(OGRE_LIBS ${OGRE_LIBS} -lOgreMainStatic)
else()
 set(OGRE_LIBS ${OGRE_LIBS} -lOgreMainStatic_d)
endif()

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

if (APPLE)
  if (OGRE_BUILD_PLATFORM_APPLE_IOS)
    set(AURA_LIBRARIES ${AURA_LIBRARIES})
    include_directories("${AURA_SOURCE_DIR}/Ogre-1.9a/OgreMain/include/iOS")
  endif (OGRE_BUILD_PLATFORM_APPLE_IOS)
endif ()

if(ANDROID)
  #include_directories(${AURA_SOURCE_DIR}/Ogre-1.9a/build_android/include)
else()
  include_directories(${AURA_SOURCE_DIR}/Ogre-1.9a/build_ios/include)
endif(ANDROID)

# Link to all enabled plugins
# Link the PLUGINS and LIBRARIES
set(AURA_LIBRARIES ${AURA_LIBRARIES} ${OGRE_LIBS} AuraEngine)

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
