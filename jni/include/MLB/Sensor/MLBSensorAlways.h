/*
 * MLBSensorAlways.h
 *
 *  Created on: 22/02/2011
 *      Author: cesar
 */

#ifndef MLBSENSORALWAYS_H_
#define MLBSENSORALWAYS_H_

#include <MLB/Sensor/MLBSensor.h>
#include <MAO/MAO.h>

class MLBSensorAlways: public MLBSensor {
public:
	MLBSensorAlways(const std::string& name, MAO& parend);
	virtual ~MLBSensorAlways();
	void evaluate();
};

#endif /* MLBSENSORALWAYS_H_ */
