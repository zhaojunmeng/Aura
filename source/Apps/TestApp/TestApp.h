
#ifndef _TEST_APP_H_
#define _TEST_APP_H_

#include <AuraApplication.h>

namespace Aura{

  class TestApp: public AuraApplication 
  {

  public:

    TestApp();
    ~TestApp();

    virtual void initTracker();
    virtual void initAudio();
    virtual void createScene();
    virtual bool frameStarted(const Ogre::FrameEvent& evt);  
    virtual bool frameEnded(const Ogre::FrameEvent& evt);  
    virtual void destroyScene();

    virtual bool keyPressed(const OIS::KeyEvent& evt);
    virtual bool keyReleased(const OIS::KeyEvent& evt);
    virtual bool mouseMoved(const OIS::MouseEvent& evt);
    virtual bool mousePressed(const OIS::MouseEvent& evt, OIS::MouseButtonID id);
    virtual bool mouseReleased(const OIS::MouseEvent& evt, OIS::MouseButtonID id);
    virtual bool touchMoved(const OIS::MultiTouchEvent&);
    virtual bool touchPressed(const OIS::MultiTouchEvent&);
    virtual bool touchReleased(const OIS::MultiTouchEvent&);
    virtual bool touchCancelled(const OIS::MultiTouchEvent&);
    virtual void destroyApp();

#if OGRE_PLATFORM == OGRE_PLATFORM_APPLE_IOS
    virtual void motionBegan( void ){}
    virtual void motionEnded( void ){}
    virtual void motionCancelled( void ){}
#endif

  private:
    Ogre::AnimationStateSet* sinbadAnims;
    CkBank* bank;
    CkSound* sound;
    CkSound* music;
 
  };

}

#endif // _TEST_APP_H
