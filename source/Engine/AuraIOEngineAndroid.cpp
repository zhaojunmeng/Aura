#include "AuraIOEngineAndroid.h"

namespace Aura{

  OIS::MultiTouchState& AndroidMultiTouch::getMultiTouchState(int i){
    while(i >= mStates.size()){
      Ogre::RenderWindow* pRenderWnd = static_cast<Ogre::RenderWindow*>(Ogre::Root::getSingleton().getRenderTarget("AuraWindow"));
      if(pRenderWnd)
	{
	  OIS::MultiTouchState state;
	  state.width = pRenderWnd->getWidth();
	  state.height = pRenderWnd->getHeight();
	  mStates.push_back(state);
	}
    }
    return mStates[i];
  }


  AuraIOEngineAndroid::AuraIOEngineAndroid(){} 
      
  void AuraIOEngineAndroid::injectKeyEvent(int action, int32_t keyCode)
  {
    if(keyCode == AKEYCODE_BACK)
      {
	OIS::KeyEvent evt(mKeyboard, OIS::KC_ESCAPE, 0);
	if(action == 0) {
	    if(mCallback) mCallback->keyPressed(evt);
	}else {
	  if(mCallback) mCallback->keyReleased(evt);
	}
      }
  }
      

  void AuraIOEngineAndroid::injectTouchEvent(int action, float x, float y, int pointerId)
  {
    OIS::MultiTouchState &state = mTouch->getMultiTouchState(pointerId);
            
    switch(action)
      {
      case 0:
	state.touchType = OIS::MT_Pressed;
	break;
      case 1:
	state.touchType = OIS::MT_Released;
	break;
      case 2:
	state.touchType = OIS::MT_Moved;
	break;
      case 3:
	state.touchType = OIS::MT_Cancelled;
	break;
      default:
	state.touchType = OIS::MT_None;
      }
            
    if(state.touchType != OIS::MT_None)
      {
	int last = state.X.abs;
	state.X.abs =  (int)x;
	state.X.rel = state.X.abs - last;
                
	last = state.Y.abs;
	state.Y.abs = (int)y;
	state.Y.rel = state.Y.abs - last;
                
	state.Z.abs = 0;
	state.Z.rel = 0;
                
	OIS::MultiTouchEvent evt(mTouch, state);

	switch(state.touchType)
	  {
	  case OIS::MT_Pressed:
	    if(mCallback) mCallback->touchPressed(evt);
	    break;
	  case OIS::MT_Released:
	    if(mCallback) mCallback->touchReleased(evt);
	    break;
	  case OIS::MT_Moved:
	    if(mCallback) mCallback->touchMoved(evt);
	    break;
	  case OIS::MT_Cancelled:
	    if(mCallback) mCallback->touchCancelled(evt);
	    break;
	  default:
	    break;
	  }
      }
  }


  void AuraIOEngineAndroid::setupInput(Ogre::RenderWindow *mWindow)
  {
    mTouch = new AndroidMultiTouch();
    mKeyboard = new AndroidKeyboard();
  }


  void AuraIOEngineAndroid::shutdownInput()
  {
    delete mTouch;
    mTouch = NULL;
            
    delete mKeyboard;
    mKeyboard = NULL;
  }

}
