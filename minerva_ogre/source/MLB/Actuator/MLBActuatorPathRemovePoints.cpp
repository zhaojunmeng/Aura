/*
 * MLBActuatorPathRemovePoints.cpp
 *
 *  Created on: 01/03/2011
 *      Author: cesar
 */

#include <MLB/Actuator/MLBActuatorPathRemovePoints.h>

MLBActuatorPathRemovePoints::MLBActuatorPathRemovePoints(const std::string& name, MAORenderable3DPath& parent): MLBActuator(name, parent) {
	_mlbType = T_MLBACTUATORPATHREMOVEPOINTS;
}

void MLBActuatorPathRemovePoints::specificActuate(){
	((MAORenderable3DPath*)_parent)->removePoints();
}

MLBActuatorPathRemovePoints::~MLBActuatorPathRemovePoints() {
}
