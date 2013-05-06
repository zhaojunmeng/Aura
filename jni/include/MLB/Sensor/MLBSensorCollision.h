/*
 * MLBSensorCollision.h
 *
 *  Created on: 07/03/2011
 *      Author: cesar
 */

#ifndef MLBSENSORCOLLISION_H_
#define MLBSENSORCOLLISION_H_

#include <MLB/Sensor/MLBSensor.h>
#include <Controllers/PhysicsController.h>
#include <Factories/MAOFactory.h>

class MLBSensorCollision: public MLBSensor {
public:
	MLBSensorCollision(const std::string& name, MAORenderable3D& parent, const std::string& property);
	virtual ~MLBSensorCollision();

	void evaluate();

	/* Python functions */
	std::string mPyGetCollisionProperty();
	void mPySetCollisionProperty(std::string property);

private:
	std::string _property;
};

#endif /* MLBSENSORCOLLISION_H_ */
