// Copyright 2011 Cricket Technology
// www.crickettechnology.com
/** @file */
/** @defgroup CkPathType CkPathType */
/** @{ */

#pragma once
#include "ck/platform.h"


/** Indicates how a file path should be interpreted. */
typedef enum 
{
    /** A full path to a file on the file system. */
    kCkPathType_FileSystem = 0,

#if CK_PLATFORM_ANDROID
    /** A path to an asset in the .apk. 
     @par Only available on Android. */
    kCkPathType_Asset,

    /** A path relative to the private files directory.
     @par Only available on Android. */
    kCkPathType_PrivateFiles,

    /** A path relative to the external storage directory.
     @par Only available on Android. */
    kCkPathType_ExternalStorage,
#endif

#if CK_PLATFORM_IOS | CK_PLATFORM_MACOS
    /** A path relative to the application's resource directory. 
     @par Only available on iOS and Mac OS. */
    kCkPathType_Resource,

    /** A path relative to the application's bundle directory.
     @par Only available on iOS and Mac OS. */
    kCkPathType_Bundle,
#endif

#if CK_PLATFORM_WIN
    /** A path relative to the executable's directory. 
     @par Only available on Windows. */
    kCkPathType_ExeDir,
#endif

    /** The default path type. */
#if CK_PLATFORM_ANDROID
    kCkPathType_Default = kCkPathType_Asset,
#elif CK_PLATFORM_IOS | CK_PLATFORM_MACOS
    kCkPathType_Default = kCkPathType_Resource,
#elif CK_PLATFORM_WIN
    kCkPathType_Default = kCkPathType_ExeDir,
#endif
} CkPathType;

/** @} */
