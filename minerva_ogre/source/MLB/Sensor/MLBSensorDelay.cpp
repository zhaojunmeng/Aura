/*
 * MLBSensorDelay.cpp
 *
 *  Created on: 28/02/2011
 *      Author: cesar
 */

#include <MLB/Sensor/MLBSensorDelay.h>

MLBSensorDelay::MLBSensorDelay(const std::string& name, MAO& parent,
		int delayFrames) :
	MLBSensor(name, parent) {
	_delayFrames = delayFrames;
	_frames = _delayFrames;
	_mlbType = T_MLBSENSORDELAY;
}

void MLBSensorDelay::evaluate() {
	_frames--;
	if (_frames == 0) {
		_frames = _delayFrames;
		_state = true;
	}
}

int MLBSensorDelay::mPyGetDelayFrames() {
	return _delayFrames;
}

void MLBSensorDelay::mPySetDelayFrames(int delayFrames) {
	_delayFrames = delayFrames;
}

MLBSensorDelay::~MLBSensorDelay() {
}
