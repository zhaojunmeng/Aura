/*
 * MLBControllerOR.cpp
 *
 *  Created on: 22/02/2011
 *      Author: cesar
 */

#include <MLB/Controller/MLBControllerOR.h>

MLBControllerOR::MLBControllerOR(const std::string& name, MAO& parent): MLBController(name,parent) {
	_mlbType = T_MLBCONTROLLEROR;
}

void MLBControllerOR::evaluate(){
	bool e = false;

		for(unsigned int i=0;i<_vectorMLBSensor.size();i++){
			e |= _vectorMLBSensor.at(i)->getState();
		}

		_state = e;
}

MLBControllerOR::~MLBControllerOR() {

}
