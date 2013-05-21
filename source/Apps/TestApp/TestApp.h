#ifndef _TEST_APP_H_
#define _TEST_APP_H_

#include <AuraApplication.h>
#include <AuraIOListener.h>

namespace Aura{

  class TestApp: public AuraApplication , public AuraIOListener
{

 public:
  virtual void setupApp(){
    mIOEngine->setIOCallback(this); // Very important line


    mCamera->setPosition(Ogre::Vector3(5,10,20));
    mCamera->lookAt(Ogre::Vector3(0,0,0));
    mCamera->setNearClipDistance(5);
    mCamera->setFarClipDistance(10000);
    mCamera->setNearClipDistance(0.1);

    Ogre::Entity* sinbad = mSceneManager->createEntity("Sinbad.mesh");
    Ogre::SceneNode* sinbadNode = mSceneManager->getRootSceneNode()->createChildSceneNode("SinbadNode");
    sinbadNode->attachObject(sinbad);
    
   }


  virtual bool keyPressed(const OIS::KeyEvent& evt){ 
     if(evt.key == OIS::KC_ESCAPE){ 
       finish(); 
     } 
   } 

  virtual bool keyReleased(const OIS::KeyEvent& evt){
  }

  virtual bool mouseMoved(const OIS::MouseEvent& evt){
  }

  virtual bool mousePressed(const OIS::MouseEvent& evt, OIS::MouseButtonID id){
  }

  virtual bool mouseReleased(const OIS::MouseEvent& evt, OIS::MouseButtonID id){
  }

  virtual bool touchMoved(const OIS::MultiTouchEvent&){

  }

  virtual bool touchPressed(const OIS::MultiTouchEvent&){
  }

  virtual bool touchReleased(const OIS::MultiTouchEvent&){
  }

  virtual bool touchCancelled(const OIS::MultiTouchEvent&){
  }

  virtual void destroyApp(){
  }

#if OGRE_PLATFORM == OGRE_PLATFORM_ANDROID
 TestApp(struct android_app* state, bool nograb): AuraApplication(state, nograb){}
#else
 TestApp(bool nograb): AuraApplication(nograb){}
#endif

  
  ~TestApp(){

  }


};

}

#endif // _TEST_APP_H
