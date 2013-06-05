// Copyright 2011 Cricket Technology
// www.crickettechnology.com
/** @file */
/** @defgroup CkConfig CkConfig */
/** @{ */

#pragma once
#include "ck/platform.h"

#if CK_PLATFORM_ANDROID
#  include <jni.h>
#endif

#if CK_PLATFORM_IOS
#  include <AudioToolbox/AudioToolbox.h>
#endif

////////////////////////////////////////

/** Memory allocation function */
typedef void* (*CkAllocFunc)(int bytes);
/** Memory deallocation function */
typedef void (*CkFreeFunc)(void*);


/** log message types */
typedef enum 
{
    kCkLog_Info =  (1 << 0),
    kCkLog_Warning = (1 << 1),
    kCkLog_Error = (1 << 2),

    kCkLog_None = 0,
    kCkLog_All = (kCkLog_Info | kCkLog_Warning | kCkLog_Error)
} CkLogType;

/** log message function */
typedef void (*CkLogFunc)(CkLogType, const char* msg);


////////////////////////////////////////

/** Configuration options */
struct _CkConfig
{
#ifdef __cplusplus
#  if CK_PLATFORM_ANDROID
    _CkConfig(JNIEnv* env, jobject activity);
#  else
    _CkConfig();
#  endif
#endif // __cplusplus

#if CK_PLATFORM_ANDROID
    /** The JNIEnv pointer. 
      @par Only available on Android. */
    JNIEnv* jni;

    /** A Java reference to your app's Activity.
      @par Only available on Android. */
    jobject activity;

    /** If true, always use Java AudioTrack for output of final mix, instead of OpenSL ES.
      Default is false (use Java AudioTrack only when OpenSL ES is not available, i.e. Android versions prior to 2.3). 
      @par Only available on Android. */
    bool useJavaAudio;
#endif

#if CK_PLATFORM_IOS
    /** Audio session category; this determines how audio from your app interacts with 
      audio from other apps.  See Apple's "Audio Session Programming Guide" for more 
      information on audio session categories.
      Default is kAudioSessionCategory_MediaPlayback. 
      @par Only available on iOS. */
    int audioSessionCategory;
#endif

    /** If true, software support for Ogg Vorbis stream sounds is enabled.
      Default is false (no additional Ogg Vorbis support in software). */
    int enableOggVorbis;


    /** Memory allocation function.
      Default is NULL (system new will be used). 
      All calls to this function will be made from the same thread on which you call 
      all Cricket Audio functions, unless you have enabled Ogg Vorbis stream support,
      in which case the allocator must be thread-safe. */
    CkAllocFunc allocFunc;

    /** Memory deallocation function.
      Default is NULL (system delete will be used). 
      All calls to this function will be made from the same thread on which you call
      all Cricket Audio functions, unless you have enabled Ogg Vorbis stream support,
      in which case the allocator must be thread-safe. */
    CkFreeFunc freeFunc;


    /** Bitmask for which types of messages are logged. 
      Default is kCkLog_All (all messages logged). */
    unsigned int logMask;

    /** Function to handle log messages.
      Default is NULL (printf or equivalent will be used). */
    CkLogFunc logFunc;

    /** Log file in which messages are saved.
      Default is NULL (log messages not saved to a file). */
    const char* logFile;


    /** Audio processing frame duration, in ms.
      Shorter times result in lower latency, but require more CPU.
      Default is 5 ms. */
    float audioUpdateMs;

    /** Size of buffer for stream sounds, in ms.
      Larger buffers require more memory, but are less likely
      to skip due to slow file reads.
      Default is 500 ms. */
    float streamBufferMs;

    /** Interval between file reads for stream sounds, in ms.
      Shorter times will allow for smaller stream buffer sizes, but require more CPU.
      This value should be set to significantly less than streamBufferMs, or your buffers will always underrun!
      Default is 100 ms. */
    float streamFileUpdateMs;

};

typedef struct _CkConfig CkConfig;

/** Default value of CkConfig.audioUpdateMs */
extern const float CkConfig_audioUpdateMsDefault;

/** Default value of CkConfig.streamBufferMs */
extern const float CkConfig_streamBufferMsDefault;

/** Default value of CkConfig.streamFileUpdateMs */
extern const float CkConfig_streamFileUpdateMsDefault;


////////////////////////////////////////

#ifdef __cplusplus
extern "C"
{
#endif

/** If you are using Objective-C, call CkConfigInit() to initialize the CkConfig
  struct to its default values.
  (If you are using C++, it is called for you by the CkConfig constructor.) 
 */

#if CK_PLATFORM_ANDROID
void CkConfigInit(CkConfig*, JNIEnv* env, jobject activity);
#else
void CkConfigInit(CkConfig*);
#endif


#ifdef __cplusplus
} // extern "C"
#endif

/** @} */
