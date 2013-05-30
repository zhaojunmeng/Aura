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

#if OGRE_PLATFORM == OGRE_PLATFORM_ANDROID
#include "AuraEngineAndroid.h"
#else
#include "AuraEngine.h"
#endif

#include "AuraQCARController.h"
#include "AuraJNIUtils.h"

namespace Aura
{

  /*=============================================================================
    | The AuraApplication interface :)
    =============================================================================*/
  class AuraApplication//: public QCAR::UpdateCallback
  {        

  public:
    //virtual void QCAR_onUpdate(QCAR::State& /*state*/)
    //{
      //AuraLog::info("Update callback");
    //}


#if OGRE_PLATFORM == OGRE_PLATFORM_ANDROID
    friend class AuraEngineAndroid;
#else
    friend class AuraEngine;
#endif

    AuraApplication();

    /* Main public methods :) */
    void go();
    void finish();

    virtual void initTracker() = 0;
    void setPause(bool pause){ mPause = pause; }

  protected:
    /* Ogre create scene */
    virtual void createScene() = 0;

    AuraEngine* mEngine;
    Ogre::Root* mRoot;
    Ogre::SceneManager* mSceneManager;
    Ogre::Camera* mCamera;
    Ogre::RenderWindow* mWindow;
    AuraQCARController* mQCARController;

  private:
    void _setupAuraInterface();
    void _setup();
    bool mRunning;
    bool mPause;
  };
}

#endif // Aura application
