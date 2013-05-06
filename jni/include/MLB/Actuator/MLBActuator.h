/*
 * MLBActuator.h
 *
 *  Created on: 22/02/2011
 *      Author: cesar
 */

#ifndef MLBACTUATOR_H_
#define MLBACTUATOR_H_

#include <vector>
#include <MLB/Sensor/MLBSensorActuator.h>

class MLBActuator: public MLB {
public:
	MLBActuator(const std::string& name, MAO& parent);
	virtual ~MLBActuator();
	void actuate(); //Public interface of actuators
	void addMLBSensorActuator(MLBSensorActuator& sensor);

protected:
	std::vector<MLBSensorActuator*> _vectorMLBSensorActuator;

	virtual void specificActuate()=0; //Specific implementation of the actuator
};

#endif /* MLBACTUATOR_H_ */
