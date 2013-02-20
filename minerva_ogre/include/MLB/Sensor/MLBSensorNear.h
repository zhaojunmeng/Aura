/*
 * MLBSensorNear.h
 *
 *  Created on: 22/02/2011
 *      Author: cesar
 */

#ifndef MLBSENSORNEAR_H_
#define MLBSENSORNEAR_H_

#include <Factories/MAOFactory.h>
#include <MLB/Sensor/MLBSensor.h>
#include <MAO/MAOPositionator3D.h>
#include <MAO/MAOProperty.h>

class MLBSensorNear: public MLBSensor {
public:
	MLBSensorNear(const std::string& name, MAOPositionator3D& parent, const std::string& property, float minDistance);
	virtual ~MLBSensorNear();
	void evaluate();

	/* Python functions! */
	float mPyGetMinDistance();
	void mPySetMinDistance(float minDistance);
	std::string mPyGetNearProperty();
	void mPySetNearProperty(std::string property);

private:
	float _minDistance;
	std::string _property;
	float distance(MAOPositionator3D& mao);
};

#endif /* MLBSENSORNEAR_H_ */
