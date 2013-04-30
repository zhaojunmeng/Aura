/*
 * MLBActuator.cpp
 *
 *  Created on: 22/02/2011
 *      Author: cesar
 */

#include <MLB/Actuator/MLBActuator.h>

MLBActuator::MLBActuator(const std::string& name,  MAO& parent): MLB(name,parent) {
	_mlbType = T_MLBACTUATOR;
}

void MLBActuator::actuate(){
	//Check if should trigger MLBSensorActuator
	for(unsigned int i=0;i<_vectorMLBSensorActuator.size();i++){
		_vectorMLBSensorActuator.at(i)->trigger();
	}

	specificActuate();
}

void MLBActuator::addMLBSensorActuator(MLBSensorActuator& sensor){
	_vectorMLBSensorActuator.push_back(&sensor);
}

MLBActuator::~MLBActuator() {
}
