/*
 * MLBControllerScript.h
 *
 *  Created on: 04/04/2011
 *      Author: cesar
 */

#ifndef MLBCONTROLLERSCRIPT_H_
#define MLBCONTROLLERSCRIPT_H_

#include <iostream>
#include <fstream>
#include <MLB/Controller/MLBController.h>

#include <MLB/MLB.h>
#include <MLB/Sensor/MLBSensor.h>
#include <MLB/Sensor/MLBSensorAlways.h>
#include <MLB/Sensor/MLBSensorKeyboard.h>
#include <MLB/Sensor/MLBSensorProperty.h>
#include <MLB/Sensor/MLBSensorRandom.h>
#include <MLB/Sensor/MLBSensorDelay.h>
#include <MLB/Sensor/MLBSensorActuator.h>
#include <MLB/Sensor/MLBSensorCollision.h>
#include <MLB/Sensor/MLBSensorNear.h>

#include <MLB/Actuator/MLBActuator.h>
#include <MLB/Actuator/MLBActuatorVisibility.h>
#include <MLB/Actuator/MLBActuatorQuitApp.h>
#include <MLB/Actuator/MLBActuatorProperty.h>
#include <MLB/Actuator/MLBActuatorChangePose.h>
#include <MLB/Actuator/MLBActuatorDistance.h>
#include <MLB/Actuator/MLBActuatorAng.h>
#include <MLB/Actuator/MLBActuatorRandom.h>
#include <MLB/Actuator/MLBActuatorSound.h>
#include <MLB/Actuator/MLBActuatorRelativePose.h>
#include <MLB/Actuator/MLBActuatorAddDynamicObject.h>
#include <MLB/Actuator/MLBActuatorAnim.h>


class MLBControllerScript: public MLBController {
public:
	MLBControllerScript(const std::string& name, MAO& parent, const boost::filesystem::path& path);
	virtual ~MLBControllerScript();
	void evaluate();
	boost::python::object* getCompiledObj();
	void setCompiled(bool compiled);

	/* API Python functions! */
	object mPyGetSensor(std::string name);
	object mPyGetActuator(std::string name);

private:
	boost::filesystem::path _path;
	boost::python::object _compiledObj;
	bool _compiled;

	void compileScript();
};

#endif /* MLBCONTROLLERSCRIPT_H_ */
