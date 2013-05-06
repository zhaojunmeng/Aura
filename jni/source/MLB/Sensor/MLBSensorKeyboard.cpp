/*
 * MLBSensorKeyboard.cpp
 *
 *  Created on: 22/02/2011
 *      Author: cesar
 */

#include <MLB/Sensor/MLBSensorKeyboard.h>

MLBSensorKeyboard::MLBSensorKeyboard(const std::string& name, MAO& parent,
		std::string& type, std::string& key) :
		MLBSensor(name, parent) {
	_type = type;
	_key = key;
	_keyDown = false;
	_mlbType = T_MLBSENSORKEYBOARD;
}

void MLBSensorKeyboard::evaluate() {
	if (_type == "KEYDOWN") {
		if (_keyDown){
			_state = true;
		}else
			_state = false;
	} else if (_type == "KEYUP") {
		//Just for one time! Intentionally empty!
	}
}

void MLBSensorKeyboard::setKeyDown(bool keyDown) {
	_keyDown = keyDown;
}

std::string& MLBSensorKeyboard::getType() {
	return _type;
}

std::string& MLBSensorKeyboard::getKey() {
	return _key;
}

MLBSensorKeyboard::~MLBSensorKeyboard() {
}
