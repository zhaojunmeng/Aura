/*
 * MAOPositionator3D.cpp
 *
 *  Created on: 21/02/2011
 *      Author: cesar
 */

#include <MAO/MAOPositionator3D.h>

MAOPositionator3D::MAOPositionator3D(const std::string& name):MAO(name) {
	_posMatrix = cv::Mat(4,4,CV_32F);

	setIdentityMat(_posMatrix);
	_positioned = false;
	_type = T_MAOPOSITIONATOR3D;
}

MAOPositionator3D::MAOPositionator3D(const MAOPositionator3D& o): MAO(o){
	_posMatrix = cv::Mat(4,4,CV_32F);
	setIdentityMat(_posMatrix);

	_positioned = o._positioned;
	_type = o._type;
}

void MAOPositionator3D::setPosMatrix(cv::Mat& posMatrix) {
	if (posMatrix.rows != 4 || posMatrix.cols != 4)
		throw "Invalid matrix exception!";

	for (unsigned int i = 0; i < 4; i++)
		for (unsigned int j = 0; j < 4; j++)
			_posMatrix.at<float> (i, j) = posMatrix.at<float> (i, j);


}

void MAOPositionator3D::setPosMatrix(const double* posMatrix) {
	for (unsigned int i = 0; i < 4; i++)
		for (unsigned int j = 0; j < 4; j++)
			_posMatrix.at<float> (i, j) = (float) posMatrix[i * 4 + j];
}

bool MAOPositionator3D::isPositioned(){
	return _positioned;
}

void MAOPositionator3D::setPositioned(bool positioned){
	_positioned = positioned;
}

void MAOPositionator3D::setIdentityMat(cv::Mat& mat){
	mat.at<float>(0,0) = 1.0; mat.at<float>(0,1) = 0.0; mat.at<float>(0,2) = 0.0; mat.at<float>(0,3) = 0.0;
	mat.at<float>(1,0) = 0.0; mat.at<float>(1,1) = 1.0; mat.at<float>(1,2) = 0.0; mat.at<float>(1,3) = 0.0;
	mat.at<float>(2,0) = 0.0; mat.at<float>(2,1) = 0.0; mat.at<float>(2,2) = 1.0; mat.at<float>(2,3) = 0.0;
	mat.at<float>(3,0) = 0.0; mat.at<float>(3,1) = 0.0; mat.at<float>(3,2) = 0.0; mat.at<float>(3,3) = 1.0;
}

MAOPositionator3D::~MAOPositionator3D() {
}
