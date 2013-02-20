/*
 * World.cpp
 *
 *  Created on: 21/02/2011
 *      Author: cesar
 */

#include <Kernel/World.h>

World::World() {
}

void World::initWorld(int width, int height) {
	Logger::getInstance()->out("Initializing world...");



	_appName = "Minerva's Application";

	_width = width;
	_height = height;

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
		Logger::getInstance()->error("Unable to initalize SDL!");
		throw "Unable to initalize SDL!";
	}

	//const SDL_VideoInfo* info = NULL;
	//info = SDL_GetVideoInfo();

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	_screen = SDL_SetVideoMode(640, 480, 32, SDL_HWSURFACE | SDL_OPENGL
			| SDL_HWPALETTE);

	if (TTF_Init() == -1) { //Init font subsystem
		Logger::getInstance()->error("Error initializing TTF subsystem.");
		Logger::getInstance()->error(TTF_GetError());
		throw "Error initializing TTF subsystem.";
	}

	if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT,
			MIX_DEFAULT_CHANNELS, 4096) < 0) { //Init audio subsystem
		Logger::getInstance()->error("Error opening audio subsystem!");
	} else {
		Logger::getInstance()->out("Mixer audio opened succesfully!");
		if (Mix_AllocateChannels(4) < 0)
			Logger::getInstance()->error(
					("Error allocating channels for Sdl Mixel"));
	}


	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.f, (GLfloat) 640 / (GLfloat) 480, .001f, 20.f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	Logger::getInstance()->out("World succesfully loaded!");
}

