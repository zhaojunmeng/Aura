/*
 * World.h
 *
 *  Created on: 21/02/2011
 *      Author: cesar
 */

#ifndef WORLD_H_
#define WORLD_H_

#include <SDL.h>
#include <SDL_mixer.h>
#include <cv.h>
#include <Ogre.h>
#include <OIS.h>
#include <MAO/MAORenderable3D.h>
#include <Controllers/PhysicsController.h>
#include <Kernel/EndController.h>
#include <Factories/VideoFactory.h>
#include <Factories/MAOFactory.h>
#include <Kernel/Logger.h>
#include <Kernel/Singleton.h>

class World: public Singleton<World>,
		public Ogre::FrameListener,
		public Ogre::WindowEventListener {

	Ogre::RenderWindow* _window;
	Ogre::Camera* _cam;
	Ogre::SceneManager* _sceneManager;
	Ogre::Root* _root;
	std::string _appName;

	void windowClosed(Ogre::RenderWindow* win);
	void _refreshBackground();
	void _createBackground();

	int _width,  _height;

public:
	World();
	virtual ~World();
	void initWorld(int width, int height);
	void drawWorld();

	Ogre::SceneManager* getSceneManager(){ return _sceneManager; }
	int getWidth() { return _width; }
	int getHeight(){ return _height; }
	Ogre::RenderWindow* getRenderWindow(){ return _window; }

	const std::string& getAppName() {
		return _appName;
	}
	void setAppName(const std::string& appName) {
		_appName = appName;
	}

	bool frameStarted(const Ogre::FrameEvent& evt);

};

#endif /* WORLD_H_ */
