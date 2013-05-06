/*
 * MLBSensor.cpp
 *
 *  Created on: 22/02/2011
 *      Author: cesar
 */

#include <MLB/Sensor/MLBSensor.h>

MLBSensor::MLBSensor(const std::string& name, MAO& parent): MLB(name, parent) {
	_state = false;
	_active = true;
	_mlbType = T_MLBSENSOR;

}

bool MLBSensor::getState(){
	return _state;
}


bool MLBSensor::isActive(){
	return _active;
}

void MLBSensor::trigger(){
	_state = true;
}

void MLBSensor::cleanup(){
	_state = false;
}

void MLBSensor::setActive(bool active){
	_active = active;
}

MLBSensor::~MLBSensor() {
}
