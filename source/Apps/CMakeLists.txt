# Prepare the Android.mk for AuraEngine (only Android)
if(ANDROID)
  configure_file("${OGRE_TEMPLATES_DIR}/Android.mk_engine.in" "${CMAKE_BINARY_DIR}/Android_engine.mk" @ONLY)
endif(ANDROID)


# ADD SUBDIRECTORIES OF THE APPS :)
add_subdirectory(TestApp)
