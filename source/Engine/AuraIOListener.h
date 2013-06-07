#ifndef _AuraIOListener_H_
#define _AuraIOListener_H_

#include <OIS/OIS.h>

namespace Aura{

  class AuraIOListener:
#if (OGRE_PLATFORM != OGRE_PLATFORM_APPLE_IOS) && (OGRE_PLATFORM != OGRE_PLATFORM_ANDROID)
    public OIS::KeyListener,
    public OIS::MouseListener
#else
    public OIS::MultiTouchListener
#endif
    {
    public:
      /* IO Interface :) */
      virtual bool keyPressed(const OIS::KeyEvent& evt){ return true; }
      virtual bool keyReleased(const OIS::KeyEvent& evt){return true; }
      virtual bool mouseMoved(const OIS::MouseEvent& evt){return true; }
      virtual bool mousePressed(const OIS::MouseEvent& evt, OIS::MouseButtonID id){return true; }
      virtual bool mouseReleased(const OIS::MouseEvent& evt, OIS::MouseButtonID id){return true; }
      virtual bool touchMoved(const OIS::MultiTouchEvent&){return true; }
      virtual bool touchPressed(const OIS::MultiTouchEvent&){return true; }
      virtual bool touchReleased(const OIS::MultiTouchEvent&){return true;}
      virtual bool touchCancelled(const OIS::MultiTouchEvent&){return true; }


#if OGRE_PLATFORM == OGRE_PLATFORM_APPLE_IOS
      virtual void motionBegan( void ){};
      virtual void motionEnded( void ){};
      virtual void motionCancelled( void ){};
#endif

      };

}// Aura


#endif //_AuraIOListener_H_
