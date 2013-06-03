/*
 -----------------------------------------------------------------------------
 This source file is part of OGRE
 (Object-oriented Graphics Rendering Engine)
 For the latest info, see http://www.ogre3d.org/
 
 Copyright (c) 2000-2013 Torus Knot Software Ltd
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 -----------------------------------------------------------------------------
 */
#include "OgrePlatform.h"
#include "TestApp.h"


// Different headers for different platforms (Main :) )
#if OGRE_PLATFORM == OGRE_PLATFORM_ANDROID

#include "AuraJNIUtils.h"
#include "AuraEngineAndroid.h"

jint JNI_OnLoad(JavaVM* vm, void* reserved)
{
  Aura::AuraJNIUtils::getInstance()->setVM(vm);
  return JNI_VERSION_1_6;
}


void android_main(struct android_app* state) {
#else
int main(int argc, char *argv[]) {
#endif

#if OGRE_PLATFORM == OGRE_PLATFORM_APPLE_IOS
  NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
  int retVal = UIApplicationMain(argc, argv, @"UIApplication", @"AppDelegate");
  [pool release];
  return retVal;

#elif (OGRE_PLATFORM == OGRE_PLATFORM_APPLE) && __LP64__
  NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
  mAppDelegate = [[AppDelegate alloc] init];
  [[NSApplication sharedApplication] setDelegate:mAppDelegate];
  int retVal = NSApplicationMain(argc, (const char **) argv);
  [pool release];
  return retVal;

#elif OGRE_PLATFORM == OGRE_PLATFORM_ANDROID
    // Make sure glue isn't stripped.
    app_dummy();

    Aura::AuraJNIUtils::getInstance()->setState(state);
    Aura::AuraEngineAndroid engine;
    Aura::TestApp app;
    Aura::AuraJNIUtils::getInstance()->setAuraApp(&app);

    engine.start(&app);

 #else
    // Run everything
    Aura::AuraEngine* engine = new AuraEngine();
    Aura::TestApp app;
    engine.start(&app);
    return 0;
 #endif

}
