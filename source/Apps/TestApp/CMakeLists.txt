cmake_minimum_required(VERSION 2.6)

project(TestApp)
SET(APP_NAME ${PROJECT_NAME})

set(OGRE_MEDIA_DIR_REL ${CMAKE_CURRENT_SOURCE_DIR})

configure_file("${AURA_SOURCE_DIR}/Engine/main.cpp.in" "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp" @ONLY)

set(APP_SOURCE_FILES
  main.cpp
  TestApp.cpp
  )

set(APP_HEADER_FILES
  TestApp.h
  )

# Automatic process starts :)
if(APPLE)
  set_source_files_properties(${CMAKE_CURRENT_SOURCE_DIR}/main.cpp PROPERTIES COMPILE_FLAGS "-x objective-c++")
endif()

if(ANDROID)
  if(APPLE OR WIN32)
    SET(ANDROID_EXECUTABLE "android")
    SET(NDK_BUILD_EXECUTABLE "ndk-build")
  else()
    SET(ANDROID_EXECUTABLE "$ENV{ANDROID_SDK}/tools/android")
    SET(NDK_BUILD_EXECUTABLE "$ENV{ANDROID_NDK}/ndk-build")
  endif()

  SET(ANT_EXECUTABLE "ant")
  if(${ANDROID_NATIVE_API_LEVEL} LESS 14)
    MATH(EXPR ANDROID_SDK_API_LEVEL "${ANDROID_NATIVE_API_LEVEL}+1")
  else()
    SET(ANDROID_SDK_API_LEVEL "${ANDROID_NATIVE_API_LEVEL}")
    SET(SCREEN_SIZE "|screenSize")
  endif()
  
  if(OGRE_CONFIG_ENABLE_GLES2_GLSL_OPTIMISER)
    SET(GLES_OPTIMISER "-lglsl_optimizer -lmesa -lglcpp-library")
  endif()

  SET(ANDROID_TARGET "android-${ANDROID_SDK_API_LEVEL}")
  
  
  SET(NDKOUT "${CMAKE_BINARY_DIR}/${APP_NAME}")
  file(MAKE_DIRECTORY "${NDKOUT}")
  file(MAKE_DIRECTORY "${NDKOUT}/jni")
  file(MAKE_DIRECTORY "${NDKOUT}/assets")	
  file(MAKE_DIRECTORY "${NDKOUT}/res")
  file(WRITE "${NDKOUT}/default.properties" "target=${ANDROID_TARGET}")
  file(WRITE "${NDKOUT}/jni/Application.mk" "APP_ABI := ${ANDROID_ABI}\nAPP_STL := gnustl_static\nAPP_PLATFORM := ${ANDROID_TARGET} ")
  configure_file("${OGRE_TEMPLATES_DIR}/AndroidManifest.xml.in" "${NDKOUT}/AndroidManifest.xml" @ONLY)

  SET(ANDROID_MOD_NAME "${APP_NAME}")
  SET(JNI_SRC "LOCAL_PATH := @CMAKE_SOURCE_DIR@/source/Apps/${APP_NAME}/\n")
  STRING(REGEX REPLACE ";" " " APP_SOURCE_FILES_ANDROID "${APP_SOURCE_FILES}")
  SET(JNI_SRC "${JNI_SRC}\nLOCAL_SRC_FILES := ${APP_SOURCE_FILES_ANDROID} \n")
  
  if(NOT ANDROID_GLES_ONLY)
    configure_file("${OGRE_TEMPLATES_DIR}/Android.mk_app.in" "${NDKOUT}/jni/Android.mk" @ONLY)
  else()
    configure_file("${OGRE_TEMPLATES_DIR}/AndroidGLES1.mk.in" "${NDKOUT}/jni/Android.mk" @ONLY)
  endif()
  configure_file("${OGRE_TEMPLATES_DIR}/Android_resources.cfg.in" "${NDKOUT}/assets/resources.cfg" @ONLY)
  configure_file("${OGRE_TEMPLATES_DIR}/Aura.java.in" "${NDKOUT}/src/com/cesardev/aura/Aura.java" @ONLY)
  
  file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/media" DESTINATION "${NDKOUT}/assets")
  file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/../SDK/RTShaderLib" DESTINATION "${NDKOUT}/assets")
  file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/../SDK/Android/.classpath" DESTINATION "${NDKOUT}/")
  file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/../SDK/Android/drawable-hdpi" DESTINATION "${NDKOUT}/res")
  file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/../SDK/Android/drawable-ldpi" DESTINATION "${NDKOUT}/res")
  file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/../SDK/Android/drawable-mdpi" DESTINATION "${NDKOUT}/res")
  file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/../SDK/Android/drawable-xhdpi" DESTINATION "${NDKOUT}/res")
  
  add_custom_command(
    TARGET ${APP_NAME}
    POST_BUILD
    COMMAND ${ANDROID_EXECUTABLE} update project --target ${ANDROID_TARGET} --path "${NDKOUT}"
    WORKING_DIRECTORY ${NDKOUT}
    )
  
  if(DEBUG)	 
    add_custom_command(
      TARGET ${APP_NAME}
      POST_BUILD
      COMMAND ${NDK_BUILD_EXECUTABLE} all -j2 V=1 NDK_DEBUG=1
      WORKING_DIRECTORY ${NDKOUT}
      )
  else()
    add_custom_command(
      TARGET ${APP_NAME}
      POST_BUILD
      COMMAND ${NDK_BUILD_EXECUTABLE} all -j2
      WORKING_DIRECTORY ${NDKOUT}
      )
  endif()
  
  add_custom_command(
    TARGET ${APP_NAME}
    POST_BUILD
    COMMAND ${ANT_EXECUTABLE} debug
    WORKING_DIRECTORY ${NDKOUT}
    )

