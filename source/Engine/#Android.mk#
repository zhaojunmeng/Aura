LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)
LOCAL_MODULE  := AuraEngine

LOCAL_LDLIBS := -landroid -lc -lm -ldl -llog -lEGL -lGLESv2
#LOCAL_LDLIBS	+= -L/home/cesar/git/Aura/build_android/lib -L$(DEPENDENCIES_DIR)

    #LOCAL_LDLIBS += -lPlugin_ParticleFXStatic -lPlugin_OctreeSceneManagerStatic -lRenderSystem_GLES2Static -lOgreRTShaderSystemStatic 
    #LOCAL_LDLIBS += -lOgreOverlayStatic -lOgreMainStatic
    #LOCAL_LDLIBS += -lzzip -lz -lFreeImage -lfreetype -lOIS  $(DEPENDENCIES_DIR)/libsupc++.a 
    #LOCAL_LDLIBS += $(DEPENDENCIES_DIR)/libstdc++.a /home/cesar/git/Aura/build_android/TestApp/obj/local/armeabi-v7a/libcpufeatures.a
LOCAL_STATIC_LIBRARIES := android_native_app_glue cpufeatures

LOCAL_CFLAGS := -DGL_GLEXT_PROTOTYPES=1 -I/home/cesar/git/Aura/build_android/source/Ogre-1.9a/include -I/home/cesar/git/Aura/source/Ogre-1.9a/OgreMain/include 
LOCAL_CFLAGS += -I/home/cesar/git/Aura/source/Ogre-1.9a/RenderSystems/GLES2/include -I/home/cesar/git/Aura/source/Ogre-1.9a/RenderSystems/GLES2/include/EGL
LOCAL_CFLAGS += -I/opt/android-ndk-r8e/sources/cpufeatures -I/home/cesar/git/Aura/source/Ogre-1.9a/Components/RTShaderSystem/include 
LOCAL_CFLAGS += -I/home/cesar/git/Aura/source/Ogre-1.9a/Components/Overlay/include -I/home/cesar/git/Aura/source/Engine
LOCAL_CFLAGS += -I/home/cesar/git/Aura/source/Ogre-1.9a/PlugIns/ParticleFX/include -I/home/cesar/git/Aura/source/Ogre-1.9a/PlugIns/OctreeSceneManager/include 
LOCAL_CFLAGS += -I/home/cesar/git/Aura/source/Dependencies/AndroidDependencies/include -I/home/cesar/git/Aura/source/Dependencies/AndroidDependencies/include/OIS -I/home/cesar/git/Aura/build_android/source/Ogre-1.9a/Samples/include
LOCAL_CFLAGS += -fexceptions -frtti -x c++ -D___ANDROID___ -DANDROID -DZZIP_OMIT_CONFIG_H -DUSE_RTSHADER_SYSTEM=1 

LOCAL_CFLAGS += -I/home/cesar/git/Aura/source/vuforia-2.0/include
LOCAL_SRC_FILES := AuraApplication.cpp AuraOgreEngineAndroid.cpp ShaderController.cpp AuraIOEngineAndroid.cpp AuraOgreEngine.cpp AuraIOEngine.cpp #AuraQCARController.cpp

    include $(BUILD_STATIC_LIBRARY) 

#    $(call import-module,android/cpufeatures) 
    $(call import-module,android/native_app_glue) 
