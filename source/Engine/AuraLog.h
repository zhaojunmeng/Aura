#ifndef _AuraLog_H_
#define _AuraLog_H_

#include "Singleton.h"
#include "Ogre.h"
#include <QCAR/QCAR.h>
#include <QCAR/Matrices.h>

#if OGRE_PLATFORM == OGRE_PLATFORM_ANDROID
#  include <android/log.h>
#else

#endif

namespace Aura{
  
  class AuraLog{

  public:

    static void info(const char* msg);
    static void warn(const char* msg);
    static void error(const char* msg);

    static void info(const std::string& msg);
    static void warn(const std::string& msg);
    static void error(const std::string& msg);

    static void printMatrix(QCAR::Matrix44F mat);
    static void printMatrix(Ogre::Matrix4 mat);
    
  };

}
#endif // _AuraLog_H_
