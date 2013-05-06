/*
 * MLBSensorActuator.h
 *
 *  Created on: 02/03/2011
 *      Author: cesar
 */

#ifndef MLBSENSORACTUATOR_H_
#define MLBSENSORACTUATOR_H_

#include <MLB/Sensor/MLBSensor.h>

class MLBSensorActuator: public MLBSensor {
public:
	MLBSensorActuator(const std::string& name, MAO& parent);
	virtual ~MLBSensorActuator();

	void evaluate();
private:
};

#endif /* MLBSENSORACTUATOR_H_ */
