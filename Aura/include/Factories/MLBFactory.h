/*
 * MLBFactory.h
 *
 *  Created on: 20/02/2011
 *      Author: cesar
 */

#ifndef MLBFACTORY_H_
#define MLBFACTORY_H_

#include <vector>
#include <typeinfo>
#include <SDL.h>

#include <Kernel/Singleton.h>
#include <Controllers/InputEventController.h>

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

#include <MLB/Controller/MLBController.h>
#include <MLB/Controller/MLBControllerAND.h>
#include <MLB/Controller/MLBControllerNAND.h>
#include <MLB/Controller/MLBControllerOR.h>
#include <MLB/Controller/MLBControllerNOR.h>

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

#include <MAO/MAO.h>
#include <MAO/MAORenderable3D.h>
#include <MAO/MAOPositionator3D.h>

class MLBFactory: public Singleton<MLBFactory> {
public:
	MLBFactory();
	virtual ~MLBFactory();

	/* Adds */
	/* -Sensors */
	MLBSensorAlways& addMLBSensorAlways(std::string name,
			std::string nparent);
	MLBSensorNear& addMLBSensorNear(std::string name,
			std::string nparent, std::string property,
			float minDistance);
	MLBSensorKeyboard& addMLBSensorKeyboard(std::string name,
			std::string nparent, std::string type, std::string key);
	MLBSensorProperty& addMLBSensorProperty(std::string name,
			std::string nparent, std::string type, MAOProperty& property,
			MAOValue* value1, MAOValue* value2 = 0);
	MLBSensorProperty& addMLBSensorProperty(std::string name,
			std::string nparent, std::string type, MAOProperty& property,
			MAOProperty& valueProp);
	MLBSensorRandom& addMLBSensorRandom(std::string name,
			std::string nparent, float prob);
	MLBSensorDelay& addMLBSensorDelay(std::string name,
			std::string nparent, int delayFrames);
	MLBSensorActuator& addMLBSensorActuator(std::string name,
			std::string nparent, std::string actuator);
	MLBSensorCollision& addMLBSensorCollision(std::string name,
			std::string nparent, std::string nproperty);

	/* -Controllers */
	MLBControllerAND& addMLBControllerAND(std::string name,
			std::string nparent);
	MLBControllerNAND& addMLBControllerNAND(std::string name,
			std::string nparent);
	MLBControllerOR& addMLBControllerOR(std::string name,
			std::string nparent);
	MLBControllerNOR& addMLBControllerNOR(std::string name,
			std::string nparent);

	/* -Actuators */
	MLBActuatorVisibility& addMLBActuatorVisibility(std::string name,
			std::string nparent, bool value);
	MLBActuatorQuitApp& addMLBActuatorQuitApp(std::string name,
			std::string nparent);
	MLBActuatorProperty& addMLBActuatorProperty(std::string name,
			std::string nparent, MAOProperty& property, MAOValue value,
			std::string type);
	MLBActuatorProperty& addMLBActuatorProperty(std::string name,
			std::string nparent, MAOProperty& property,
			MAOProperty& valueProp, std::string type);
	MLBActuatorChangePose& addMLBActuatorChangePose(std::string name,
			std::string nparent, std::string locType, Ogre::Vector3* loc,
			std::string rotType, Ogre::Vector3* rot);
	MLBActuatorDistance& addMLBActuatorDistance(std::string name,
			std::string nparent, std::string nmao, MAOProperty& property);
	MLBActuatorAng& addMLBActuatorAng(std::string name,
			std::string nparent, MAOProperty& property, std::string angAxis);
	MLBActuatorRandom& addMLBActuatorRandom(std::string name,
			std::string nparent, MAOProperty& property);
	MLBActuatorSound& addMLBActuatorSound(std::string name,
			std::string nparent, std::string path);
	MLBActuatorRelativePose& addMLBActuatorRelativePose(
			std::string name, std::string nparent, std::string nref,
			MAOProperty& property, bool inverse = false);
	MLBActuatorAddDynamicObject& addMLBActuatorAddDynamicObject(
			std::string name, std::string nparent, std::string nmao,
			int timeToExpire = 0, Ogre::Matrix4* offset = 0, Ogre::Vector3* impulse = 0);
	MLBActuatorAnim& addMLBActuatorAnim(std::string name,
			std::string nparent, std::string nanimChoice,
			std::string* nanimType);

	/* Links! */
	void addMLBLink(std::string parent, std::string a, std::string b);

	/* Getters */
	MLB& getMLB(std::string parent, std::string name);
	MLBSensor& getMLBSensor(std::string parent, std::string name);
	MLBController& getMLBController(std::string parent,
			std::string name);
	MLBActuator& getMLBActuator(std::string parent,
			std::string name);

	std::vector<MLBSensor*>& getVectorMLBSensor();
	std::vector<MLBController*>& getVectorMLBController();
	std::vector<MLBActuator*>& getVectorMLBActuator();

protected:
	bool checkMLBName(std::string parent, std::string name);

	std::vector<MLB*> _vectorMLB;
	std::vector<MLBSensor*> _vectorMLBSensor;
	std::vector<MLBController*> _vectorMLBController;
	std::vector<MLBActuator*> _vectorMLBActuator;
};

#endif /* MLBFACTORY_H_ */
