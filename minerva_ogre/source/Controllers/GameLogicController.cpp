/*
 * GameLogicController.cpp
 *
 *  Created on: 20/02/2011
 *      Author: cesar
 */

#include <Controllers/GameLogicController.h>

GameLogicController::GameLogicController() {

}

void GameLogicController::pollLogic() {
	//Check the instantiated MAO's
	checkInstMAO();

	//Evaluate the sensors
	pollSensors();

	//Evaluate the controllers
	std::vector<MLBController*>& activeControllers = pollControllers();

	cleanupSensors(); //Clean up sensors first! To make MLBSensorActuators work! ;)
	cleanupControllers();

	//Activate actuators
	activateActuators(activeControllers);

	//Cleaning up!
	delete &activeControllers;

}

void GameLogicController::checkInstMAO() {
	std::vector<MAORenderable3D*>& v =
			MAOFactory::getInstance()->getVectorInstMAORenderable3D();

	std::vector<MAORenderable3D*>::iterator it;
	std::vector<MAORenderable3D*> toDelete;

	for(it = v.begin(); it != v.end(); it++){
		(*it)->decrementTimeToExpire();
		if((*it)->getTimeToExpire() == 1){ //If time is zero it means that lives forever! ;)
			if((*it)->isPhysic()){
				PhysicsController::getInstance()->removeDynamicRigidBody(*(it));
			}

			v.erase(it);
			it--;

		}
	}



}

void GameLogicController::pollSensors() {
	std::vector<MLBSensor*>& sensors =
			MLBFactory::getInstance()->getVectorMLBSensor();

	for (unsigned int i = 0; i < sensors.size(); i++) {
		sensors.at(i)->evaluate();
	}
}

/*Returns the triggered controllers */
std::vector<MLBController*>& GameLogicController::pollControllers() {
	std::vector<MLBController*>& controllers =
			MLBFactory::getInstance()->getVectorMLBController();
	std::vector<MLBController*>* activeControllers = new std::vector<
			MLBController*>();

	for (unsigned int i = 0; i < controllers.size(); i++) {
		controllers.at(i)->evaluate();
		if (controllers.at(i)->getState()) {
			activeControllers->push_back(controllers.at(i));
		}
	}

	return *activeControllers;
}

void GameLogicController::activateActuators(
		std::vector<MLBController*>& activeControllers) {
	for (unsigned int i = 0; i < activeControllers.size(); i++) {
		activeControllers.at(i)->activateActuators();
	}
}

void GameLogicController::cleanupSensors() {
	std::vector<MLBSensor*>& sensors =
			MLBFactory::getInstance()->getVectorMLBSensor();

	for (unsigned int i = 0; i < sensors.size(); i++) {
		sensors.at(i)->cleanup();
	}
}

void GameLogicController::cleanupControllers() {
	std::vector<MLBController*>& controllers =
			MLBFactory::getInstance()->getVectorMLBController();

	for (unsigned int i = 0; i < controllers.size(); i++) {
		controllers.at(i)->cleanup();
	}
}

GameLogicController::~GameLogicController() {
}
