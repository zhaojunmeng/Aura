#ifndef _AURAIOENGINEANDROID_H_
#define _AURAIOENGINEANDROID_H_

#include "AuraIOEngine.h"
#include <android_native_app_glue.h>

namespace Aura{

  /*=============================================================================
    | Android input handling
    =============================================================================*/
  class AndroidMultiTouch : public OIS::MultiTouch
    {
    public:
    AndroidMultiTouch():OIS::MultiTouch("DWM", false, 0, 0){}
      
      /** @copydoc Object::setBuffered */
      virtual void setBuffered(bool buffered){}
      
      /** @copydoc Object::capture */
      virtual void capture(){}
      
      /** @copydoc Object::queryInterface */
      virtual OIS::Interface* queryInterface(OIS::Interface::IType type) {return 0;}
      
      /** @copydoc Object::_initialize */
      virtual void _initialize(){}
      
      OIS::MultiTouchState &getMultiTouchState(int i);
    };
    
  class AndroidKeyboard : public OIS::Keyboard
    {
    public:
    AndroidKeyboard():OIS::Keyboard("DWM", false, 1, 0){}
        
      /** @copydoc Object::setBuffered */
      virtual void setBuffered(bool buffered){}
        
      /** @copydoc Object::capture */
      virtual void capture(){}
        
      /** @copydoc Object::queryInterface */
      virtual OIS::Interface* queryInterface(OIS::Interface::IType type) {return 0;}
        
      /** @copydoc Object::_initialize */
      virtual void _initialize(){}
        
      virtual bool isKeyDown( OIS::KeyCode key ) const{
	return false;
      }
        
      virtual const std::string& getAsString( OIS::KeyCode kc ){
	static std::string defstr = "";
	return defstr;
      }
        
      virtual void copyKeyStates( char keys[256] ) const{
            
      }
    };
    
  /*=============================================================================
    | Android input injection
    =============================================================================*/
  class AuraIOEngineAndroid: public AuraIOEngine
  {
        
  public:
        
    AuraIOEngineAndroid();

    void injectKeyEvent(int action, int32_t keyCode);
    void injectTouchEvent(int action, float x, float y, int pointerId = 0);
    virtual void setupInput(Ogre::RenderWindow *mWindow);
    virtual void shutdownInput();
    virtual void setIOCallback(AuraIOListener* callback);
    virtual void capture(){
      // Nothing to do. Handled by Android callback
    }


  private:
    AuraIOListener* mCallback;
    AndroidMultiTouch* mTouch;
  };


} // Aura

#endif // _AURAIOENGINEANDROID_H_
