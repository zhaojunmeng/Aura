/*
 * MLBActuatorQuitApp.cpp
 *
 *  Created on: 24/02/2011
 *      Author: cesar
 */

#include <MLB/Actuator/MLBActuatorQuitApp.h>

MLBActuatorQuitApp::MLBActuatorQuitApp(const std::string& name, MAO& parent):MLBActuator(name, parent) {
	_mlbType = T_MLBACTUATORQUITAPP;

}

void MLBActuatorQuitApp::specificActuate(){
	EndController::getInstance()->end();
}

MLBActuatorQuitApp::~MLBActuatorQuitApp() {

}
