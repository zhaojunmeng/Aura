# Configure Apps build
include(OgreConfigTargets)


#include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Common/include)
include_directories(${OGRE_SOURCE_DIR}/OgreMain/include)
include_directories(${OGRE_BINARY_DIR}/include)
include_directories(${AURA_SOURCE_DIR}/Engine)

# Make sure all plugins are built
if (OGRE_BUILD_PLUGIN_OCTREE)
  set(APPS_DEPENDENCIES ${APPS_DEPENDENCIES} Plugin_OctreeSceneManager)
endif ()
if (OGRE_BUILD_PLUGIN_BSP)
  set(APPS_DEPENDENCIES ${APPS_DEPENDENCIES} Plugin_BSPSceneManager)
endif ()
if (OGRE_BUILD_PLUGIN_CG)
  set(APPS_DEPENDENCIES ${APPS_DEPENDENCIES} Plugin_CgProgramManager)
endif (OGRE_BUILD_PLUGIN_CG)
if (OGRE_BUILD_PLUGIN_PFX)
  set(APPS_DEPENDENCIES ${APPS_DEPENDENCIES} Plugin_ParticleFX)
endif ()

if (OGRE_BUILD_PLUGIN_PCZ)
  set(APPS_DEPENDENCIES ${APPS_DEPENDENCIES} Plugin_PCZSceneManager)
  set(APPS_DEPENDENCIES ${APPS_DEPENDENCIES} Plugin_OctreeZone)
endif ()

if (OGRE_BUILD_COMPONENT_RTSHADERSYSTEM)
  add_definitions(-DUSE_RTSHADER_SYSTEM)
  ogre_add_component_include_dir(RTShaderSystem)
  set(APPS_DEPENDENCIES ${APPS_DEPENDENCIES} OgreRTShaderSystem)
endif ()

if (OGRE_BUILD_COMPONENT_OVERLAY)
  ogre_add_component_include_dir(Overlay)
  set(APPS_DEPENDENCIES ${APPS_DEPENDENCIES} OgreOverlay)
endif ()

if (OGRE_BUILD_COMPONENT_TERRAIN)
  set(APPS_DEPENDENCIES ${APPS_DEPENDENCIES} OgreTerrain)
endif ()

if (OGRE_BUILD_COMPONENT_VOLUME)
  set(APPS_DEPENDENCIES ${APPS_DEPENDENCIES} OgreVolume)
endif ()

if (OGRE_BUILD_RENDERSYSTEM_D3D9)
  set(APPS_DEPENDENCIES ${APPS_DEPENDENCIES} RenderSystem_Direct3D9)
endif ()
if (OGRE_BUILD_RENDERSYSTEM_D3D11)
  set(APPS_DEPENDENCIES ${APPS_DEPENDENCIES} RenderSystem_Direct3D11)
endif ()
if (OGRE_BUILD_RENDERSYSTEM_GL)
  set(APPS_DEPENDENCIES ${APPS_DEPENDENCIES} RenderSystem_GL)
endif ()
if (OGRE_BUILD_RENDERSYSTEM_GL3PLUS)
  set(APPS_DEPENDENCIES ${APPS_DEPENDENCIES} RenderSystem_GL3Plus)
endif ()
if (OGRE_BUILD_RENDERSYSTEM_GLES)
  set(APPS_DEPENDENCIES ${APPS_DEPENDENCIES} RenderSystem_GLES)
endif ()
if (OGRE_BUILD_RENDERSYSTEM_GLES2)
  set(APPS_DEPENDENCIES ${APPS_DEPENDENCIES} RenderSystem_GLES2)
endif ()
if (APPLE)
  if (OGRE_BUILD_PLATFORM_APPLE_IOS)
    set(OGRE_LIBRARIES ${OGRE_LIBRARIES})
  else ()
    set(OGRE_LIBRARIES ${OGRE_LIBRARIES} IOKit)
  endif ()
