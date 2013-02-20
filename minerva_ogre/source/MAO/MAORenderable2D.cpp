/*
 * MAORenderable2D.cpp
 *
 *  Created on: 23/02/2011
 *      Author: cesar
 */

#include <MAO/MAORenderable2D.h>

MAORenderable2D::MAORenderable2D(const std::string& name, const int& x,
		const int& y, const int& width, const int& height) :
	MAO(name) {
        _texture = -1;
	addPropertyBoolean("visible", true);
	addPropertyInt("width", width);
	addPropertyInt("height", height);
	addPropertyInt("x", x);
	addPropertyInt("y", y);
	_type = T_MAORENDERABLE2D;

}

void MAORenderable2D::draw() {
	generateTexFromSDLSurface();//_surface;

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	glDisable(GL_LIGHTING);

	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glBindTexture(GL_TEXTURE_2D, _texture);

	float screenHeight =(float)
			VideoFactory::getInstance()->getMainCamera().getHeight();

	float y2 = screenHeight - getY();

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex2f((GLfloat)getX(), (GLfloat) y2);
	glTexCoord2f(1, 0);
	glVertex2f((GLfloat) getX() + getWidth(), (GLfloat)y2);
	glTexCoord2f(1, 1);
	glVertex2f((GLfloat)getX() + getWidth(), (GLfloat)y2 - getHeight());
	glTexCoord2f(0, 1);
	glVertex2f((GLfloat)getX(), (GLfloat)y2 - getHeight());
	glEnd();

	glDisable(GL_BLEND);
	glEnable(GL_LIGHTING);

	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
}

void MAORenderable2D::genGlTexture(SDL_Surface* surface) {
	GLenum textureFormat;

	if(_texture!=-1){
	  glDeleteTextures(1, &_texture);
	}

	switch (surface->format->BytesPerPixel) {
	case 4: //With alpha channel
		if (surface->format->Rmask == 0x000000ff) {
			textureFormat = GL_RGBA;
		} else {
			textureFormat = GL_BGRA;
		}
		break;

	case 3: // Without alpha channel
		if (surface->format->Rmask == 0x000000ff) {
			textureFormat = GL_RGB;
		} else {
			textureFormat = GL_BGR;
		}
		break;
	default:
		Logger::getInstance()->error(
				"Error determining the texture format. Bytes per pixel: "
						+ surface->format->BitsPerPixel);
	}

	glGenTextures(1, &_texture);

	if (_texture == GL_INVALID_OPERATION) {
		Logger::getInstance()->error("Error processing a texture");
		throw "Error processing a texture";
	}

	glBindTexture(GL_TEXTURE_2D, _texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

	glTexImage2D(GL_TEXTURE_2D, 0, surface->format->BytesPerPixel, surface->w,
			surface->h, 0, textureFormat, GL_UNSIGNED_BYTE, surface->pixels);

}

bool MAORenderable2D::isVisible() {
	return getProperty("visible").getValue<bool> ();
}
void MAORenderable2D::setVisible(bool visible) {
	getProperty("visible").setValue<bool> (visible);
}

int MAORenderable2D::getX() {
	return getProperty("x").getValue<int> ();
}
void MAORenderable2D::setX(int x) {
	getProperty("x").setValue<int> (x);
}

int MAORenderable2D::getY() {
	return getProperty("y").getValue<int> ();
}

void MAORenderable2D::setY(int y) {
	getProperty("y").setValue<int> (y);
}

int MAORenderable2D::getWidth() {
	return getProperty("width").getValue<int> ();
}

void MAORenderable2D::setWidth(int width) {
	getProperty("width").setValue<int> (width);
}

int MAORenderable2D::getHeight() {
	return getProperty("height").getValue<int> ();
}

void MAORenderable2D::setHeight(int height) {
	getProperty("height").setValue<int> (height);
}

MAORenderable2D::~MAORenderable2D() {
}
