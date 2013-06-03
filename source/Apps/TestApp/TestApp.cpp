#include "TestApp.h"

namespace Aura{

  TestApp::TestApp(): AuraApplication(){}

  TestApp::~TestApp(){}

  void TestApp::createScene(){
 
    Ogre::Entity* sinbad = mSceneManager->createEntity("Sinbad.mesh");
    Ogre::SceneNode* chipsNode = mSceneManager->getSceneNode("chips");
    Ogre::SceneNode* sinbadNode = chipsNode->createChildSceneNode("sinbadNode");
    sinbadNode->setScale(Ogre::Vector3(10,10,10));
    sinbadNode->attachObject(sinbad);

  }

  void TestApp::initTracker(){
    // Loading the data :)
  //    This creates a scene node "chips" and "stones"
       mQCARController->loadImageData("StonesAndChips", "ar/StonesAndChips.xml");
  }

  bool TestApp::keyPressed(const OIS::KeyEvent& evt){ 
    if(evt.key == OIS::KC_ESCAPE){ 
      finish(); 
    } 
  } 

  bool TestApp::keyReleased(const OIS::KeyEvent& evt){
  }

  bool TestApp::mouseMoved(const OIS::MouseEvent& evt){
  }

  bool TestApp::mousePressed(const OIS::MouseEvent& evt, OIS::MouseButtonID id){
  }

  bool TestApp::mouseReleased(const OIS::MouseEvent& evt, OIS::MouseButtonID id){
  }

  bool TestApp::touchMoved(const OIS::MultiTouchEvent&){

  }

  bool TestApp::touchPressed(const OIS::MultiTouchEvent&){
  }

  bool TestApp::touchReleased(const OIS::MultiTouchEvent&){
  }

  bool TestApp::touchCancelled(const OIS::MultiTouchEvent&){
  }

  void TestApp::destroyApp(){
  }


}
