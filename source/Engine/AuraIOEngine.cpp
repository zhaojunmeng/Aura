#include "AuraIOEngine.h"

namespace Aura{

  AuraIOEngine::AuraIOEngine(){
    mNoGrabInput = true;
    mKeyboard = 0;
    mMouse = 0;
#if OIS_WITH_MULTITOUCH
    mMultiTouch = 0;
#endif
    mAccelerometer = 0;
    mCallback = 0;
  }

  void AuraIOEngine::capture() const
  {
    if(mKeyboard)
      mKeyboard->capture();
    if(mMouse)
      mMouse->capture();
#if OIS_WITH_MULTITOUCH
    if(mMultiTouch)
      mMultiTouch->capture();
#endif
    if(mAccelerometer)
      mAccelerometer->capture();
  }
  
  bool AuraIOEngine::isKeyDown(OIS::KeyCode key) const
  {
    return mKeyboard && mKeyboard->isKeyDown(key);
  }
  
  bool AuraIOEngine::getCursorPosition(Ogre::Real& x, Ogre::Real& y)
  {
    // prefer mouse
    if(mMouse)
      {
	x = (Ogre::Real)mMouse->getMouseState().X.abs;
	y = (Ogre::Real)mMouse->getMouseState().Y.abs;
	return true;
      }
    
#if OIS_WITH_MULTITOUCH
    // than touch device
    if(mMultiTouch)
      {
	std::vector<OIS::MultiTouchState> states = mMultiTouch->getMultiTouchStates();
	if(states.size() > 0)
	  {
	    x = (Ogre::Real)states[0].X.abs;
	    y = (Ogre::Real)states[0].Y.abs;
	    return true;
	  }
      }
#endif
    
    // fallback
    x = y = 0.0;
    return false;
  }
  
  void AuraIOEngine::setIOCallback(AuraIOListener* callback){
    mCallback = callback;

#if (OGRE_PLATFORM != OGRE_PLATFORM_APPLE_IOS) && (OGRE_PLATFORM != OGRE_PLATFORM_ANDROID)
    if(mKeyboard)
      mKeyboard->setEventCallback(callback);
    if(mMouse)
      mMouse->setEventCallback(callback);
#else
    if(mMultiTouch)
      mMultiTouch->setEventCallback(callback);
#endif
    
  }


  void AuraIOEngine::setupInput(Ogre::RenderWindow *mWindow)
  {
#if OGRE_PLATFORM != OGRE_PLATFORM_ANDROID
    OIS::ParamList pl;
    size_t winHandle = 0;
    std::ostringstream winHandleStr;
	  
    mWindow->getCustomAttribute("WINDOW", &winHandle);
    winHandleStr << winHandle;
	  
    pl.insert(std::make_pair("WINDOW", winHandleStr.str()));
    if (mNoGrabInput)
      {
	pl.insert(std::make_pair("x11_keyboard_grab", "false"));
	pl.insert(std::make_pair("x11_mouse_grab", "false"));
	pl.insert(std::make_pair("w32_mouse", "DISCL_FOREGROUND"));
	pl.insert(std::make_pair("w32_mouse", "DISCL_NONEXCLUSIVE"));
	pl.insert(std::make_pair("w32_keyboard", "DISCL_FOREGROUND"));
	pl.insert(std::make_pair("w32_keyboard", "DISCL_NONEXCLUSIVE"));
      }
	  
    mInputMgr = OIS::InputManager::createInputSystem(pl);

    createInputDevices();      // create the specific input devices
#endif
  }


  void AuraIOEngine::createInputDevices()
  {
#if OGRE_PLATFORM == OGRE_PLATFORM_APPLE_IOS
    mMultiTouch = static_cast<OIS::MultiTouch*>(mInputMgr->createInputObject(OIS::OISMultiTouch, true));
    mAccelerometer = static_cast<OIS::JoyStick*>(mInputMgr->createInputObject(OIS::OISJoyStick, true));
#elif OGRE_PLATFORM == OGRE_PLATFORM_ANDROID
    // nothing to do
#else
    mKeyboard = static_cast<OIS::Keyboard*>(mInputMgr->createInputObject(OIS::OISKeyboard, true));
    mMouse = static_cast<OIS::Mouse*>(mInputMgr->createInputObject(OIS::OISMouse, true));
#endif
  }


