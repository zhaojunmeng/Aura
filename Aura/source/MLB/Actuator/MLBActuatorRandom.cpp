/*
 * MLBActuatorRandom.cpp
 *
 *  Created on: 28/02/2011
 *      Author: cesar
 */

#include <MLB/Actuator/MLBActuatorRandom.h>

MLBActuatorRandom::MLBActuatorRandom(const std::string& name, MAO& parent, MAOProperty& property): MLBActuator(name, parent) {
	if(property.getType()!=MAOPROPERTY_FLOAT)
		throw "Just Mao Property Float is allowed for MLB Actuator Random: "+name;

	_property = &property;
	srand((unsigned int)time(NULL));
	_mlbType = T_MLBACTUATORRANDOM;
}

void MLBActuatorRandom::specificActuate(){
	float prob = (float) rand();

	_property->setValue<float>(prob);
}


MLBActuatorRandom::~MLBActuatorRandom() {
}
