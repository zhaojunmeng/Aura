# Aura's CMakeLists.txt
cmake_minimum_required(VERSION 2.6)

project(AURA)
set(AURA 1.0)
set(AURA_BIN_NAME main)

if(AURA_BUILD_ANDROID)
  set(ANDROID_ABI x86)
  set(ANDROID_NATIVE_API_LEVEL 9)
endif()


# Dependencies first

set(CMAKE_MODULE_PATH
    ${AURA_SOURCE_DIR}/Dependencies/CMake
    ${AURA_SOURCE_DIR}/Dependencies/CMake/Utils
    ${AURA_SOURCE_DIR}/Dependencies/CMake/Packages
    ${AURA_SOURCE_DIR}/Dependencies/CMake/Templates
    )

include(ConfigOgreKit)

set(GAMEKIT_GRAPHIC_BACKEND 2)

configure_ogrekit(${AURA_SOURCE_DIR}/Dependencies ${AURA_SOURCE_DIR}/Dependencies/${GAMEKIT_GRAPHIC_BACKEND_DIR} ${GAMEKIT_GRAPHIC_BACKEND})

subdirs(Dependencies)

# Dependencies
include_directories(${AURA_SOURCE_DIR}/Aura)
include_directories(${AURA_SOURCE_DIR}/Dependencies/Ogre-1.8rc/OgreMain/include)
include_directories(${AURA_BINARY_DIR}/Dependencies/include)

# Aura :)
subdirs(Aura)



# Final executable
if(AURA_BUILD_LINUX)
  include_directories(${AURA_SOURCE_DIR}/Aura)
  add_executable(${AURA_BIN_NAME} ${AURA_SOURCE_DIR}/Apps/linux/aura-linux.cpp)
  target_link_libraries(${AURA_BIN_NAME} Aura ${OGREKIT_OGRE_LIBS})
endif()

if(AURA_BUILD_ANDROID)
  
endif()

if(AURA_BUILD_IPHONE)

endif()

if(AURA_BUILD_WINDOWS)

endif()



