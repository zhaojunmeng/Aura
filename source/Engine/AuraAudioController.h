#ifndef _AuraAudioController_H_
#define _AuraAudioController_H_

#include "Singleton.h"
#include "ck/ck.h"
#include "ck/config.h"
#include "ck/bank.h"
#include "ck/sound.h"

#if OGRE_PLATFORM == OGRE_PLATFORM_ANDROID
#  include "AuraJNIUtils.h"
#endif

namespace Aura{

  class AuraAudioController: public Singleton<AuraAudioController>{

  public:
    AuraAudioController();
    ~AuraAudioController();
    
    void initialize();
    void update();

    void loadAudioFile(std::string& file);
    void play(std::string& sound);

    void pause();
    void resume();

    void shutdown();



  }; // AuraAudioController


}// Aura

#endif // _AuraAudioController_H_
