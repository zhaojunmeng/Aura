#include "AuraLog.h"

namespace Aura{

  void AuraLog::info(const char* msg){
#if OGRE_PLATFORM == OGRE_PLATFORM_ANDROID
    __android_log_print(ANDROID_LOG_INFO, "Aura", msg);
#else
    NSLog(@"[INFO] ",msg);
#endif
  }

  void AuraLog::warn(const char* msg){
#if OGRE_PLATFORM == OGRE_PLATFORM_ANDROID
    __android_log_print(ANDROID_LOG_WARN, "Aura", msg);
#else
    NSLog(@"[WARN] ",msg);
#endif
  }

  void AuraLog::error(const char* msg){
#if OGRE_PLATFORM == OGRE_PLATFORM_ANDROID
    __android_log_print(ANDROID_LOG_ERROR, "Aura", msg);
#else
    NSLog(@"[ERROR] ",msg);
#endif
  }

  void AuraLog::info(const std::string& msg){
    info(msg.c_str());
  }
  void AuraLog::warn(const std::string& msg){
    warn(msg.c_str());
  }
  void AuraLog::error(const std::string& msg){
    error(msg.c_str());
  }

  void AuraLog::printMatrix(QCAR::Matrix44F mat){
#if OGRE_PLATFORM == OGRE_PLATFORM_ANDROID
    char str[100];
    sprintf(str,"%f %f %f %f", mat.data[0],mat.data[4],mat.data[8],mat.data[12]);
    info(str);
    sprintf(str,"%f %f %f %f",mat.data[1],mat.data[5],mat.data[9],mat.data[13]);
    info(str);
    sprintf(str,"%f %f %f %f",mat.data[2],mat.data[6],mat.data[10],mat.data[14]);
    info(str);
    sprintf(str,"%f %f %f %f",mat.data[3],mat.data[7],mat.data[11],mat.data[15]);
    info(str);
#else
    //ßstd::cout<<"[Mat] "<<mat<<std::endl;
#endif
    
  }

  void AuraLog::printMatrix(Ogre::Matrix4 mat){
#if OGRE_PLATFORM == OGRE_PLATFORM_ANDROID
    char str[100];
    sprintf(str,"%f %f %f %f", mat[0][0], mat[0][1],mat[0][2],mat[0][3]);
    info(str);
    sprintf(str,"%f %f %f %f", mat[1][0], mat[1][1],mat[1][2],mat[1][3]);
    info(str);
    sprintf(str,"%f %f %f %f", mat[2][0], mat[2][1],mat[2][2],mat[2][3]);
    info(str);
    sprintf(str,"%f %f %f %f", mat[3][0], mat[3][1],mat[3][2],mat[3][3]);
    info(str);

#else
    std::cout<<"[Mat] "<<mat<<std::endl;
#endif
  }


} // Aura
