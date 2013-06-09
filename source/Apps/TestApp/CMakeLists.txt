cmake_minimum_required(VERSION 2.6)

project(TestApp)
SET(APP_NAME ${PROJECT_NAME})

set(OGRE_MEDIA_DIR_REL ${CMAKE_CURRENT_SOURCE_DIR})

configure_file("${AURA_SOURCE_DIR}/Engine/main.cpp.in" "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp" @ONLY)

set(APP_SOURCE_FILES
  TestApp.cpp
  )

set(APP_HEADER_FILES
  TestApp.h
  )


if(ANDROID)
#  if(APPLE OR WIN32)
#    SET(ANDROID_EXECUTABLE "android")
#    SET(NDK_BUILD_EXECUTABLE "ndk-build")
#  else()
#    SET(ANDROID_EXECUTABLE "$ENV{ANDROID_SDK}/tools/android")
#    SET(NDK_BUILD_EXECUTABLE "$ENV{ANDROID_NDK}/ndk-build")
#  endif()

#  SET(ANT_EXECUTABLE "ant")
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
  SET(JNI_SRC "${JNI_SRC}\nLOCAL_SRC_FILES := ${APP_SOURCE_FILES_ANDROID} main.cpp \n")
  
  STRING(REGEX REPLACE ";" " " APPS_DEPENDENCIES_LIBS_ANDROID "${APPS_DEPENDENCIES_LIBS}")
  if(NOT ANDROID_GLES_ONLY)
    configure_file("${OGRE_TEMPLATES_DIR}/Android.mk_app.in" "${NDKOUT}/jni/Android.mk" @ONLY)
  else()
    configure_file("${OGRE_TEMPLATES_DIR}/AndroidGLES1.mk.in" "${NDKOUT}/jni/Android.mk" @ONLY)
  endif()
  configure_file("${OGRE_TEMPLATES_DIR}/Aura.java.in" "${NDKOUT}/src/com/cesardev/aura/Aura.java" @ONLY)
  
  file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/resources.cfg" DESTINATION "${NDKOUT}/assets")
  file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/media" DESTINATION "${NDKOUT}/assets")
  file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/ar" DESTINATION "${NDKOUT}/assets")
  file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/sound" DESTINATION "${NDKOUT}/assets")
  file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/RTShaderLib" DESTINATION "${NDKOUT}/assets")
  file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/../SDK/Android/.classpath" DESTINATION "${NDKOUT}/")
  file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/../SDK/Android/drawable-hdpi" DESTINATION "${NDKOUT}/res")
  file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/../SDK/Android/drawable-ldpi" DESTINATION "${NDKOUT}/res")
  file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/../SDK/Android/drawable-mdpi" DESTINATION "${NDKOUT}/res")
  file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/../SDK/Android/drawable-xhdpi" DESTINATION "${NDKOUT}/res")
  
#  add_custom_command(
#    TARGET ${APP_NAME}
#    POST_BUILD
#    COMMAND ${ANDROID_EXECUTABLE} update project --target ${ANDROID_TARGET} --path "${NDKOUT}"
#    WORKING_DIRECTORY ${NDKOUT}
#    )
  
#  if(DEBUG)	 
#    add_custom_command(
#      TARGET ${APP_NAME}
#      POST_BUILD
#      COMMAND ${NDK_BUILD_EXECUTABLE} all -j2 V=1 NDK_DEBUG=1
#      WORKING_DIRECTORY ${NDKOUT}
#      )
#  else()
#    add_custom_command(
#      TARGET ${APP_NAME}
#      POST_BUILD
#      COMMAND ${NDK_BUILD_EXECUTABLE} all -j2
#      WORKING_DIRECTORY ${NDKOUT}
#      )
#  endif()
  
#  add_custom_command(
#    TARGET ${APP_NAME}
#    POST_BUILD
#    COMMAND ${ANT_EXECUTABLE} debug
#    WORKING_DIRECTORY ${NDKOUT}
#    )

else()
  
  # Set up the frameworks
 # set(CMAKE_EXE_LINKER_FLAGS
  #"-framework QuartzCore -framework CoreMotion -framework SystemConfiguration -framework CoreVideo -framework CoreMedia -framework CoreGraphics -framework OpenGLES -framework UIKit -framework AudioToolbox" 
  #)

  set(CMAKE_OSX_ARCHITECTURES $(ARCHS_STANDARD_32_BIT))

  link_directories(${AURA_DEPENDENCIES_DIR})	
  
  ogre_add_executable(${APP_NAME} WIN32  ${APP_SOURCE_FILES} main.cpp ${AURA_RESOURCE_FILES})
  target_link_libraries(${APP_NAME} ${AURA_LIBRARIES} QCAR ck FreeImage FreeType OIS glsl_optimizer zzip boost_chrono boost_date_time boost_system boost_thread)

  # configure build
  set(OGRE_RUNTIME_OUTPUT ${CMAKE_CURRENT_BINARY_DIR})
  ogre_config_common(${APP_NAME})

  file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/resources.cfg" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")
  file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/media" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")
  file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/ar" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")
  file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/sound" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")
  file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/RTShaderLib" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")
  #file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/../SDK/RTShaderLib" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")

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

# APPLE!!
  if (APPLE)
# Automatic process starts :)

    set_source_files_properties(${CMAKE_CURRENT_SOURCE_DIR}/main.cpp PROPERTIES COMPILE_FLAGS "-x objective-c++")
    set_source_files_properties(${CMAKE_CURRENT_SOURCE_DIR}/${APP_NAME}.cpp PROPERTIES COMPILE_FLAGS "-x objective-c++")


    # On OS X, create .app bundle
    set_property(TARGET ${APP_NAME} PROPERTY MACOSX_BUNDLE TRUE)
    set_property(TARGET ${APP_NAME} PROPERTY MACOSX_BUNDLE_ICON_FILE AuraApplication_OSX.icns)
    set_property(TARGET ${APP_NAME} PROPERTY MACOSX_BUNDLE_INFO_PLIST ${CMAKE_CURRENT_SOURCE_DIR}/misc/Info.plist)
    set(MACOSX_BUNDLE_GUI_IDENTIFIER "org.ogre3d.\${PRODUCT_NAME:rfc1034identifier}")
    set_target_properties(${APP_NAME} PROPERTIES XCODE_ATTRIBUTE_ONLY_ACTIVE_ARCH "NO")

    set_target_properties(${APP_NAME} PROPERTIES XCODE_ATTRIBUTE_TARGETED_DEVICE_FAMILY "1,2")
    set(AURA_CONTENTS_PATH ${AURA_BINARY_DIR}/bin/$(CONFIGURATION)/${APP_NAME}.app)


    add_custom_command(TARGET ${APP_NAME} POST_BUILD
    COMMAND ditto ${CMAKE_CURRENT_SOURCE_DIR}/misc/*.png ${AURA_CONTENTS_PATH}/
    COMMAND ditto ${AURA_BINARY_DIR}/bin/*.cfg ${AURA_CONTENTS_PATH}/
    )

    add_custom_command(TARGET ${APP_NAME} POST_BUILD
    COMMAND mkdir ARGS -p ${CMAKE_BINARY_DIR}/lib/$(CONFIGURATION)/
    )
   




  endif (APPLE)

endif(ANDROID)


