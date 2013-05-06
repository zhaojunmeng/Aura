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

	addPropertyBoolean("visible", true);
	addPropertyInt("width", width);
	addPropertyInt("height", height);
	addPropertyInt("x", x);
	addPropertyInt("y", y);
	_type = T_MAORENDERABLE2D;

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
