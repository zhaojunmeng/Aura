# Configure Apps build
include(OgreConfigTargets)


#include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Common/include)
include_directories(${OGRE_SOURCE_DIR}/OgreMain/include)
include_directories(${OGRE_BINARY_DIR}/include)
include_directories(${AURA_SOURCE_DIR}/Engine)

if (OGRE_BUILD_RENDERSYSTEM_GLES)
  set(FLAG_RENDERSYSTEM "-DUSE_OPENGL_ES_1_1")
endif ()
if (OGRE_BUILD_RENDERSYSTEM_GLES2)
  set(FLAG_RENDERSYSTEM "-DUSE_OPENGL_ES_2_0")
endif ()

configure_file("${OGRE_TEMPLATES_DIR}/Android.mk_engine.in" "${CMAKE_BINARY_DIR}/Android_engine.mk" @ONLY)

# Make sure all plugins are built


if (OGRE_BUILD_PLUGIN_OCTREE)
  set(APPS_DEPENDENCIES ${APPS_DEPENDENCIES} Plugin_OctreeSceneManager)
  set(APPS_DEPENDENCIES_LIBS ${APPS_DEPENDENCIES_LIBS} -lPlugin_OctreeSceneManagerStatic)
endif ()
if (OGRE_BUILD_PLUGIN_BSP)
  set(APPS_DEPENDENCIES ${APPS_DEPENDENCIES} Plugin_BSPSceneManager)
  set(APPS_DEPENDENCIES_LIBS ${APPS_DEPENDENCIES_LIBS} -lPlugin_BSPSceneManagerStatic)
endif ()
if (OGRE_BUILD_PLUGIN_CG)
  set(APPS_DEPENDENCIES ${APPS_DEPENDENCIES} Plugin_CgProgramManager)
  set(APPS_DEPENDENCIES_LIBS ${APPS_DEPENDENCIES_LIBS} -lPlugin_CgProgramManagerStatic)
endif (OGRE_BUILD_PLUGIN_CG)
if (OGRE_BUILD_PLUGIN_PFX)
  set(APPS_DEPENDENCIES ${APPS_DEPENDENCIES} Plugin_ParticleFX)
  set(APPS_DEPENDENCIES_LIBS ${APPS_DEPENDENCIES_LIBS} -lPlugin_ParticleFXStatic)
endif ()

if (OGRE_BUILD_PLUGIN_PCZ)
  set(APPS_DEPENDENCIES ${APPS_DEPENDENCIES} Plugin_PCZSceneManager)
  set(APPS_DEPENDENCIES ${APPS_DEPENDENCIES} Plugin_OctreeZone)
  set(APPS_DEPENDENCIES_LIBS ${APPS_DEPENDENCIES_LIBS} -lPlugin_PCZSceneManagerStatic)
  set(APPS_DEPENDENCIES_LIBS ${APPS_DEPENDENCIES_LIBS} -lPlugin_OctreeZoneStatic)

endif ()

if (OGRE_BUILD_COMPONENT_RTSHADERSYSTEM)
  add_definitions(-DUSE_RTSHADER_SYSTEM)
  ogre_add_component_include_dir(RTShaderSystem)
  set(APPS_DEPENDENCIES ${APPS_DEPENDENCIES} OgreRTShaderSystem)
endif ()

if (OGRE_BUILD_COMPONENT_OVERLAY)
  ogre_add_component_include_dir(Overlay)
  set(APPS_DEPENDENCIES ${APPS_DEPENDENCIES} OgreOverlay)
  set(APPS_DEPENDENCIES_LIBS ${APPS_DEPENDENCIES_LIBS} -lOgreOverlayStatic)
endif ()

if (OGRE_BUILD_COMPONENT_TERRAIN)
  set(APPS_DEPENDENCIES ${APPS_DEPENDENCIES} OgreTerrain)
  set(APPS_DEPENDENCIES_LIBS ${APPS_DEPENDENCIES_LIBS} -lOgreTerrainStatic)
endif ()

if (OGRE_BUILD_COMPONENT_VOLUME)
  set(APPS_DEPENDENCIES ${APPS_DEPENDENCIES} OgreVolume)
  set(APPS_DEPENDENCIES_LIBS ${APPS_DEPENDENCIES_LIBS} -lOgreVolumeStatic)
endif ()
  if (OGRE_BUILD_COMPONENT_RTSHADERSYSTEM)	
    set(OGRE_LIBRARIES ${OGRE_LIBRARIES} OgreRTShaderSystem)
    set(APPS_DEPENDENCIES_LIBS ${APPS_DEPENDENCIES_LIBS} -lOgreRTShaderSystemStatic)
  endif () 
if (OGRE_BUILD_RENDERSYSTEM_D3D9)
  set(APPS_DEPENDENCIES ${APPS_DEPENDENCIES} RenderSystem_Direct3D9)
endif ()
if (OGRE_BUILD_RENDERSYSTEM_D3D11)
  set(APPS_DEPENDENCIES ${APPS_DEPENDENCIES} RenderSystem_Direct3D11)
endif ()
if (OGRE_BUILD_RENDERSYSTEM_GL)
  set(APPS_DEPENDENCIES ${APPS_DEPENDENCIES} RenderSystem_GL)
  set(APPS_DEPENDENCIES_LIBS ${APPS_DEPENDENCIES_LIBS} -lRenderSystem_GLStatic)
endif ()
if (OGRE_BUILD_RENDERSYSTEM_GL3PLUS)
  set(APPS_DEPENDENCIES ${APPS_DEPENDENCIES} RenderSystem_GL3Plus)
  set(APPS_DEPENDENCIES_LIBS ${APPS_DEPENDENCIES_LIBS} -lRenderSystem_GL3PlusStatic)
endif ()
if (OGRE_BUILD_RENDERSYSTEM_GLES)
  set(APPS_DEPENDENCIES ${APPS_DEPENDENCIES} RenderSystem_GLES)
  set(APPS_DEPENDENCIES_LIBS ${APPS_DEPENDENCIES_LIBS} -lRenderSystem_GLESStatic)
endif ()
if (OGRE_BUILD_RENDERSYSTEM_GLES2)
  set(APPS_DEPENDENCIES ${APPS_DEPENDENCIES} RenderSystem_GLES2)
  set(APPS_DEPENDENCIES_LIBS ${APPS_DEPENDENCIES_LIBS} -lRenderSystem_GLES2Static)
endif ()
if (APPLE)
  if (OGRE_BUILD_PLATFORM_APPLE_IOS)
    set(OGRE_LIBRARIES ${OGRE_LIBRARIES})
  else ()
    set(OGRE_LIBRARIES ${OGRE_LIBRARIES} IOKit)
  endif ()
endif ()
# Last but not least, Ogre Main static :)
set(APPS_DEPENDENCIES_LIBS ${APPS_DEPENDENCIES_LIBS} -lOgreMainStatic)

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