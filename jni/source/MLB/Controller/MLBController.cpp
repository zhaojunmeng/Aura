/*
 * MLBController.cpp
 *
 *  Created on: 22/02/2011
 *      Author: cesar
 */

#include <MLB/Controller/MLBController.h>

MLBController::MLBController(const std::string& name, MAO& parent): MLB(name, parent) {
	_state = false;
	_mlbType = T_MLBCONTROLLER;

}

void MLBController::addMLBSensor(MLBSensor& sensor){
	_vectorMLBSensor.push_back(&sensor);
}

void MLBController::addMLBActuator(MLBActuator& actuator){
	_vectorMLBActuator.push_back(&actuator);
}

void MLBController::activateActuators(){
	for(unsigned int i=0;i<_vectorMLBActuator.size();i++){
		_vectorMLBActuator.at(i)->actuate();
	}
}


bool MLBController::getState(){
	return _state;
}

void MLBController::cleanup(){
	_state=false;
}

MLBController::~MLBController() {
}
