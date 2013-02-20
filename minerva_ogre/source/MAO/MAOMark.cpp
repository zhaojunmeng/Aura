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
	_offsetMatrix = cv::Mat(4, 4, CV_32F);
	setIdentityMat(_offsetMatrix);
	_type = T_MAOMARK;

}

cv::Mat& MAOMark::getPosMatrix() {
	return _posMatrix;
}

void MAOMark::setTrackingMatrix(cv::Mat& m) {
	cv::Mat posAux;

	posAux = _offsetMatrix * m;

	_vectorPosMatrix.push_back(posAux);
		setPosMatrix(posAux);



}

void MAOMark::setTrackingMatrix(const double* m) {
	cv::Mat posAux;
	cv::Mat rAux(4, 4, CV_32F);

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			rAux.at<float> (i, j) = (float) m[i * 4 + j];
		}
	}

	//posAux = _offsetMatrix.inv() * rAux;
	posAux = _offsetMatrix * rAux;

	_vectorPosMatrix.push_back(posAux);

	if (_vectorPosMatrix.size() > HIST_LENGTH) {
		_vectorPosMatrix.erase(_vectorPosMatrix.begin());
		cv::Mat average;

		average = 0.5 * _vectorPosMatrix.at(3) + 0.25 * _vectorPosMatrix.at(2)
				+ 0.15 * _vectorPosMatrix.at(1) + 0.1 * _vectorPosMatrix.at(0);

		setPosMatrix(average);

	} else {
		setPosMatrix(posAux);
	}


}

cv::Mat& MAOMark::getOffsetMatrix() {
	return _offsetMatrix;
}

void MAOMark::setOffsetMatrix(const cv::Mat* offsetMatrix) {
	if(offsetMatrix != 0){
	    setOffsetMatrix(*offsetMatrix);
	}
}

void MAOMark::setOffsetMatrix(const cv::Mat& offsetMatrix) {
	if (offsetMatrix.rows != 4 || offsetMatrix.cols != 4)
		throw "Invalid matrix exception!";

	for (unsigned int i = 0; i < 4; i++)
		for (unsigned int j = 0; j < 4; j++)
			_offsetMatrix.at<float> (i, j) = offsetMatrix.at<float> (i, j);
}

void MAOMark::setOffsetMatrix(const double* offsetMatrix) {
	for (unsigned int i = 0; i < 4; i++)
		for (unsigned int j = 0; j < 4; j++)
			_offsetMatrix.at<float> (i, j) = (float) offsetMatrix[i * 4 + j];
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
