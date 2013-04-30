/*
 * MLBSensor.h
 *
 *  Created on: 22/02/2011
 *      Author: cesar
 */

#ifndef MLBSENSOR_H_
#define MLBSENSOR_H_

#include <MLB/MLB.h>

class MLBSensor: public MLB {
public:
	MLBSensor(const std::string& name, MAO& parent);
	virtual ~MLBSensor();
	virtual void evaluate()=0;

	void cleanup();
	bool getState();
	void trigger();
	bool isActive();
	void setActive(bool active);
protected:
	bool _state;
	bool _active;
};

#endif /* MLBSENSOR_H_ */
