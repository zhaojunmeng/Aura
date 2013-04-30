/*
 * MLBControllerNAND.cpp
 *
 *  Created on: 22/02/2011
 *      Author: cesar
 */

#include <MLB/Controller/MLBControllerNAND.h>

MLBControllerNAND::MLBControllerNAND(const std::string& name, MAO& parent): MLBController(name, parent) {
	_mlbType = T_MLBCONTROLLERNAND;
}

void MLBControllerNAND::evaluate(){
	bool e = true;

	for(unsigned int i=0;i<_vectorMLBSensor.size();i++){
		e &= _vectorMLBSensor.at(i)->getState();
	}

	_state = !e;
}

MLBControllerNAND::~MLBControllerNAND() {

}
