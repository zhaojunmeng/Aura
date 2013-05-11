LOCAL_PATH := $(call my-dir)

# Aura module
include $(CLEAR_VARS)
LOCAL_MODULE := Aura
LOCAL_SRC_FILES := $(TARGET_ARCH_ABI)/libAura.a
include $(PREBUILT_STATIC_LIBRARY)


# Aura-native module

include $(CLEAR_VARS)

LOCAL_MODULE    := Aura-native
LOCAL_SRC_FILES := Aura-native.cpp
LOCAL_LDLIBS    += -landroid
LOCAL_STATIC_LIBRARIES := android_native_app_glue Aura
LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../../Aura

include $(BUILD_SHARED_LIBRARY)

$(call import-module,android/native_app_glue)	
