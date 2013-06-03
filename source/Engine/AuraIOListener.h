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
	virtual bool keyPressed(const OIS::KeyEvent& evt){}
	virtual bool keyReleased(const OIS::KeyEvent& evt){}
	virtual bool mouseMoved(const OIS::MouseEvent& evt){}
	virtual bool mousePressed(const OIS::MouseEvent& evt, OIS::MouseButtonID id){}
	virtual bool mouseReleased(const OIS::MouseEvent& evt, OIS::MouseButtonID id){}
	virtual bool touchMoved(const OIS::MultiTouchEvent&){}
	virtual bool touchPressed(const OIS::MultiTouchEvent&){}
	virtual bool touchReleased(const OIS::MultiTouchEvent&){}
	virtual bool touchCancelled(const OIS::MultiTouchEvent&){}

      };

}// Aura


#endif //_AuraIOListener_H_
