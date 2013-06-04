# Development Makefile. To build the app faster

ANDROID_ABI = armeabi-v7a
#ANDROID_ABI = armeabi

ANDROID_TARGET_API_LEVEL = 17

ANDROID_OPTIONS = -DOGRE_BUILD_PLATFORM_ANDROID=1\
		  -DCMAKE_TOOLCHAIN_FILE="./source/CMake/toolchain/android.toolchain.cmake" -DANDROID_ABI=$(ANDROID_ABI)\
	    	  -DANDROID_NATIVE_API_LEVEL=$(ANDROID_TARGET_API_LEVEL) -DOGRE_DEPENDENCIES_DIR="../source/Dependencies/AndroidDependencies/"\
		-DFREETYPE_FT2BUILD_INCLUDE_DIR="../source/Dependencies/AndroidDependencies/include/freetype"\
		-DFREETYPE_INCLUDE_DIR="../source/Dependencies/AndroidDependencies/include/freetype"\
		-DFREETYPE_LIBRARY_REL="../source/Dependencies/AndroidDependencies/lib/"$(ANDROID_ABI)"/libfreetype.a"\
		-DFreeImage_INCLUDE_DIR="../source/Dependencies/AndroidDependencies/include/"\
		-DFreeImage_LIBRARY_REL="../source/Dependencies/AndroidDependencies/lib/"$(ANDROID_ABI)"/libFreeImage.a"\
		-DZZip_INCLUDE_DIR="../source/Dependencies/AndroidDependencies/include/zzip"\
		-DZZip_LIBRARY_REL="../source/Dependencies/AndroidDependencies/lib/"$(ANDROID_ABI)"/libzzip.a"\

LINUX_OPTIONS = -G "Unix Makefiles"

WINDOWS_OPTIONS = -DAURA_BUILD_WINDOWS=1
IPHONE_OPTIONS = -DAURA_BUILD_IPHONE=1
COMMON_OPTIONS = -DBUILD_ENGINE=1\
BUILD_OPTIONS = -DOGRE_BUILD_PLUGIN_OCTREE=0 -DOGRE_BUILD_PLUGIN_PFX=0\
		-DOGRE_BUILD_RTSHADERSYSTEM_CORE_SHADERS=1 -DOGRE_BUILD_RTSHADERSYSTEM_EXT_SHADERS=0\
		-DOGRE_CONFIG_ENABLE_DDS=0 -DOGRE_CONFIG_ENABLE_GLES2_GLSL_OPTIMISER=1

mode = debug
ifeq ($(mode), debug)
BUILD_OPTIONS += -DCMAKE_BUILD_TYPE="RelWithDebInfo"
else
BUILD_OPTIONS += -DCMAKE_BUILD_TYPE="Release"	
endif

all: linux android #iphone windows

linux:
	rm -Rf build_linux_$(mode)
	mkdir build_linux_$(mode)
	cd build_linux_$(mode); cmake $(COMMON_OPTIONS) $(LINUX_OPTIONS) ..

android:
	rm -Rf build_android_$(mode)
	mkdir -p build_android_$(mode)
	cd build_android_$(mode); cmake $(COMMON_OPTIONS) $(BUILD_OPTIONS) $(ANDROID_OPTIONS) ..	

iphone:
	echo "iPhone not supported yet."

windows:
	echo "Windows not supported yet."

clean:
	rm -Rf build_android* build_linux*
	find . -name "*~" -exec rm -Rf {} \;
#	cd source/Apps/android; rm -Rf bin gen obj libs