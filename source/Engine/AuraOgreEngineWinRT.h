#ifndef _AuraOgreEngineWinRT_H_
#define _AuraOgreEngineWinRT_H_

	/*-----------------------------------------------------------------------------
	  | init data members needed only by WinRT
	  -----------------------------------------------------------------------------*/
#if (OGRE_PLATFORM == OGRE_PLATFORM_WINRT)
	void initAppForWinRT( Windows::UI::Core::CoreWindow^ nativeWindow, InputContext inputContext)
	{
	  mNativeWindow = nativeWindow;
#   if (OGRE_WINRT_TARGET_TYPE == DESKTOP_APP)
	  mNativeControl = nullptr;
#	endif // (OGRE_WINRT_TARGET_TYPE == DESKTOP_APP)
	  mInputContext = inputContext;
	}
#	if (OGRE_WINRT_TARGET_TYPE == DESKTOP_APP)
	void initAppForWinRT( Windows::UI::Xaml::Shapes::Rectangle ^ nativeControl, InputContext inputContext)
	{
	  mNativeWindow = nullptr;
	  mNativeControl = nativeControl;
	  mInputContext = inputContext;
	}
#	endif // (OGRE_WINRT_TARGET_TYPE == DESKTOP_APP)
#endif // (OGRE_PLATFORM == OGRE_PLATFORM_WINRT)





	/*-----------------------------------------------------------------------------
	  | Overrides the default window title.
	  -----------------------------------------------------------------------------*/
	virtual Ogre::RenderWindow* createWindow()
	  {
	    Ogre::RenderWindow* res = mRoot->initialise(false, "Aura Application");
	    Ogre::NameValuePairList miscParams;
	    if(mNativeWindow.Get())
	      {
		miscParams["externalWindowHandle"] = Ogre::StringConverter::toString((size_t)reinterpret_cast<void*>(mNativeWindow.Get()));
		res = mRoot->createRenderWindow("Aura Application", mNativeWindow->Bounds.Width, mNativeWindow->Bounds.Height, false, &miscParams);
	      }
#	if (OGRE_WINRT_TARGET_TYPE == DESKTOP_APP)
	    else if(mNativeControl)
	      {
		miscParams["windowType"] = "SurfaceImageSource";
		res = mRoot->createRenderWindow("Aura Application", mNativeControl->ActualWidth, mNativeControl->ActualHeight, false, &miscParams);
		void* pUnk = NULL;
		res->getCustomAttribute("ImageBrush", &pUnk);
		mNativeControl->Fill = reinterpret_cast<Windows::UI::Xaml::Media::ImageBrush^>(pUnk);
	      }
#	endif // (OGRE_WINRT_TARGET_TYPE == DESKTOP_APP)

	    return res;
	  }


#endif // _AuraOgreEngineWinRT_H_
