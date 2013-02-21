/*
 * MAOPositionator3D.cpp
 *
 *  Created on: 21/02/2011
 *      Author: cesar
 */

#include <MAO/MAOPositionator3D.h>

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

void MAOPositionator3D::setNodeMatrix(const double* posMatrix) {
	Ogre::Matrix4 mat(posMatrix[0], posMatrix[1], posMatrix[2], posMatrix[3],
			posMatrix[4], posMatrix[5], posMatrix[6], posMatrix[7],
			posMatrix[8], posMatrix[9], posMatrix[10], posMatrix[11],
			posMatrix[12], posMatrix[13], posMatrix[14], posMatrix[15]);

	_node->setPosition(mat.getTrans());
	_node->setOrientation(mat.extractQuaternion());
}

bool MAOPositionator3D::isPositioned() {
	return _positioned;
}

void MAOPositionator3D::setPositioned(bool positioned) {
	_positioned = positioned;
}

MAOPositionator3D::~MAOPositionator3D() {
}
