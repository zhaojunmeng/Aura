/*
 * MLBControllerAND.cpp
 *
 *  Created on: 22/02/2011
 *      Author: cesar
 */

#include <MLB/Controller/MLBControllerAND.h>

MLBControllerAND::MLBControllerAND(const std::string& name, MAO& parent): MLBController(name, parent) {
	_mlbType = T_MLBCONTROLLERAND;
}

void MLBControllerAND::evaluate(){
	bool e = true;

	for(unsigned int i=0;i<_vectorMLBSensor.size();i++){
		e &= _vectorMLBSensor.at(i)->getState();
	}

	_state = e;
}

MLBControllerAND::~MLBControllerAND() {

}
