/*
 * MLBSensorRandom.cpp
 *
 *  Created on: 28/02/2011
 *      Author: cesar
 */

#include <MLB/Sensor/MLBSensorRandom.h>

MLBSensorRandom::MLBSensorRandom(const std::string& name, MAO& parent, float prob): MLBSensor(name, parent) {
	if(prob<0 || prob>1)
		throw "Probability not valid for MLB Sensor Random: "+name;

	_prob = prob;
	srand((unsigned int)time(NULL));

	_mlbType = T_MLBSENSORRANDOM;

}

void MLBSensorRandom::evaluate(){
	if(rand()<=_prob)
			_state = true;
}

float MLBSensorRandom::mPyGetProbability(){
	return _prob;
}

void MLBSensorRandom::mPySetProbability(float prob){
	_prob = prob;
}


MLBSensorRandom::~MLBSensorRandom() {
}
