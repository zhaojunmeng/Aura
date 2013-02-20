/*
 * MLBSensorKeyboard.cpp
 *
 *  Created on: 22/02/2011
 *      Author: cesar
 */

#include <MLB/Sensor/MLBSensorKeyboard.h>

MLBSensorKeyboard::MLBSensorKeyboard(const std::string& name, MAO& parent,
		SDL_EventType& type, SDLKey& key) :
	MLBSensor(name, parent) {
	_type = type;
	_key = key;
	_keyDown = false;
	_mlbType = T_MLBSENSORKEYBOARD;
}

void MLBSensorKeyboard::evaluate() {
	switch (_type) {
	case SDL_KEYDOWN:
		if (_keyDown)
			_state = true;
		else
			_state = false;
		break;
	case SDL_KEYUP:
		//Just for one time! Intentionally empty!
		break;
	default:
		break;
	}
}

void MLBSensorKeyboard::setKeyDown(bool keyDown) {
	_keyDown = keyDown;
}

SDL_EventType& MLBSensorKeyboard::getType() {
	return _type;
}

SDLKey& MLBSensorKeyboard::getKey() {
	return _key;
}

MLBSensorKeyboard::~MLBSensorKeyboard() {
}
