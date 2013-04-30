/*
 * MAOMark.cpp
 *
 *  Created on: 21/02/2011
 *      Author: cesar
 */

#include <MAO/MAOMark.h>

MAOMark::MAOMark(const std::string& name, const boost::filesystem::path& path,
		const float& size) :
		MAOPositionator3D(name) {
	_bPath = path;
	_size = size;
	_center = new double[2];
	_center[0] = .0;
	_center[1] = .0;

	_type = T_MAOMARK;
	_offsetMatrix = Ogre::Matrix4::IDENTITY;

	Ogre::Root::getSingleton().getSceneManager("SceneManager")->getRootSceneNode()->addChild(
			_node);
}

void MAOMark::setTrackingMatrix(Ogre::Matrix4& m) {
	Ogre::Matrix4 posAux = _offsetMatrix * m;

	_listPosMatrix.push_back(posAux);
	if (_listPosMatrix.size() > _historicSize) {
		_listPosMatrix.pop_front();
	}

	setNodeMatrix(posAux);
}

void MAOMark::setOffsetMatrix(const Ogre::Matrix4* offsetMatrix) {
	if (offsetMatrix != 0) {
		_offsetMatrix = *offsetMatrix;
	}
}

const boost::filesystem::path& MAOMark::getPath() {
	return _bPath;
}

float MAOMark::getSize() {
	return _size;
}

void MAOMark::setId(int id) {
	_id = id;
}
int MAOMark::getId() {
	return _id;
}

double* MAOMark::getCenter() {
	return _center;
}

MAOMark::~MAOMark() {
	delete _center;
}
