#include "TestApp.h"

namespace Aura{

  TestApp::TestApp(): AuraApplication(){}

  TestApp::~TestApp(){}

  void TestApp::createScene(){
    // add a bright light above the scene
    Ogre::Light* light = mSceneManager->createLight();
    light->setType(Ogre::Light::LT_POINT);
    light->setPosition(-10, 40, 20);
    light->setSpecularColour(Ogre::ColourValue::White);

    Ogre::Entity* sinbad = mSceneManager->createEntity("Sinbad.mesh");
    Ogre::SceneNode* chipsNode = mSceneManager->getSceneNode("chips");
    Ogre::SceneNode* sinbadNode = chipsNode->createChildSceneNode("sinbadNode");
    sinbadNode->pitch(Ogre::Degree(90));
    sinbadNode->translate(0,0,50);
    sinbadNode->setScale(Ogre::Vector3(10,10,10));
    sinbadNode->attachObject(sinbad);

    // Set animation mode
    sinbad->getSkeleton()->setBlendMode(Ogre::ANIMBLEND_CUMULATIVE);
    
    // Get animations
    sinbadAnims = sinbad->getAllAnimationStates();

    AuraLog::info("Sinbad animations!! ");
    Ogre::AnimationStateIterator it = sinbadAnims->getAnimationStateIterator();
    while(it.hasMoreElements()){
      Ogre::AnimationState* as = it.getNext();
      AuraLog::info(as->getAnimationName());
    }

    
    sinbadAnims->getAnimationState("IdleTop")->setLoop(true);
    sinbadAnims->getAnimationState("IdleTop")->setEnabled(true);

    sinbadAnims->getAnimationState("IdleBase")->setLoop(true);
    sinbadAnims->getAnimationState("IdleBase")->setEnabled(true);
    sinbadAnims->getAnimationState("Dance")->setLoop(true);


    // Sound?
    bank = CkBank::newBank("sound/game.ckb");
    sound = CkSound::newBankSound(bank, 0);
    music = CkSound::newStreamSound("sound/music.cks");

    music->play();
    music->setLoopCount(-1);
  }

  bool TestApp::frameStarted(const Ogre::FrameEvent& evt){
    // Check if the resources are initialized
    sinbadAnims->getAnimationState("IdleTop")->addTime(evt.timeSinceLastFrame);
    sinbadAnims->getAnimationState("IdleBase")->addTime(evt.timeSinceLastFrame);
    sinbadAnims->getAnimationState("Dance")->addTime(evt.timeSinceLastFrame);
      
    return true;
  }

  bool TestApp::frameEnded(const Ogre::FrameEvent& evt){
    return true;
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

 
  bool TestApp::touchMoved(const OIS::MultiTouchEvent&){

  }

  bool TestApp::touchPressed(const OIS::MultiTouchEvent&){
   sound->play();
    if(sinbadAnims->getAnimationState("Dance")->getEnabled()){
      sinbadAnims->getAnimationState("Dance")->setEnabled(false);
    }else{
      sinbadAnims->getAnimationState("Dance")->setEnabled(true);
    }
  }

  bool TestApp::touchReleased(const OIS::MultiTouchEvent&){

  }

  bool TestApp::touchCancelled(const OIS::MultiTouchEvent&){
  }

 bool TestApp::mouseMoved(const OIS::MouseEvent& evt){
  }

  bool TestApp::mousePressed(const OIS::MouseEvent& evt, OIS::MouseButtonID id){
  }

  bool TestApp::mouseReleased(const OIS::MouseEvent& evt, OIS::MouseButtonID id){
  }


  void TestApp::destroyApp(){
  }


}
