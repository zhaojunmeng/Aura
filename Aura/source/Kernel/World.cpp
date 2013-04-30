/*
 * World.cpp
 *
 *  Created on: 21/02/2011
 *      Author: cesar
 */

#include <Kernel/World.h>

World::World(): _width(640), _height(480) {
}

void World::initWorld(int width, int height) {
	Logger::getInstance()->out("Initializing world...");

	/* Name */
	_appName = "ABBY";

	_width = width;
	_height = height;

	/* Audio */
	if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT,
			MIX_DEFAULT_CHANNELS, 4096) < 0) { //Init audio subsystem
		Logger::getInstance()->error("Error opening audio subsystem!");
	} else {
		Logger::getInstance()->out("Mixer audio opened succesfully!");
		if (Mix_AllocateChannels(4) < 0)
			Logger::getInstance()->error(
					("Error allocating channels for Sdl Mixel"));
	}

	/* Ogre ;) */
	_root = new Ogre::Root("config/plugins.cfg", "config/ogre.cfg", "Ogre.log");
	_root->addFrameListener(this);

	//Deactivating the Ogre Log Console
	//Ogre::LogManager::getSingleton().getDefaultLog()->setDebugOutputEnabled(false);

	if (!_root->restoreConfig()) {
		_root->showConfigDialog();
		_root->saveConfig();
	}

	_window = _root->initialise(true, _appName);
	Ogre::WindowEventUtilities::addWindowEventListener(_window, this);

	_sceneManager = _root->createSceneManager(Ogre::ST_GENERIC, "SceneManager");

	_cam = _sceneManager->createCamera("Camera");
	_cam->setPosition(Ogre::Vector3(0, 0, 0));
	_cam->lookAt(Ogre::Vector3(0, 0, -1));
	_cam->setNearClipDistance(0.001);
	_cam->setFarClipDistance(20);
	_cam->setAspectRatio(width / (float) height);
	_cam->setFOVy(Ogre::Degree(45));

	Ogre::Viewport* viewport = _window->addViewport(_cam);
	viewport->setBackgroundColour(Ogre::ColourValue(0.0, 0.0, 0.0));

	{
		Ogre::ConfigFile cf;
		cf.load("config/resources.cfg");

		Ogre::ConfigFile::SectionIterator sI = cf.getSectionIterator();
		Ogre::String sectionstr, typestr, datastr;
		while (sI.hasMoreElements()) {
			sectionstr = sI.peekNextKey();
			Ogre::ConfigFile::SettingsMultiMap *settings = sI.getNext();
			Ogre::ConfigFile::SettingsMultiMap::iterator i;
			for (i = settings->begin(); i != settings->end(); ++i) {
				typestr = i->first;
				datastr = i->second;
				Ogre::ResourceGroupManager::getSingleton().addResourceLocation(
						datastr, typestr, sectionstr);
			}
		}
		Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
	}

	_createBackground();

	Logger::getInstance()->out("World succesfully loaded!");
}

void World::drawWorld() {
	Ogre::WindowEventUtilities::messagePump();
	if (!_root->renderOneFrame()) {
		EndController::getInstance()->end();
	}

	//Draw renderable3D
	std::vector<MAORenderable3D*>& renderables3d =
			MAOFactory::getInstance()->getVectorMAORenderable3D();

	for (unsigned int i = 0; i < renderables3d.size(); i++)
		renderables3d.at(i)->update();


	//Draw Instantiated renderable3D
	std::vector<MAORenderable3D*>& renderables3dInst =
			MAOFactory::getInstance()->getVectorInstMAORenderable3D();
	for (unsigned int i = 0; i < renderables3dInst.size(); i++)
		renderables3dInst.at(i)->update();

}

void World::windowClosed(Ogre::RenderWindow* win) {
	EndController::getInstance()->end();
}

bool World::frameStarted(const Ogre::FrameEvent& evt) {
	_refreshBackground();

	return true;
}

void World::_createBackground() {
	VideoFactory::getInstance()->getMainCamera().grabFrame();
	cv::Mat* frame =
			VideoFactory::getInstance()->getMainCamera().getLastFrame();

	/* Ogre code */
	Ogre::TexturePtr texture =
			Ogre::TextureManager::getSingleton().createManual(
					"BackgroundTex",	// name
					Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
					Ogre::TEX_TYPE_2D,	// texture type
					frame->cols, frame->rows,
					0,	// number of mipmaps
					Ogre::PF_BYTE_BGRA,
					Ogre::HardwareBuffer::HBU_DYNAMIC_WRITE_ONLY_DISCARDABLE);

	Ogre::MaterialPtr material = Ogre::MaterialManager::getSingleton().create(
			"Background",
			Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
	material->getTechnique(0)->getPass(0)->createTextureUnitState();
	material->getTechnique(0)->getPass(0)->setSceneBlending(
			Ogre::SBT_TRANSPARENT_ALPHA);
	material->getTechnique(0)->getPass(0)->setDepthCheckEnabled(false);
	material->getTechnique(0)->getPass(0)->setDepthWriteEnabled(false);
	material->getTechnique(0)->getPass(0)->setLightingEnabled(false);
	material->getTechnique(0)->getPass(0)->getTextureUnitState(0)->setTextureName(
			"BackgroundTex");

	// Create background rectangle covering the whole screen
	Ogre::Rectangle2D* rect = new Ogre::Rectangle2D(true);
	rect->setCorners(-1.0, 1.0, 1.0, -1.0);
	rect->setMaterial("Background");

	// Render the background before everything else
	rect->setRenderQueueGroup(Ogre::RENDER_QUEUE_BACKGROUND);

	rect->setBoundingBox(
			Ogre::AxisAlignedBox(-100000.0 * Ogre::Vector3::UNIT_SCALE,
					100000.0 * Ogre::Vector3::UNIT_SCALE));

	// Attach background to the scene
	Ogre::SceneNode* node =	_sceneManager->getRootSceneNode()->createChildSceneNode(
					"BackgroundNode");
	node->attachObject(rect);
}

void World::_refreshBackground() {
	cv::Mat* frame =
			VideoFactory::getInstance()->getMainCamera().getLastFrame();
	if (frame->rows == 0)
		return;

	Ogre::TexturePtr texture = Ogre::TextureManager::getSingleton().getByName(
			"BackgroundTex",
			Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);

	Ogre::HardwarePixelBufferSharedPtr pixelBuffer = texture->getBuffer();

	pixelBuffer->lock(Ogre::HardwareBuffer::HBL_DISCARD);
	const Ogre::PixelBox& pixelBox = pixelBuffer->getCurrentLock();

	Ogre::uint8* pDest = static_cast<Ogre::uint8*>(pixelBox.data);

	for (int j = 0; j < frame->rows; j++) {
		for (int i = 0; i < frame->cols; i++) {
			int idx = ((j) * pixelBox.rowPitch + i) * 4; //Use pixelBox.rowPitch instead of "width"
			pDest[idx] = frame->data[(j * frame->cols + i) * 3];
			pDest[idx + 1] = frame->data[(j * frame->cols + i) * 3 + 1];
			pDest[idx + 2] = frame->data[(j * frame->cols + i) * 3 + 2];
			pDest[idx + 3] = 255;
		}
	}

	pixelBuffer->unlock();

	Ogre::Rectangle2D* rect =
			static_cast<Ogre::Rectangle2D*>(_sceneManager->getSceneNode(
					"BackgroundNode")->getAttachedObject(0));
	Ogre::MaterialPtr material = rect->getMaterial();

}

World::~World() {
	Mix_CloseAudio();
}
