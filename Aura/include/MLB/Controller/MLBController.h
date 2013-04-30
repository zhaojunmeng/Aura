/*
 * MLBController.h
 *
 *  Created on: 22/02/2011
 *      Author: cesar
 */

#ifndef MLBCONTROLLER_H_
#define MLBCONTROLLER_H_

#include <vector>
#include <MLB/MLB.h>
#include <MLB/Sensor/MLBSensor.h>
#include <MLB/Actuator/MLBActuator.h>


class MLBController: public MLB {
public:
	MLBController(const std::string& name, MAO& parent);
	virtual ~MLBController();;
	virtual void evaluate()=0;
	void addMLBSensor(MLBSensor& sensor);
	void addMLBActuator(MLBActuator& actuator);
	void activateActuators();
	//std::vector<MLBSensor*>& getVectorMLBSensor();

	void cleanup();
	bool getState();

protected:
	bool _state;
	std::vector<MLBSensor*> _vectorMLBSensor;
	std::vector<MLBActuator*> _vectorMLBActuator;
};

#endif /* MLBCONTROLLER_H_ */
