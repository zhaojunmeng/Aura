/*
 * MAOMark.h
 *
 *  Created on: 21/02/2011
 *      Author: cesar
 */

#ifndef MAOMARK_H_
#define MAOMARK_H_

#define HIST_LENGTH 4

#include <string>

#include<MAO/MAOPositionator3D.h>

class MAOMark: public MAOPositionator3D {
public:
	MAOMark(const std::string& name, const boost::filesystem::path& path,
			const float& size);
	virtual ~MAOMark();
	const boost::filesystem::path& getPath();
	float getSize();
	double* getCenter();

	cv::Mat& getPosMatrix();

	void setTrackingMatrix(cv::Mat& m);
	void setTrackingMatrix(const double* m);

	cv::Mat& getOffsetMatrix();
	void setOffsetMatrix(const cv::Mat* offsetMatrix);
	void setOffsetMatrix(const cv::Mat& offsetMatrix);
	void setOffsetMatrix(const double* offsetMatrix);

	void setId(int id);
	int getId();

private:
	cv::Mat _offsetMatrix;
	boost::filesystem::path _bPath;
	std::vector<cv::Mat> _vectorPosMatrix;
	float _size;
	int _id;
	double* _center;

};

#endif /* MAOMARK_H_ */
