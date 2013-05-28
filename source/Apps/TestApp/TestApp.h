
#ifndef _TEST_APP_H_
#define _TEST_APP_H_

#include <AuraApplication.h>
#include <AuraIOListener.h>

namespace Aura{

  class TestApp: public AuraApplication , public AuraIOListener
{

 public:
  virtual void createScene(){
    // Set the IO Callback
    mEngine->setIOCallback(this); // Very important line
    
    Ogre::Entity* sinbad = mSceneManager->createEntity("Sinbad.mesh");
    //    Ogre::SceneNode* sinbadNode = mSceneManager->getSceneNode("chips");
    Ogre::SceneNode* sinbadNode = mSceneManager->getRootSceneNode()->createChildSceneNode("sinbad");
    sinbadNode->setScale(Ogre::Vector3(10,10,10));
    sinbadNode->attachObject(sinbad);
    
   }

  virtual void initTracker(){
    // Loading the data :)
    mQCARController->loadImageData("StonesAndChips", "StonesAndChips.xml");
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

 TestApp(): AuraApplication(){}

  
  ~TestApp(){

  }


};

}

#endif // _TEST_APP_H
