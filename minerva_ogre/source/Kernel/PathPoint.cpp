/*
 * MAORenderable3DPathPoint.cpp
 *
 *  Created on: 28/02/2011
 *      Author: cesar
 */

#include <Kernel/PathPoint.h>

PathPoint::PathPoint(float x, float y, float z,
		float size, int r, int g, int b, bool visible) {
	_x = x;
	_y = y;
	_z = z;
	_r = r;
	_g = g;
	_b = b;
	_visible = visible;
	_size = size;
}

float PathPoint::getX() {
	return _x;
}
float PathPoint::getY() {
	return _y;
}
float PathPoint::getZ() {
	return _z;
}
int PathPoint::getR() {
	return _r;
}
int PathPoint::getG() {
	return _g;
}
int PathPoint::getB() {
	return _b;
}

bool PathPoint::getVisible() {
	return _visible;
}

float PathPoint::getSize() {
	return _size;
}

PathPoint::~PathPoint() {
}
