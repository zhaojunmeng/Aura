// Copyright 2011 Cricket Technology
// www.crickettechnology.com
/** @file */

#pragma once

// software platform
#undef CK_PLATFORM_IOS
#undef CK_PLATFORM_ANDROID
#undef CK_PLATFORM_MACOS
#undef CK_PLATFORM_WIN

#ifdef __APPLE__
#  include <TargetConditionals.h>
#  if TARGET_OS_IPHONE
#    define CK_PLATFORM_IOS 1
#  else
#    define CK_PLATFORM_MACOS 1
#  endif
#elif defined(__ANDROID__)
#  define CK_PLATFORM_ANDROID 1
#elif defined(_WIN64) || defined(_WIN32)
#  define CK_PLATFORM_WIN 1
#endif

#if CK_PLATFORM_MACOS && (__ENVIRONMENT_MAC_OS_X_VERSION_MIN_REQUIRED__ < 1060)
#  error "Mac OS 10.6 required!"
#endif

#if !CK_PLATFORM_IOS && !CK_PLATFORM_ANDROID && !CK_PLATFORM_MACOS && !CK_PLATFORM_WIN
#  error "Unsupported platform!"
#endif
