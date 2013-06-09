# Set the Aura Source Files
set(AURA_SOURCE_FILES
  AuraApplication.cpp
  AuraAudioController.cpp
  AuraEngine.cpp
  AuraIOEngine.cpp
  AuraLog.cpp
  AuraQCARController.cpp
  ShaderController.cpp
)

# Android source files
if(ANDROID)
 set(AURA_SOURCE_FILES
  ${AURA_SOURCE_FILES}
  Android/AuraEngineAndroid.cpp
  Android/AuraIOEngineAndroid.cpp
  Android/AuraJNIUtils.cpp
 )

# Apple source files
else()
 set(AURA_SOURCE_FILES
  ${AURA_SOURCE_FILES}
  IOS/AuraEngineIOS.cpp
 )
 set_source_files_properties(${CMAKE_CURRENT_SOURCE_DIR}/IOS/AuraEngineIOS.cpp PROPERTIES COMPILE_FLAGS "-x objective-c++")
 set_source_files_properties(${CMAKE_CURRENT_SOURCE_DIR}/AuraLog.cpp PROPERTIES COMPILE_FLAGS "-x objective-c++")
 set_source_files_properties(${CMAKE_CURRENT_SOURCE_DIR}/AuraQCARController.cpp PROPERTIES COMPILE_FLAGS "-x objective-c++")	

endif(ANDROID)



# Set the Aura Header Files
set(AURA_HEADER_FILES

)

add_library(AuraEngine ${AURA_SOURCE_FILES})

# Config the render system
if (OGRE_BUILD_RENDERSYSTEM_GLES)
  set_target_properties(AuraEngine PROPERTIES COMPILE_FLAGS "-DUSE_OPENGL_ES_1_1")
endif ()
if (OGRE_BUILD_RENDERSYSTEM_GLES2)
  set_target_properties(AuraEngine PROPERTIES COMPILE_FLAGS "-DUSE_OPENGL_ES_2_0")
endif ()
