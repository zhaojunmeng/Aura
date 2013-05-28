
#ifndef _AURAIOSENGINE_H
#define _AURAIOSENGINE_H

#include <OIS/OIS.h>
#include "Ogre.h"
#include "AuraIOListener.h"
#include "Singleton.h"

#if OIS_VERSION >= 0x010300		//  OIS_VERSION >= 1.3.0
#define OIS_WITH_MULTITOUCH		1
#else							//  OIS_VERSION == 1.2.0
#define OIS_WITH_MULTITOUCH		0
#endif

namespace Aura{

  class AuraIOEngine
    {
    public:

      AuraIOEngine();

      virtual void capture() const;
      bool isKeyDown(OIS::KeyCode key) const;
      bool getCursorPosition(Ogre::Real& x, Ogre::Real& y);
      virtual void setIOCallback(AuraIOListener* callback);
      virtual void setupInput(Ogre::RenderWindow *mWindow);
      virtual void createInputDevices();
      virtual void shutdownInput();

    protected:
      bool mNoGrabInput;  // don't grab input devices	
      OIS::InputManager* mInputMgr;   // OIS input manager
      OIS::Keyboard* mKeyboard;         // context keyboard device
      OIS::Mouse* mMouse;               // context mouse device
#if OIS_WITH_MULTITOUCH
      OIS::MultiTouch* mMultiTouch;     // context multitouch device
#endif
      OIS::JoyStick* mAccelerometer;    // context accelerometer device
    };

} // Aura

#endif // _AURAIOSENGINE_H_
