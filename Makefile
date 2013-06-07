# Development Makefile. To build the app faster

ANDROID_ABI = armeabi-v7a
#ANDROID_ABI = armeabi

ANDROID_TARGET_API_LEVEL = 17

ANDROID_OPTIONS = -DOGRE_BUILD_PLATFORM_ANDROID=1 -DCMAKE_TOOLCHAIN_FILE="./source/CMake/toolchain/android.toolchain.cmake"\
		  -DANDROID_ABI=$(ANDROID_ABI) -DANDROID_NATIVE_API_LEVEL=$(ANDROID_TARGET_API_LEVEL)\

LINUX_OPTIONS = -G "Unix Makefiles"

WINDOWS_OPTIONS = -DAURA_BUILD_WINDOWS=1
IOS_OPTIONS =  -DOGRE_BUILD_PLATFORM_APPLE_IOS=1 -G "Xcode"
COMMON_OPTIONS =  -DBUILD_ENGINE=1 -DOGRE_STATIC=1\
		  -DOGRE_BUILD_RENDERSYSTEM_GLES2=1\
		  -DOGRE_BUILD_COMPONENT_RTSHADERSYSTEM=1\
		  -DOGRE_BUILD_COMPONENT_OVERLAY=1\

mode = debug
ifeq ($(mode), debug)
BUILD_OPTIONS += -DCMAKE_BUILD_TYPE="RelWithDebInfo"
else
BUILD_OPTIONS += -DCMAKE_BUILD_TYPE="Release"	
endif

all: android ios #windows

android:
	rm -Rf build_android_$(mode)
	mkdir -p build_android_$(mode)
	cd build_android_$(mode); cmake $(COMMON_OPTIONS) $(ANDROID_OPTIONS) ..	

ios:
	rm -Rf build_ios_$(mode)
	mkdir -p build_ios_$(mode)
	cd build_ios_$(mode); cmake $(COMMON_OPTIONS) $(IOS_OPTIONS) ..
windows:
	echo "Windows not supported yet."

clean:
	rm -Rf build_android* build_linux* build_ios*
	find . -name "*~" -exec rm -Rf {} \;
#	cd source/Apps/android; rm -Rf bin gen obj libs