endif ()

if (OGRE_STATIC)
  # Static linking means we need to directly use plugins
  include_directories(${OGRE_SOURCE_DIR}/PlugIns/BSPSceneManager/include)
  include_directories(${OGRE_SOURCE_DIR}/PlugIns/CgProgramManager/include)
  include_directories(${OGRE_SOURCE_DIR}/PlugIns/OctreeSceneManager/include)
  include_directories(${OGRE_SOURCE_DIR}/PlugIns/OctreeZone/include)
  include_directories(${OGRE_SOURCE_DIR}/PlugIns/ParticleFX/include)
  include_directories(${OGRE_SOURCE_DIR}/PlugIns/PCZSceneManager/include)
  include_directories(${OGRE_SOURCE_DIR}/RenderSystems/Direct3D9/include)
  include_directories(${OGRE_SOURCE_DIR}/RenderSystems/Direct3D11/include)
  include_directories(${OGRE_SOURCE_DIR}/RenderSystems/GLES/include)
  include_directories(${OGRE_SOURCE_DIR}/RenderSystems/GLES2/include)
  include_directories(
    ${OGRE_SOURCE_DIR}/RenderSystems/GL/include
    ${OGRE_SOURCE_DIR}/RenderSystems/GL/src/GLSL/include
    ${OGRE_SOURCE_DIR}/RenderSystems/GL/src/atifs/include
    ${OGRE_SOURCE_DIR}/RenderSystems/GL/src/nvparse
    )
  include_directories(
    ${OGRE_SOURCE_DIR}/RenderSystems/GL3Plus/include
    ${OGRE_SOURCE_DIR}/RenderSystems/GL3Plus/src/GLSL/include
    )

  # Link to all enabled plugins
  set(OGRE_LIBRARIES ${OGRE_LIBRARIES} ${APPS_DEPENDENCIES})

  # Need to include resource files so that icons are linked
  if (WIN32)
    set(AURA_RESOURCE_FILES
      ${OGRE_SOURCE_DIR}/OgreMain/src/WIN32/resource.h
      ${OGRE_SOURCE_DIR}/OgreMain/src/WIN32/OgreWin32Resources.rc
      ${OGRE_SOURCE_DIR}/OgreMain/src/WIN32/winres.h
      )
    source_group(Resources FILES ${AURA_RESOURCE_FILES})
  endif ()
else ()
  # Link to RT Shader System if enabled.
  if (OGRE_BUILD_COMPONENT_RTSHADERSYSTEM)	
    set(OGRE_LIBRARIES ${OGRE_LIBRARIES} OgreRTShaderSystem)
  endif () 
  if (OGRE_BUILD_COMPONENT_OVERLAY)	
    set(OGRE_LIBRARIES ${OGRE_LIBRARIES} OgreOverlay)
  endif () 
endif ()


# ADD SUBDIRECTORIES OF THE APPS :)
add_subdirectory(TestApp)

# if (NOT OGRE_BUILD_PLATFORM_WINRT)
#   # Add browser last
#   add_subdirectory(Browser)
# else ()
#   # create link to dependencies in well known place for SampleBrowserWinRT
#   if (NOT EXISTS "${OGRE_BINARY_DIR}/Dependencies" AND NOT OGRE_BINARY_DIR STREQUAL OGRE_SOURCE_DIR)
#     file(TO_NATIVE_PATH "${OGRE_BINARY_DIR}/Dependencies" OGRE_BINARY_DEPENDENCIES_DIR_NATIVE )
#     file(TO_NATIVE_PATH "${OGRE_DEPENDENCIES_DIR}" OGRE_DEPENDENCIES_DIR_NATIVE )
#     execute_process(COMMAND cmd /c mklink /J "${OGRE_BINARY_DEPENDENCIES_DIR_NATIVE}" "${OGRE_DEPENDENCIES_DIR_NATIVE}" )
#   endif ()
# endif ()