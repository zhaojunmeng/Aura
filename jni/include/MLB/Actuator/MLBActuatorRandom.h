/*
 * MLBActuatorRandom.h
 *
 *  Created on: 28/02/2011
 *      Author: cesar
 */

#ifndef MLBACTUATORRANDOM_H_
#define MLBACTUATORRANDOM_H_

#include <MLB/Actuator/MLBActuator.h>
#include <time.h>

class MLBActuatorRandom: public MLBActuator {
public:
	MLBActuatorRandom(const std::string& name, MAO& parent, MAOProperty& property);
	virtual ~MLBActuatorRandom();


private:
	MAOProperty* _property;

	void specificActuate();
};

#endif /* MLBACTUATORRANDOM_H_ */
