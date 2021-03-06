/*
  -----------------------------------------------------------------------------
  This source file is part of OGRE
  (Object-oriented Graphics Rendering Engine)
  For the latest info, see http://www.ogre3d.org/
 
  Copyright (c) 2000-2013 Torus Knot Software Ltd
 
  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:
 
  The above copyright notice and this permission notice shall be included in
  all copies or substantial portions of the Software.
 
  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
  THE SOFTWARE.
  -----------------------------------------------------------------------------
*/
#ifndef __AuraApplication_H__
#define __AuraApplication_H__

#include "OgrePlatform.h"
#include "OgreBuildSettings.h"
#include "AuraQCARController.h"
#include "AuraAudioController.h"
#include "AuraIOListener.h" 

#if OGRE_PLATFORM == OGRE_PLATFORM_ANDROID
# include "Android/AuraJNIUtils.h"
#endif

namespace Aura
{

  /*=============================================================================
    | The AuraApplication interface :)
    =============================================================================*/
  class AuraApplication: public AuraIOListener
  {        

  public:

    AuraApplication();

    /* Main public methods :) */
    virtual void initTracker() = 0;
    /* Ogre create scene */
    virtual void createScene() = 0;
    /* Init audio */
    virtual void initAudio() = 0;
    /* Frame started */
    virtual bool frameStarted(const Ogre::FrameEvent& evt) = 0;  
    /* Frame ended */
    virtual bool frameEnded(const Ogre::FrameEvent& evt) = 0;  
    /* Destroy scene */
    virtual void destroyScene() = 0;

    void setupAuraInterface();
    
    void finish() {
#if OGRE_PLATFORM == OGRE_PLATFORM_ANDROID
      AuraJNIUtils::getInstance()->finishActivity();
#endif
    }

  protected:

    /* Interface :) */
    Ogre::Root* mRoot;
    Ogre::SceneManager* mSceneManager;
    AuraQCARController* mQCARController;
    AuraAudioController* mAudioController;
  };
}

#endif // Aura application
