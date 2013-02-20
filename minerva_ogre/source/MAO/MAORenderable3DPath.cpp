/*
 * MAORenderable3DPath.cpp
 *
 *  Created on: 28/02/2011
 *      Author: cesar
 */

#include <MAO/MAORenderable3DPath.h>

MAORenderable3DPath::MAORenderable3DPath(const std::string& name, float size,
		int r, int g, int b) :
	MAORenderable3D(name, size) {
	addPropertyInt("r", r);
	addPropertyInt("g", g);
	addPropertyInt("b", b);
	addPropertyBoolean("visiblePoint", false);
	Logger::getInstance()->warning(
			"The variable \"visiblePoint\" is set to False at first in MAO Renderable 3D Path!: "
					+ name);
	_type = T_MAORENDERABLE3DPATH;
}


void MAORenderable3DPath::generateCollisionShape(int type) {
	switch (type) {
	case MAO_BOX_SHAPE:{
		float s = getSize();
		Logger::getInstance()->warning("Very innacurate Box Shape for Paths! Could improve!");
		_collisionShape = new btBoxShape(btVector3(s, s, s));
		_collisionShapeType = MAO_BOX_SHAPE;
		break;
	}
	case MAO_SPHERE_SHAPE:
		Logger::getInstance()->error(
				"Sphere Collision Shape not defined for Paths! Bye!");
		throw "Sphere Collision Shape not defined for Paths! Bye!";
		break;
	case MAO_CYLINDER_SHAPE:
		Logger::getInstance()->error(
				"Cylinder Collision Shape not defined for Paths! Bye!");
		throw "Cylinder Collision Shape not defined for Paths! Bye!";

		break;
	case MAO_CONVEXTRIANGLEMESH_SHAPE:
		Logger::getInstance()->error(
				"Triangle Mesh Collision Shape not defined for Paths! Bye!");
		throw "Triangle Mesh Collision Shape not defined for Paths! Bye!";
		break;
	}
}

void MAORenderable3DPath::_drawMAONoTexture(){
	_drawMAO();
}

void MAORenderable3DPath::_drawMAO() {
  	if (_vectorPathPoint.size() == 0)
		return;

	glDisable( GL_LIGHTING);
	glLoadIdentity();


	float *m = (float*) _globalReference->getPosMatrix().data;
	glMultMatrixf(m);

	refPoint = &_vectorPathPoint.at(0);

	glLineWidth(refPoint->getSize());
	glBegin( GL_LINE_STRIP);

	for (unsigned int i = 0; i < _vectorPathPoint.size(); i++) {
		PathPoint& p = _vectorPathPoint.at(i);

		if (_hasChanged(p)) {
			refPoint = &p;
			glEnd();
			glLineWidth(p.getSize());
			glBegin(GL_LINE_STRIP);
		}

		if (p.getVisible()) {
			glColor3f(p.getR() / 255.0f, p.getG() / 255.0f, p.getB() / 255.0f);
			glVertex3f(p.getX(), p.getY(), p.getZ());
		}

	}
	glEnd();

	glEnable(GL_LIGHTING);
}

bool MAORenderable3DPath::_hasChanged(PathPoint& p) {
	if (refPoint->getR() != p.getR() || refPoint->getG() != p.getG()
			|| refPoint->getB() != p.getB())
		return true;

	if (refPoint->getVisible() != p.getVisible())
		return true;

	if (refPoint->getSize() != p.getSize())
		return true;

	return false;
}

void MAORenderable3DPath::addPoint() {
	float x = getRelativeMatrix().at<float> (3, 0);
	float y = getRelativeMatrix().at<float> (3, 1);
	float z = getRelativeMatrix().at<float> (3, 2);

	_vectorPathPoint.push_back(PathPoint(x, y, z, getSize(), getR(), getG(),
			getB(), getVisiblePoint()));
}
void MAORenderable3DPath::removePoints() {
	_vectorPathPoint.clear();
}
int MAORenderable3DPath::getR() {
	return getProperty("r").getValue<int> ();
}

int MAORenderable3DPath::getG() {
	return getProperty("g").getValue<int> ();
}

int MAORenderable3DPath::getB() {
	return getProperty("b").getValue<int> ();
}

bool MAORenderable3DPath::getVisiblePoint() {
	return getProperty("visiblePoint").getValue<bool> ();
}


MAORenderable3DPath::~MAORenderable3DPath() {

}
