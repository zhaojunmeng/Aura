/*
 * MLBActuatorPathAddPoint.cpp
 *
 *  Created on: 02/03/2011
 *      Author: cesar
 */

#include <MLB/Actuator/MLBActuatorPathAddPoint.h>

MLBActuatorPathAddPoint::MLBActuatorPathAddPoint(const std::string& name, MAORenderable3DPath& parent): MLBActuator(name, parent) {
	_mlbType = T_MLBACTUATORPATHADDPOINT;
}

void MLBActuatorPathAddPoint::specificActuate(){
	((MAORenderable3DPath*)_parent)->addPoint();
}

MLBActuatorPathAddPoint::~MLBActuatorPathAddPoint() {

}
