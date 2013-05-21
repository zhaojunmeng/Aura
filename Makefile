# Development Makefile. To build the app faster

ANDROID_ABI = armeabi-v7a
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
COMMON_OPTIONS = -DBUILD_ENGINE=1 \
# -DCMAKE_BUILD_TYPE="Debug" \

all: linux android #iphone windows

#tools:
#	rm -Rf build_tools
#	mkdir build_tools
#	cd build_tools; cmake -DBUILD_TOOLS=1 ..; make

linux:
	rm -Rf build_linux
	mkdir build_linux
	cd build_linux; cmake $(COMMON_OPTIONS) $(LINUX_OPTIONS) ..

android:
	rm -Rf build_android
#	mkdir -p build_android/source/systemlibs
	mkdir -p build_android/
#	cp -R libs/AndroidDependencies/lib/* build_android/source/systemlibs
	cd build_android; cmake $(COMMON_OPTIONS) $(ANDROID_OPTIONS) .. # Twice to solve an error
	cd build_android; cmake $(COMMON_OPTIONS) $(ANDROID_OPTIONS) ..	

iphone:
	echo "iPhone not supported yet."

windows:
	echo "Windows not supported yet."

clean:
	rm -Rf build_android build_linux build_tools
	find . -name "*~" -exec rm -Rf {} \;
#	cd source/Apps/android; rm -Rf bin gen obj libs