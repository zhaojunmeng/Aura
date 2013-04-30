/*
 * MLBActuatorQuitApp.h
 *
 *  Created on: 24/02/2011
 *      Author: cesar
 */

#ifndef MLBACTUATORQUITAPP_H_
#define MLBACTUATORQUITAPP_H_

#include <Kernel/EndController.h>
#include <MLB/Actuator/MLBActuator.h>
#include <MAO/MAOPositionator3D.h>

class MLBActuatorQuitApp:public MLBActuator {
public:
	MLBActuatorQuitApp(const std::string& name, MAO& parent);
	virtual ~MLBActuatorQuitApp();

private:
	void specificActuate();
};

#endif /* MLBACTUATORQUITAPP_H_ */
