/*
 * MAOPositionator3D.cpp
 *
 *  Created on: 21/02/2011
 *      Author: cesar
 */

#include <MAO/MAOPositionator3D.h>

using namespace std;

MAOPositionator3D::MAOPositionator3D(const std::string& name) :
		MAO(name) {

	_positioned = false;
	_type = T_MAOPOSITIONATOR3D;
	_node = Ogre::Root::getSingleton().getSceneManager("SceneManager")->createSceneNode(name);
}

MAOPositionator3D::MAOPositionator3D(const MAOPositionator3D& o) :
		MAO(o) {


	_positioned = o._positioned;
	_type = o._type;
}

void MAOPositionator3D::setNodeMatrix(Ogre::Matrix4& posMatrix) {

	_node->setPosition(posMatrix.getTrans());
	_node->setOrientation(posMatrix.extractQuaternion());
}

bool MAOPositionator3D::isPositioned() {
	return _positioned;
}

void MAOPositionator3D::setPositioned(bool positioned) {
	_positioned = positioned;
}

MAOPositionator3D::~MAOPositionator3D() {
}
