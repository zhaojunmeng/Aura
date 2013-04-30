/*
 * MLBSensorAlways.cpp
 *
 *  Created on: 22/02/2011
 *      Author: cesar
 */

#include <MLB/Sensor/MLBSensorAlways.h>

MLBSensorAlways::MLBSensorAlways(const std::string& name, MAO& parent): MLBSensor(name, parent) {
	_mlbType = T_MLBSENSORALWAYS;
}

void MLBSensorAlways::evaluate(){
	_state = true;
}

MLBSensorAlways::~MLBSensorAlways() {
}
