/*
 * MAORenderable3DLine.cpp
 *
 *  Created on: 28/02/2011
 *      Author: cesar
 */

#include <MAO/MAORenderable3DLine.h>

MAORenderable3DLine::MAORenderable3DLine(const std::string& name, float size,
		int r, int g, int b) :
	MAORenderable3D(name, size) {
	addPropertyInt("r", r);
	addPropertyInt("g", g);
	addPropertyInt("b", b);
	_type = T_MAORENDERABLE3DLINE;

	_x1 = 0;
	_y1 = 0;
	_z1 = 0;

	_x2 = 0;
	_y2 = 0;
	_z2 = 0;

	_mao1 = NULL;
	_mao2 = NULL;
}

MAORenderable3DLine::MAORenderable3DLine(const std::string& name, float size,
		int r, int g, int b, MAOPositionator3D& mao1, MAOPositionator3D& mao2) :
	MAORenderable3D(name, size) {
	_mao1 = &mao1;
	_mao2 = &mao2;

	setVisible(true);

	_x1 = 0;
	_y1 = 0;
	_z1 = 0;

	_x2 = 0;
	_y2 = 0;
	_z2 = 0;

	addPropertyInt("r", r);
	addPropertyInt("g", g);
	addPropertyInt("b", b);

	//Hack
	_globalReference = _mao1;
}



void MAORenderable3DLine::generateCollisionShape(int type) {
	switch (type) {
	case MAO_BOX_SHAPE:{
		float s = getSize();
		Logger::getInstance()->warning("Very innacurate Box Shape for Lines! Could improve!");
		_collisionShape = new btBoxShape(btVector3(s, s, s));
		_collisionShapeType = MAO_BOX_SHAPE;
		break;
	}
	case MAO_SPHERE_SHAPE:
		Logger::getInstance()->error(
				"Sphere Collision Shape not defined for Lines! Bye!");
		throw "Sphere Collision Shape not defined for Lines! Bye!";
		break;
	case MAO_CYLINDER_SHAPE:
		Logger::getInstance()->error(
				"Cylinder Collision Shape not defined for Lines! Bye!");
		throw "Cylinder Collision Shape not defined for Lines! Bye!";

		break;
	case MAO_CONVEXTRIANGLEMESH_SHAPE:
		Logger::getInstance()->error(
				"Triangle Mesh Collision Shape not defined for Lines! Bye!");
		throw "Triangle Mesh Collision Shape not defined for Lines! Bye!";
		break;
	}
}


void MAORenderable3DLine::setPoints(float x1, float y1, float z1, float x2,
		float y2, float z2) {
	_x1 = x1;
	_y1 = y1;
	_z1 = z1;

	_x2 = x2;
	_y2 = y2;
	_z2 = z2;
}

int MAORenderable3DLine::getR() {
	return getProperty("r").getValue<int>();
}

int MAORenderable3DLine::getG() {
	return getProperty("g").getValue<int>();
}

int MAORenderable3DLine::getB() {
	return getProperty("b").getValue<int>();
}

void MAORenderable3DLine::setPointsFromMao() {
	if (_mao1 != NULL && _mao2 != NULL) {
		_x1 = _mao1->getPosMatrix().at<float> (3, 0);
		_y1 = _mao1->getPosMatrix().at<float> (3, 1);
		_z1 = _mao1->getPosMatrix().at<float> (3, 2);

		_x2 = _mao2->getPosMatrix().at<float> (3, 0);
		_y2 = _mao2->getPosMatrix().at<float> (3, 1);
		_z2 = _mao2->getPosMatrix().at<float> (3, 2);
	}
}
void MAORenderable3DLine::_drawMAONoTexture(){
	_drawMAO();
}

void MAORenderable3DLine::_drawMAO() {

	glDisable(GL_LIGHTING);

	glMatrixMode( GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	glLineWidth(getSize());
	glColor3f(getR() / 255.0f, getG() / 255.0f, getB() / 255.0f);

	setPointsFromMao(); //In case we have MAO's

	glBegin(GL_LINES);
	glVertex3f(_x1, _y1, _z1);
	glVertex3f(_x2, _y2, _z2);
	glEnd();

	glEnable(GL_LIGHTING);

	glPopMatrix();
}

MAORenderable3DLine::~MAORenderable3DLine() {
}
