# Development Makefile. To build the app faster

ANDROID_ABI = armeabi-v7a
MODE = debug

ifeq ($(MODE), debug)

else

endif

#ANDROID_ABI = armeabi

ANDROID_OPTIONS = -DCMAKE_TOOLCHAIN_FILE="./source/CMake/toolchain/android.toolchain.cmake" -DANDROID_ABI=$(ANDROID_ABI)\
		-DANDROID_NATIVE_API_LEVEL=9\
		-DOGRE_DEPENDENCIES_DIR="../source/Dependencies/AndroidDependencies"\
		-DFREETYPE_FT2BUILD_INCLUDE_DIR="../source/Dependencies/AndroidDependencies/include/freetype"\
		-DFREETYPE_INCLUDE_DIR="../source/Dependencies/AndroidDependencies/include/freetype"\
		-DFREETYPE_LIBRARY_REL="../source/Dependencies/AndroidDependencies/lib/"$(ANDROID_ABI)"/libfreetype.a"\
		-DFreeImage_INCLUDE_DIR="../source/Dependencies/AndroidDependencies/include/"\
		-DFreeImage_LIBRARY_REL="../source/Dependencies/AndroidDependencies/lib/"$(ANDROID_ABI)"/libFreeImage.a"\
		-DZZip_INCLUDE_DIR="../source/Dependencies/AndroidDependencies/include/zzip"\
		-DZZip_LIBRARY_REL="../source/Dependencies/AndroidDependencies/lib/"$(ANDROID_ABI)"/libzzip.a"\
		-DOIS_INCLUDE_DIR="../source/Dependencies/AndroidDependencies/include/OIS"\
		-DOIS_LIBRARY_REL="../source/Dependencies/AndroidDependencies/lib/"$(ANDROID_ABI)"/libOIS.a"\
		-DGLSL_Optimizer_INCLUDE_DIR="../source/Dependencies/AndroidDependencies/include/"\
		-DGLSL_Optimizer_LIBRARY_REL="../source/Dependencies/AndroidDependencies/lib/"$(ANDROID_ABI)"/libglsl_optimizer.a"\



LINUX_OPTIONS = -G "Unix Makefiles"

WINDOWS_OPTIONS = -DAURA_BUILD_WINDOWS=1
IPHONE_OPTIONS = -DAURA_BUILD_IPHONE=1
COMMON_OPTIONS = -DBUILD_ENGINE=1\
OPTIMIZE_OPTIONS = -DOGRE_BUILD_PLUGIN_OCTREE=0 -DOGRE_BUILD_PLUGIN_PFX=0\
		   -DOGRE_BUILD_RTSHADERSYSTEM_CORE_SHADERS=1 -DOGRE_BUILD_RTSHADERSYSTEM_EXT_SHADERS=0\
		   -DOGRE_CONFIG_ENABLE_DDS=0
# -DCMAKE_BUILD_TYPE="Debug" \

all: linux android #iphone windows

linux:
	rm -Rf build_linux_$(MODE)
	mkdir build_linux_$(MODE)
	cd build_linux; cmake $(COMMON_OPTIONS) $(LINUX_OPTIONS) ..

android:
	rm -Rf build_android_$(MODE)
	mkdir -p build_android_$(MODE)
	cd build_android; cmake $(COMMON_OPTIONS) $(OPTIMIZE_OPTIONS) $(ANDROID_OPTIONS) ..	

iphone:
	echo "iPhone not supported yet."

windows:
	echo "Windows not supported yet."

clean:
	rm -Rf build_android* build_linux*
	find . -name "*~" -exec rm -Rf {} \;
#	cd source/Apps/android; rm -Rf bin gen obj libs