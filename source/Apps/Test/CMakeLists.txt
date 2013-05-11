# Build all the versions
if(AURA_BUILD_LINUX)
 subdirs(linux)
endif()

if(AURA_BUILD_ANDROID)
  subdirs(android)
endif()

if(AURA_BUILD_IOS)
  subdirs(ios)
endif()