void World::drawWorld() {
	glClearDepth(1.0f);
	glClear(GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	//Draw the camera frame
	drawBackground();

	//Draw the ground plane / grid, etc..
	drawGround();


	//Drawing shadows of 3D renderables!
	if (PhysicsController::getInstance()->shadowsActive()) {
		drawShadows();
	}

	//Draw renderable3D
	std::vector<MAORenderable3D*>& renderables3d =
			MAOFactory::getInstance()->getVectorMAORenderable3D();

	for (unsigned int i = 0; i < renderables3d.size(); i++)
		if (renderables3d.at(i)->isVisible()) {
			renderables3d.at(i)->draw();
		}

	//Draw Instantiated renderable3D
	std::vector<MAORenderable3D*>& renderables3dInst =
			MAOFactory::getInstance()->getVectorInstMAORenderable3D();
	for (unsigned int i = 0; i < renderables3dInst.size(); i++)
		if (renderables3dInst.at(i)->isVisible()) {
			renderables3dInst.at(i)->draw();
		}


	//Draw Physics DebugWorld!
	//PhysicsController::getInstance()->drawDebugWorld();

	glDisable(GL_DEPTH_TEST);

	enable2D();

	//Draw renderable 2D
	std::vector<MAORenderable2D*>& renderables2d =
			MAOFactory::getInstance()->getVectorMAORenderable2D();
	for (unsigned int i = 0; i < renderables2d.size(); i++)
		if (renderables2d.at(i)->isVisible())
			renderables2d.at(i)->draw();

	disable2D();

	SDL_GL_SwapBuffers();
}

void World::drawGround() {
	if(!PhysicsController::getInstance()->isActive()) return;

	MAOPositionator3D& ground =
			PhysicsController::getInstance()->getMAOGround();
	bool drawPlane = true;

	if (drawPlane && ground.isPositioned()) {
		GLfloat planeScale = .2;
		cv::Mat& mground = ground.getPosMatrix();
		btVector3 vx(mground.at<float> (0, 0), mground.at<float> (0, 1),
				mground.at<float> (0, 2));
		btVector3 vy(mground.at<float> (1, 0), mground.at<float> (1, 1),
				mground.at<float> (1, 2));
		btVector3 vz(mground.at<float> (2, 0), mground.at<float> (2, 1),
				mground.at<float> (2, 2));
		btVector3 p(mground.at<float> (3, 0), mground.at<float> (3, 1),
				mground.at<float> (3, 2));
		GLfloat E = -0.001; /* Micro gap between the plane ground and the shadows */

		glDisable(GL_TEXTURE_2D);
		glColor3f(.9, .9, .9);

		/* Drawing the ground plane! */
		glBegin(GL_POLYGON);
		glVertex3f(p.x() + planeScale * (+vx.x() + vy.x()), p.y() + planeScale
				* (+vx.y() + vy.y()) - E, p.z() + planeScale * (+vx.z()
				+ vy.z()));
		glVertex3f(p.x() + planeScale * (+vx.x() - vy.x()), p.y() + planeScale
				* (+vx.y() - vy.y()) - E, p.z() + planeScale * (+vx.z()
				- vy.z()));
		glVertex3f(p.x() + planeScale * (-vx.x() - vy.x()), p.y() + planeScale
				* (-vx.y() - vy.y()) - E, p.z() + planeScale * (-vx.z()
				- vy.z()));
		glVertex3f(p.x() + planeScale * (-vx.x() + vy.x()), p.y() + planeScale
				* (-vx.y() + vy.y()) - E, p.z() + planeScale * (-vx.z()
				+ vy.z()));
		glEnd();
	}
}

void World::drawShadows() {

	if(!PhysicsController::getInstance()->isActive()) return;

	MAOPositionator3D& ground =
			PhysicsController::getInstance()->getMAOGround();

	if (ground.isPositioned()) {
		cv::Mat& mground = ground.getPosMatrix();
		btVector3 vx(mground.at<float> (0, 0), mground.at<float> (0, 1),
				mground.at<float> (0, 2));
		btVector3 vy(mground.at<float> (1, 0), mground.at<float> (1, 1),
				mground.at<float> (1, 2));
		btVector3 vz(mground.at<float> (2, 0), mground.at<float> (2, 1),
				mground.at<float> (2, 2));
		btVector3 p(mground.at<float> (3, 0), mground.at<float> (3, 1),
				mground.at<float> (3, 2));

		//Calculating the shadow
		float* res = PhysicsController::getInstance()->getShadowsMatrix();

		glPushMatrix();
		glDisable(GL_LIGHTING);


		glDisable(GL_TEXTURE_2D);
		glDisable(GL_DEPTH_TEST);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

		glLoadIdentity();
		glColor4f(0.3, 0.3, 0.3,0.3);

		/*Drawing shadows!*/
		//Draw Renderable3D's Shadows
		std::vector<MAORenderable3D*>& renderables3d =
				MAOFactory::getInstance()->getVectorMAORenderable3D();

		for (unsigned int i = 0; i < renderables3d.size(); i++) {
			if (renderables3d.at(i)->isVisible()) {
				glPushMatrix();
				float* renderablePosMatrix =
						(float*) renderables3d.at(i)->getPosMatrix().data;
				glMultMatrixf(res);
				glMultMatrixf(renderablePosMatrix);
				renderables3d.at(i)->drawNoTexture();
				glPopMatrix();
			}
		}

		/* Draw Instantiated Renderable3D's Shadows */
		std::vector<MAORenderable3D*>& renderables3dInst =
				MAOFactory::getInstance()->getVectorInstMAORenderable3D();
		for (unsigned int i = 0; i < renderables3dInst.size(); i++) {
			if (renderables3dInst.at(i)->isVisible()) {
				glPushMatrix();
				float* renderablePosMatrix =
						(float*) renderables3dInst.at(i)->getPosMatrix().data;
				glMultMatrixf(res);
				glMultMatrixf(renderablePosMatrix);
				renderables3dInst.at(i)->drawNoTexture();
				glPopMatrix();
			}
		}

		//Ending Shadows Draw
		glDisable(GL_BLEND);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_LIGHTING);
		glEnable(GL_TEXTURE_2D);
		glPopMatrix();

	}
}

void World::drawBackground() {
	cv::Mat* frame = VideoFactory::getInstance()->getMainCamera().getLastFrame();

	unsigned int textureId;
	glGenTextures(1, &textureId);

	if (textureId == GL_INVALID_OPERATION) {
	  Logger::getInstance()->warning("Error processing a frame texture");
	  return;
	}

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glBindTexture(GL_TEXTURE_2D, textureId);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, frame->cols, frame->rows,0, GL_BGR, GL_UNSIGNED_BYTE, frame->data);



	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0,1,1,0,-1,1);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();


	glDisable(GL_DEPTH_TEST);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textureId);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glBegin(GL_QUADS);
	        glTexCoord2f(0,0);
		glVertex2f(0,0);

		glTexCoord2f(1,0);
		glVertex2f(1,0);

		glTexCoord2f(1,1);
		glVertex2f(1,1);

		glTexCoord2f(0,1);
		glVertex2f(0,1);
	glEnd();
	glDeleteTextures(1,&textureId);
	glDisable(GL_TEXTURE_2D);


	glEnable(GL_DEPTH_TEST);

	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
}

void World::enable2D() {
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0, _width, 0, _height, -1., 1.);
}

void World::disable2D() {
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
}

int World::getWidth() {
	return _width;
}

int World::getHeight() {
	return _height;
}

SDL_Surface& World::getScreen() {
	return *_screen;
}


World::~World() {
	SDL_Quit();
	TTF_Quit();
	Mix_CloseAudio();
}
