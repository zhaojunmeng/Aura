/*
 * MLBActuatorAng.h
 *
 *  Created on: 28/02/2011
 *      Author: cesar
 */

#ifndef MLBACTUATORANG_H_
#define MLBACTUATORANG_H_

#define ANG_X 0
#define ANG_Y 1
#define ANG_Z 2

#include <MLB/Actuator/MLBActuator.h>
#include <MAO/MAOPositionator3D.h>

class MLBActuatorAng: public MLBActuator {
public:
	MLBActuatorAng(const std::string& name, MAOPositionator3D& parent, MAOProperty& property, int angAxis);
	virtual ~MLBActuatorAng();



private:
	int _angAxis;
	MAOProperty* _property;
	float angle(cv::Mat v1, cv::Mat v2);
	float module(cv::Mat v);
	void specificActuate();
};

#endif /* MLBACTUATORANG_H_ */