  /*-----------------------------------------------------------------------------
    | Destroys OIS input devices and the input manager.
    -----------------------------------------------------------------------------*/
  void AuraIOEngine::shutdownInput()
  {
    // detach input devices
    if(mKeyboard)
      mKeyboard->setEventCallback(NULL);

    if(mMouse)
      mMouse->setEventCallback(NULL);

#if OIS_WITH_MULTITOUCH
    if(mMultiTouch)
      mMultiTouch->setEventCallback(NULL);
#endif
    if(mAccelerometer)
      mAccelerometer->setEventCallback(NULL);

    // Destroy resources	  
#if OGRE_PLATFORM != OGRE_PLATFORM_ANDROID && OGRE_PLATFORM != OGRE_PLATFORM_WINRT
    if (mInputMgr)
      {
	if(mKeyboard)
	  mInputMgr->destroyInputObject(mKeyboard);
	if(mMouse)
	  mInputMgr->destroyInputObject(mMouse);
#  if OIS_WITH_MULTITOUCH
	if(mMultiTouch)
	  mInputMgr->destroyInputObject(mMultiTouch);
#  endif
	if(mAccelerometer)
	  mInputMgr->destroyInputObject(mAccelerometer);
	      
	OIS::InputManager::destroyInputSystem(mInputMgr);
	mInputMgr = 0;
      }
#endif
  }




// #if (OGRE_NO_VIEWPORT_ORIENTATIONMODE == 0)
//         void transformInputState(OIS::MultiTouchState &state) {
//             int w = mWindow->getViewport(0)->getActualWidth();
//             int h = mWindow->getViewport(0)->getActualHeight();
//             int absX = state.X.abs;
//             int absY = state.Y.abs;
//             int relX = state.X.rel;
//             int relY = state.Y.rel;

//             switch (mWindow->getViewport(0)->getOrientationMode()){
//             case Ogre::OR_DEGREE_0:
//                 break;
//             case Ogre::OR_DEGREE_90:
//                 state.X.abs = w - absY;
//                 state.Y.abs = absX;
//                 state.X.rel = -relY;
//                 state.Y.rel = relX;
//                 break;
//             case Ogre::OR_DEGREE_180:
//                 state.X.abs = w - absX;
//                 state.Y.abs = h - absY;
//                 state.X.rel = -relX;
//                 state.Y.rel = -relY;
//                 break;
//             case Ogre::OR_DEGREE_270:
//                 state.X.abs = absY;
//                 state.Y.abs = h - absX;
//                 state.X.rel = relY;
//                 state.Y.rel = -relX;
//                 break;
//             }
//         }

// #elif (OGRE_NO_VIEWPORT_ORIENTATIONMODE == 1) && (OGRE_PLATFORM == OGRE_PLATFORM_APPLE_IOS)
//     // Variation based upon device orientation for use with a view controller
//     void transformInputState(OIS::MultiTouchState &state)
//     {
//         int w = mWindow->getViewport(0)->getActualWidth();
//         int h = mWindow->getViewport(0)->getActualHeight();
//         int absX = state.X.abs;
//         int absY = state.Y.abs;
//         int relX = state.X.rel;
//         int relY = state.Y.rel;

//         UIInterfaceOrientation interfaceOrientation = [UIApplication sharedApplication].statusBarOrientation;
//         switch (interfaceOrientation)
//         {
//             case UIInterfaceOrientationPortrait:
//                 break;
//             case UIInterfaceOrientationLandscapeLeft:
//                 state.X.abs = w - absY;
//                 state.Y.abs = absX;
//                 state.X.rel = -relY;
//                 state.Y.rel = relX;
//                 break;
//             case UIInterfaceOrientationPortraitUpsideDown:
//                 state.X.abs = w - absX;
//                 state.Y.abs = h - absY;
//                 state.X.rel = -relX;
//                 state.Y.rel = -relY;
//                 break;
//             case UIInterfaceOrientationLandscapeRight:
//                 state.X.abs = absY;
//                 state.Y.abs = h - absX;
//                 state.X.rel = relY;
//                 state.Y.rel = -relX;
//                 break;
//         }
//     }
// #endif



}
