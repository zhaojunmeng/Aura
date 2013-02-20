/*
 * MAOPositionable.h
 *
 *  Created on: 21/02/2011
 *      Author: cesar
 */

#ifndef MAOPOSITIONATOR3D_H_
#define MAOPOSITIONATOR3D_H_

#include <cv.h>
#include <string>
#include <iostream>

#include <MAO/MAO.h>

class MAOPositionator3D: public MAO {
public:
	MAOPositionator3D(const std::string& name);
	MAOPositionator3D(const MAOPositionator3D& o);
	virtual ~MAOPositionator3D();
	virtual cv::Mat& getPosMatrix()=0;

	/* Getters and Setters */
	bool isPositioned();
	void setPositioned(bool positioned);

protected:
	cv::Mat _posMatrix;
	bool _positioned;

	void setPosMatrix(cv::Mat& relativeMatrix);
	void setPosMatrix(const double* relativeMatrix);

	void setIdentityMat(cv::Mat& mat);
};

#endif /* MAOPositionator3D_H_ */
