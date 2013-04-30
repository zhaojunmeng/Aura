/*
 * GameLogicController.h
 *
 *  Created on: 20/02/2011
 *      Author: cesar
 */

#ifndef GAMELOGICCONTROLLER_H_
#define GAMELOGICCONTROLLER_H_

#include <vector>
#include <algorithm>
#include <Kernel/Singleton.h>
#include <Factories/MLBFactory.h>
#include <Factories/MAOFactory.h>
#include <Controllers/PhysicsController.h>
#include <MLB/Sensor/MLBSensor.h>
#include <MLB/Controller/MLBController.h>
#include <MLB/Actuator/MLBActuator.h>

class GameLogicController: public Singleton<GameLogicController>{
public:
	GameLogicController();
	virtual ~GameLogicController();
	void pollLogic();

private:
	void pollSensors();
	std::vector<MLBController*>& pollControllers();
	void activateActuators(std::vector<MLBController*>& activeControllers);
	void cleanupSensors();
	void cleanupControllers();
	void checkInstMAO();
};

#endif /* GAMELOGICCONTROLLER_H_ */
