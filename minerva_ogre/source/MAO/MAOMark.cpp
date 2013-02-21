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

	Ogre::Root::getSingleton().getSceneManager("SceneManager")->getRootSceneNode()->addChild(_node);

}

void MAOMark::setTrackingMatrix(Ogre::Matrix4& m) {
	Ogre::Matrix4 posAux;

	posAux = _offsetMatrix * m;

	_vectorPosMatrix.push_back(posAux);
		setNodeMatrix(posAux);

}

void MAOMark::setTrackingMatrix(const double* m) {
	Ogre::Matrix4 posAux;
	Ogre::Matrix4 rAux(m[0], m[1],m[2],m[3],
			m[4], m[5],m[6],m[7],
			m[8], m[9],m[10],m[11],
			m[12], m[13],m[14],m[15]);



	posAux = _offsetMatrix * rAux;

	_vectorPosMatrix.push_back(posAux);

	//if (_vectorPosMatrix.size() > HIST_LENGTH) {
		//_vectorPosMatrix.erase(_vectorPosMatrix.begin());
		//Ogre::Matrix4 average;

		//average = 0.5 * _vectorPosMatrix.at(3) + 0.25 * _vectorPosMatrix.at(2)
			//	+ 0.15 * _vectorPosMatrix.at(1) + 0.1 * _vectorPosMatrix.at(0);

		//setNodeMatrix(average);
//TODO
	//} else {
		setNodeMatrix(posAux);
	//}


}

Ogre::Matrix4& MAOMark::getOffsetMatrix() {
	return _offsetMatrix;
}

void MAOMark::setOffsetMatrix(const Ogre::Matrix4* offsetMatrix) {
	if(offsetMatrix != 0){
	    _offsetMatrix = *offsetMatrix;
	}
}

void MAOMark::setOffsetMatrix(const double* offsetMatrix) {
	_offsetMatrix = Ogre::Matrix4(offsetMatrix[0],offsetMatrix[1],offsetMatrix[2],offsetMatrix[3],
			offsetMatrix[4],offsetMatrix[5],offsetMatrix[6],offsetMatrix[7],
			offsetMatrix[8],offsetMatrix[9],offsetMatrix[10],offsetMatrix[11],
			offsetMatrix[12],offsetMatrix[13],offsetMatrix[14],offsetMatrix[15]);
}

const boost::filesystem::path& MAOMark::getPath() {
  return _bPath;
}

Ogre::Matrix4& MAOMark::getPosMatrix(){
	// TODO
	Ogre::Matrix4 m;
	return m;
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