else()

  find_package(OIS)
  ogre_add_executable(${APP_NAME} WIN32 ${AURA_HEADER_FILES} ${AURA_SOURCE_FILES} ${APP_SOURCE_FILES} ${AURA_RESOURCE_FILES})
  target_link_libraries(${APP_NAME} ${OGRE_LIBRARIES} ${OGRE_PLUGIN_LIBRARIES} ${OIS_LIBRARIES})

  

  # configure SampleBrowser build
  set(OGRE_RUNTIME_OUTPUT ${CMAKE_CURRENT_BINARY_DIR})
  ogre_config_common(${APP_NAME})


  configure_file("${OGRE_TEMPLATES_DIR}/resources.cfg.in" "${CMAKE_CURRENT_BINARY_DIR}/resources.cfg" @ONLY)
  file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/media" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")
  file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/../SDK/RTShaderLib" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")

  # append _d for debug builds
  if (NOT APPLE)
    set_property(TARGET ${APP_NAME} APPEND PROPERTY DEBUG_POSTFIX "_d")
  endif ()

  # set install RPATH for Unix systems
  if (UNIX AND OGRE_FULL_RPATH)
    set_property(TARGET ${APP_NAME} APPEND PROPERTY
      INSTALL_RPATH ${CMAKE_INSTALL_PREFIX}/${OGRE_LIB_DIRECTORY})
    set_property(TARGET ${APP_NAME} PROPERTY INSTALL_RPATH_USE_LINK_PATH TRUE)
  endif ()

  if (APPLE)
    set_source_files_properties(${CMAKE_CURRENT_SOURCE_DIR}/src/${APP_NAME}.cpp PROPERTIES COMPILE_FLAGS "-x objective-c++")

    # On OS X, create .app bundle
    set_property(TARGET ${APP_NAME} PROPERTY MACOSX_BUNDLE TRUE)
    set_property(TARGET ${APP_NAME} PROPERTY MACOSX_BUNDLE_ICON_FILE SampleBrowser_OSX.icns)
    set_property(TARGET ${APP_NAME} PROPERTY MACOSX_BUNDLE_INFO_PLIST ${OGRE_SOURCE_DIR}misc/Info.plist)
    set(MACOSX_BUNDLE_GUI_IDENTIFIER "org.ogre3d.\${PRODUCT_NAME:rfc1034identifier}")
    set_target_properties(${APP_NAME} PROPERTIES XCODE_ATTRIBUTE_ONLY_ACTIVE_ARCH "NO")

    if (OGRE_BUILD_PLATFORM_APPLE_IOS)
      set_target_properties(${APP_NAME} PROPERTIES XCODE_ATTRIBUTE_TARGETED_DEVICE_FAMILY "1,2")
      set(OGRE_SAMPLE_CONTENTS_PATH ${OGRE_BINARY_DIR}/bin/$(CONFIGURATION)/${APP_NAME}.app)
      add_custom_command(TARGET ${APP_NAME} POST_BUILD
	COMMAND ditto ${OGRE_SOURCE_DIR}/misc/*.png ${OGRE_SAMPLE_CONTENTS_PATH}/
	COMMAND ditto ${OGRE_BINARY_DIR}/bin/*.cfg ${OGRE_SAMPLE_CONTENTS_PATH}/
	)
      if(OGRE_SDK_BUILD)
	add_custom_command(TARGET ${APP_NAME} POST_BUILD
          COMMAND mkdir ARGS -p ${OGRE_BINARY_DIR}/lib/$(CONFIGURATION)/
	  COMMAND ditto ${OGRE_BINARY_DIR}/Media ${OGRE_SAMPLE_CONTENTS_PATH}/Media
	  )
      else()
        add_custom_command(TARGET ${APP_NAME} POST_BUILD
          COMMAND mkdir ARGS -p ${OGRE_BINARY_DIR}/lib/$(CONFIGURATION)/
          #COMMAND ditto ${OGRE_SOURCE_DIR}/Samples/Media ${OGRE_SAMPLE_CONTENTS_PATH}/Media
          )
      endif(OGRE_SDK_BUILD)
    else()

      include_directories(
        ${OGRE_SOURCE_DIR}/RenderSystems/GL/include
        ${OGRE_SOURCE_DIR}/RenderSystems/GL/include/OSX
        )

      target_link_libraries(SampleBrowser ${OPENGL_LIBRARIES} ${CoreVideo_LIBRARIES})

      # Add the path where the Ogre framework was found, if it has been found somewhere
      if(NOT ${OGRE_FRAMEWORK_PATH} STREQUAL "" AND OGRE_SDK_BUILD)
	set_target_properties(${APP_NAME} PROPERTIES
          COMPILE_FLAGS "-F${OGRE_FRAMEWORK_PATH}"
          LINK_FLAGS "-F${OGRE_FRAMEWORK_PATH} -framework IOKit -framework Cocoa -framework Carbon -framework OpenGL -framework CoreVideo"
	  )
      endif()
      # also, symlink frameworks so .app is standalone
      # NOTE: $(CONFIGURATION) is not resolvable at CMake run time, it's only 
      # valid at build time (hence parenthesis rather than braces)
      
      set(OGRE_OSX_BUILD_CONFIGURATION "$(PLATFORM_NAME)/$(CONFIGURATION)")
      set(OGRE_BUILT_FRAMEWORK "$(PLATFORM_NAME)/$(CONFIGURATION)")
      #set (OGRE_SAMPLE_CONTENTS_PATH 
      #	${OGRE_BINARY_DIR}/bin/$(CONFIGURATION)/SampleBrowser.app/Contents)
      add_custom_command(TARGET ${APP_NAME} POST_BUILD
	#	COMMAND mkdir ARGS -p ${OGRE_SAMPLE_CONTENTS_PATH}/Frameworks
	COMMAND ln ARGS -s -f ${OGRE_BINARY_DIR}/lib/${OGRE_BUILT_FRAMEWORK}/Ogre.framework 
	${OGRE_SAMPLE_CONTENTS_PATH}/Frameworks/
	COMMAND ln ARGS -s -f ${Cg_LIBRARY_REL}
	${OGRE_SAMPLE_CONTENTS_PATH}/Frameworks/
	)
      # now cfg files
      if(OGRE_SDK_BUILD)
	add_custom_command(TARGET ${APP_NAME} POST_BUILD
	  COMMAND mkdir ARGS -p ${OGRE_SAMPLE_CONTENTS_PATH}/Resources
	  COMMAND ln ARGS -s -f ${OGRE_BINARY_DIR}/bin/macosx/plugins.cfg 
	  ${OGRE_SAMPLE_CONTENTS_PATH}/Resources/
	  COMMAND ln ARGS -s -f ${OGRE_BINARY_DIR}/bin/macosx/resources.cfg 
	  ${OGRE_SAMPLE_CONTENTS_PATH}/Resources/
	  #	  COMMAND ln ARGS -s -f ${OGRE_BINARY_DIR}/bin/macosx/samples.cfg 
	  #	  ${OGRE_SAMPLE_CONTENTS_PATH}/Resources/
	  #	  COMMAND ln ARGS -s -f ${OGRE_BINARY_DIR}/bin/macosx/quakemap.cfg 
	  #	  ${OGRE_SAMPLE_CONTENTS_PATH}/Resources/
	  COMMAND ln ARGS -s -f ${OGRE_SOURCE_DIR}/Media
	  ${OGRE_SAMPLE_CONTENTS_PATH}/Resources/
          COMMAND ditto 
	  ${OGRE_SOURCE_DIR}/misc/${APP_NAME}_OSX.icns ${OGRE_SAMPLE_CONTENTS_PATH}/Resources
	  )
      else()
	add_custom_command(TARGET ${APP_NAME} POST_BUILD
	  COMMAND mkdir ARGS -p ${OGRE_SAMPLE_CONTENTS_PATH}/Resources
	  COMMAND ln ARGS -s -f ${OGRE_BINARY_DIR}/bin/plugins.cfg 
	  ${OGRE_SAMPLE_CONTENTS_PATH}/Resources/
	  COMMAND ln ARGS -s -f ${OGRE_BINARY_DIR}/bin/resources.cfg 
	  ${OGRE_SAMPLE_CONTENTS_PATH}/Resources/
	  #	  COMMAND ln ARGS -s -f ${OGRE_BINARY_DIR}/bin/samples.cfg 
	  #	  ${OGRE_SAMPLE_CONTENTS_PATH}/Resources/
	  COMMAND ln ARGS -s -f ${OGRE_BINARY_DIR}/bin/quakemap.cfg 
	  ${OGRE_SAMPLE_CONTENTS_PATH}/Resources/
	  COMMAND ln ARGS -s -f ${OGRE_SOURCE_DIR}/Samples/Media
	  ${OGRE_SAMPLE_CONTENTS_PATH}/Resources/
          COMMAND ditto 
	  ${OGRE_SOURCE_DIR}/Samples/Common/misc/${APP_NAME}_OSX.icns ${OGRE_SAMPLE_CONTENTS_PATH}/Resources
	  )
      endif()

      # now plugins
      add_custom_command(TARGET ${APP_NAME} POST_BUILD
	COMMAND mkdir ARGS -p ${OGRE_SAMPLE_CONTENTS_PATH}/Plugins)
      if (OGRE_BUILD_RENDERSYSTEM_GL OR OGRE_SDK_BUILD)
	add_custom_command(TARGET SampleBrowser POST_BUILD
	  COMMAND ln ARGS -s -f ${OGRE_BINARY_DIR}/lib/${OGRE_OSX_BUILD_CONFIGURATION}/RenderSystem_GL.framework 
	  ${OGRE_SAMPLE_CONTENTS_PATH}/Frameworks/
	  )
      endif ()
      if (OGRE_BUILD_RENDERSYSTEM_GL3PLUS OR OGRE_SDK_BUILD)
	add_custom_command(TARGET ${APP_NAME} POST_BUILD
	  COMMAND ln ARGS -s -f ${OGRE_BINARY_DIR}/lib/${OGRE_OSX_BUILD_CONFIGURATION}/RenderSystem_GL3Plus.framework 
	  ${OGRE_SAMPLE_CONTENTS_PATH}/Frameworks/
	  )
      endif ()
      if (OGRE_BUILD_PLUGIN_BSP OR OGRE_SDK_BUILD)
	add_custom_command(TARGET ${APP_NAME} POST_BUILD
	  COMMAND ln ARGS -s -f ${OGRE_BINARY_DIR}/lib/${OGRE_OSX_BUILD_CONFIGURATION}/Plugin_BSPSceneManager.framework 
	  ${OGRE_SAMPLE_CONTENTS_PATH}/Frameworks/
	  )
      endif()
      if (OGRE_BUILD_PLUGIN_CG OR OGRE_SDK_BUILD)
	add_custom_command(TARGET ${APP_NAME} POST_BUILD
	  COMMAND ln ARGS -s -f ${OGRE_BINARY_DIR}/lib/${OGRE_OSX_BUILD_CONFIGURATION}/Plugin_CgProgramManager.framework 
	  ${OGRE_SAMPLE_CONTENTS_PATH}/Frameworks/
	  )
      endif()
      if (OGRE_BUILD_PLUGIN_OCTREE OR OGRE_SDK_BUILD)
	add_custom_command(TARGET ${APP_NAME} POST_BUILD
	  COMMAND ln ARGS -s -f ${OGRE_BINARY_DIR}/lib/${OGRE_OSX_BUILD_CONFIGURATION}/Plugin_OctreeSceneManager.framework 
	  ${OGRE_SAMPLE_CONTENTS_PATH}/Frameworks/
	  )
      endif()
      if (OGRE_BUILD_PLUGIN_PCZ OR OGRE_SDK_BUILD)
	add_custom_command(TARGET ${APP_NAME} POST_BUILD
	  COMMAND ln ARGS -s -f ${OGRE_BINARY_DIR}/lib/${OGRE_OSX_BUILD_CONFIGURATION}/Plugin_PCZSceneManager.framework 
	  ${OGRE_SAMPLE_CONTENTS_PATH}/Frameworks/    
	  )
	add_custom_command(TARGET ${APP_NAME} POST_BUILD
	  COMMAND ln ARGS -s -f ${OGRE_BINARY_DIR}/lib/${OGRE_OSX_BUILD_CONFIGURATION}/Plugin_OctreeZone.framework 
	  ${OGRE_SAMPLE_CONTENTS_PATH}/Frameworks/
	  )
      endif()
      if (OGRE_BUILD_PLUGIN_PFX OR OGRE_SDK_BUILD)
	add_custom_command(TARGET ${APP_NAME} POST_BUILD
	  COMMAND ln ARGS -s -f ${OGRE_BINARY_DIR}/lib/${OGRE_OSX_BUILD_CONFIGURATION}/Plugin_ParticleFX.framework 
	  ${OGRE_SAMPLE_CONTENTS_PATH}/Frameworks/
	  )
      endif()
      
      # Components
      if (OGRE_BUILD_COMPONENT_PAGING OR OGRE_SDK_BUILD)
	add_custom_command(TARGET ${APP_NAME} POST_BUILD
	  COMMAND ln ARGS -s -f ${OGRE_BINARY_DIR}/lib/${OGRE_OSX_BUILD_CONFIGURATION}/OgrePaging.framework 
	  ${OGRE_SAMPLE_CONTENTS_PATH}/Frameworks/
	  )
      endif()
      if (OGRE_BUILD_COMPONENT_PROPERTY OR OGRE_SDK_BUILD)
	add_custom_command(TARGET ${APP_NAME} POST_BUILD
	  COMMAND ln ARGS -s -f ${OGRE_BINARY_DIR}/lib/${OGRE_OSX_BUILD_CONFIGURATION}/OgreProperty.framework 
	  ${OGRE_SAMPLE_CONTENTS_PATH}/Frameworks/
	  )
      endif()
      if (OGRE_BUILD_COMPONENT_RTSHADERSYSTEM OR OGRE_SDK_BUILD)
	add_custom_command(TARGET ${APP_NAME} POST_BUILD
	  COMMAND ln ARGS -s -f ${OGRE_BINARY_DIR}/lib/${OGRE_OSX_BUILD_CONFIGURATION}/OgreRTShaderSystem.framework 
	  ${OGRE_SAMPLE_CONTENTS_PATH}/Frameworks/
	  )
      endif()
      if (OGRE_BUILD_COMPONENT_TERRAIN OR OGRE_SDK_BUILD)
	add_custom_command(TARGET ${APP_NAME} POST_BUILD
	  COMMAND ln ARGS -s -f ${OGRE_BINARY_DIR}/lib/${OGRE_OSX_BUILD_CONFIGURATION}/OgreTerrain.framework 
	  ${OGRE_SAMPLE_CONTENTS_PATH}/Frameworks/
	  )
      endif()
      if (OGRE_BUILD_COMPONENT_VOLUME OR OGRE_SDK_BUILD)
	add_custom_command(TARGET ${APP_NAME} POST_BUILD
	  COMMAND ln ARGS -s -f ${OGRE_BINARY_DIR}/lib/${OGRE_OSX_BUILD_CONFIGURATION}/OgreVolume.framework 
	  ${OGRE_SAMPLE_CONTENTS_PATH}/Frameworks/
	  )
      endif()
      if (OGRE_BUILD_COMPONENT_OVERLAY OR OGRE_SDK_BUILD)
	add_custom_command(TARGET ${APP_NAME} POST_BUILD
	  COMMAND ln ARGS -s -f ${OGRE_BINARY_DIR}/lib/${OGRE_OSX_BUILD_CONFIGURATION}/OgreOverlay.framework 
	  ${OGRE_SAMPLE_CONTENTS_PATH}/Frameworks/
	  )
      endif()

    endif()
  endif (APPLE)

endif(ANDROID)


