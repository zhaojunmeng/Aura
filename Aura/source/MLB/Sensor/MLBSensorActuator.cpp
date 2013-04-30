/*
 * MLBSensorActuator.cpp
 *
 *  Created on: 02/03/2011
 *      Author: cesar
 */

#include <MLB/Sensor/MLBSensorActuator.h>

MLBSensorActuator::MLBSensorActuator(const std::string& name, MAO& parent): MLBSensor(name, parent) {
	_mlbType = T_MLBSENSORACTUATOR;
}

void MLBSensorActuator::evaluate(){
	/* Intentionally empty ;) */
}

MLBSensorActuator::~MLBSensorActuator() {
}
