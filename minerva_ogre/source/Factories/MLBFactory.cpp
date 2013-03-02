/*
 * MLBFactory.cpp
 *
 *  Created on: 20/02/2011
 *      Author: cesar
 */

#include <Factories/MLBFactory.h>

MLBFactory::MLBFactory() {

}

/* Adds */
/*-Sensors */
MLBSensorAlways& MLBFactory::addMLBSensorAlways(std::string name,
		std::string nparent) {
	if (!checkMLBName(nparent, name))
		throw "MLB name already exists " + name;

	MAO& parent = MAOFactory::getInstance()->getMAO(nparent);

	MLBSensorAlways* s = new MLBSensorAlways(name, parent);
	_vectorMLB.push_back(s);
	_vectorMLBSensor.push_back(s);

	return *s;
}

MLBSensorNear& MLBFactory::addMLBSensorNear(std::string name,
		const std::string nparent, const std::string nproperty,
		float minDistance) {
	if (!checkMLBName(nparent, name))
		throw "MLB name already exists " + name;

	MAOPositionator3D& parent =
			MAOFactory::getInstance()->getMAOPositionator3D(nparent);

	MLBSensorNear* s = new MLBSensorNear(name, parent, nproperty, minDistance);
	_vectorMLB.push_back(s);
	_vectorMLBSensor.push_back(s);

	return *s;
}

MLBSensorKeyboard& MLBFactory::addMLBSensorKeyboard(std::string name,
		std::string nparent, std::string type, std::string key) {
	if (!checkMLBName(nparent, name))
		throw "MLB name already exists " + name;

	MAO& parent = MAOFactory::getInstance()->getMAO(nparent);

	MLBSensorKeyboard* s = new MLBSensorKeyboard(name, parent, type, key);
	_vectorMLB.push_back(s);
	_vectorMLBSensor.push_back(s);

	InputEventController::getInstance()->addMLBSensorKeyboard(*s);

	return *s;
}

MLBSensorProperty& MLBFactory::addMLBSensorProperty(std::string name,
		std::string nparent, std::string type, MAOProperty& property,
		MAOValue* value1, MAOValue* value2) {
	if (!checkMLBName(nparent, name))
		throw "MLB name already exists: " + name;

	MAO& parent = MAOFactory::getInstance()->getMAO(nparent);

	int itype;
	if (type == "EQUAL") {
		itype = MAOPROPERTY_EQUAL;
	} else if (type == "NOTEQUAL") {
		itype = MAOPROPERTY_NOTEQUAL;
	} else if (type == "INTERVAL") {
		itype = MAOPROPERTY_INTERVAL;
	} else {
		throw "Invalid MLB Sensor Property type!: " + name;
	}

	if (value1 == 0) {
		throw "Value 1 is NULL in MLB Sensor Property!: " + name;
	}

	MLBSensorProperty* s = NULL;

	if (value2 == 0) {
		s = new MLBSensorProperty(name, parent, itype, property, *value1,
				MAOValue());

	} else {
		s = new MLBSensorProperty(name, parent, itype, property, *value1,
				*value2);

	}

	_vectorMLB.push_back(s);
	_vectorMLBSensor.push_back(s);

	return *s;
}

MLBSensorProperty& MLBFactory::addMLBSensorProperty(std::string name,
		std::string nparent, std::string type, MAOProperty& property,
		MAOProperty& valueProp) {
	if (!checkMLBName(nparent, name))
		throw "MLB name already exists: " + name;

	MAO& parent = MAOFactory::getInstance()->getMAO(nparent);

	int itype;
	if (type == "EQUAL") {
		itype = MAOPROPERTY_EQUAL;
	} else if (type == "NOTEQUAL") {
		itype = MAOPROPERTY_NOTEQUAL;
	} else if (type == "INTERVAL") {
		itype = MAOPROPERTY_INTERVAL;
	} else {
		throw "Invalid MLB Sensor Property type!: " + name;
	}

	if (itype == MAOPROPERTY_INTERVAL)
		throw "Not allowed Interval type for MLB Sensor Property if the value is another property! yet!: "
				+ name;

	MLBSensorProperty* s = new MLBSensorProperty(name, parent, itype, property,
			valueProp);
	_vectorMLB.push_back(s);
	_vectorMLBSensor.push_back(s);

	return *s;

}

MLBSensorRandom& MLBFactory::addMLBSensorRandom(std::string name,
		std::string nparent, float prob) {
	if (!checkMLBName(nparent, name))
		throw "MLB name already exists: " + name;

	MAO& parent = MAOFactory::getInstance()->getMAO(nparent);

	MLBSensorRandom* s = new MLBSensorRandom(name, parent, prob);
	_vectorMLB.push_back(s);
	_vectorMLBSensor.push_back(s);

	return *s;
}

MLBSensorDelay& MLBFactory::addMLBSensorDelay(std::string name,
		std::string nparent, int delayFrames) {
	if (!checkMLBName(nparent, name))
		throw "MLB name already exists: " + name;

	MAO& parent = MAOFactory::getInstance()->getMAO(nparent);

	MLBSensorDelay* s = new MLBSensorDelay(name, parent, delayFrames);
	_vectorMLB.push_back(s);
	_vectorMLBSensor.push_back(s);

	return *s;
}

MLBSensorActuator& MLBFactory::addMLBSensorActuator(std::string name,
		std::string nparent, std::string nactuator) {
	if (!checkMLBName(nparent, name))
		throw "MLB name already exists: " + name;

	MAO& parent = MAOFactory::getInstance()->getMAO(nparent);
	Logger::getInstance()->warning(
			"The MLB Sensor Actuator just observes actuators from its parent!");
	MLBActuator& actuator = getMLBActuator(nparent, nactuator);

	MLBSensorActuator* s = new MLBSensorActuator(name, parent);
	_vectorMLB.push_back(s);
	_vectorMLBSensor.push_back(s);

	actuator.addMLBSensorActuator(*s);

	return *s;
}

MLBSensorCollision& MLBFactory::addMLBSensorCollision(std::string name,
		std::string nparent, const std::string nproperty) {
	if (!checkMLBName(nparent, name))
		throw "MLB name already exists: " + name;

	MAORenderable3D& parent = MAOFactory::getInstance()->getMAORenderable3D(
			nparent);

	MLBSensorCollision* s = new MLBSensorCollision(name, parent, nproperty);
	_vectorMLB.push_back(s);
	_vectorMLBSensor.push_back(s);

	return *s;
}

/* -Controllers */
MLBControllerAND& MLBFactory::addMLBControllerAND(std::string name,
		std::string nparent) {
	if (!checkMLBName(nparent, name))
		throw "MLB name already exists " + name;

	MAO& parent = MAOFactory::getInstance()->getMAO(nparent);

	MLBControllerAND* c = new MLBControllerAND(name, parent);
	_vectorMLB.push_back(c);
	_vectorMLBController.push_back(c);

	return *c;
}

MLBControllerNAND& MLBFactory::addMLBControllerNAND(std::string name,
		std::string nparent) {
	if (!checkMLBName(nparent, name))
		throw "MLB name already exists " + name;

	MAO& parent = MAOFactory::getInstance()->getMAO(nparent);

	MLBControllerNAND* c = new MLBControllerNAND(name, parent);
	_vectorMLB.push_back(c);
	_vectorMLBController.push_back(c);

	return *c;
}

MLBControllerOR& MLBFactory::addMLBControllerOR(std::string name,
		std::string nparent) {
	if (!checkMLBName(nparent, name))
		throw "MLB name already exists " + name;

	MAO& parent = MAOFactory::getInstance()->getMAO(nparent);

	MLBControllerOR* c = new MLBControllerOR(name, parent);
	_vectorMLB.push_back(c);
	_vectorMLBController.push_back(c);

	return *c;
}

MLBControllerNOR& MLBFactory::addMLBControllerNOR(std::string name,
		std::string nparent) {
	if (!checkMLBName(nparent, name))
		throw "MLB name already exists " + name;

	MAO& parent = MAOFactory::getInstance()->getMAO(nparent);

	MLBControllerNOR* c = new MLBControllerNOR(name, parent);
	_vectorMLB.push_back(c);
	_vectorMLBController.push_back(c);

	return *c;
}


/* -Actuators */
MLBActuatorVisibility& MLBFactory::addMLBActuatorVisibility(
		std::string name, std::string nparent, bool value) {
	if (!checkMLBName(nparent, name))
		throw "MLB name already exists " + name;

	try{ //Maybe a MAORenderable3D...
	  MAORenderable3D& parent = MAOFactory::getInstance()->getMAORenderable3D(nparent);
	  MLBActuatorVisibility* a = new MLBActuatorVisibility(name, parent, value);
	  _vectorMLB.push_back(a);
	  _vectorMLBActuator.push_back(a);

	  return *a;
	}catch(const char* e){ //..or it it does not, it should be a MAORenderable2D!
	  MAORenderable2D& parent = MAOFactory::getInstance()->getMAORenderable2D(nparent);
	  MLBActuatorVisibility* a = new MLBActuatorVisibility(name, parent, value);
	  _vectorMLB.push_back(a);
	  _vectorMLBActuator.push_back(a);

	  return *a;
	}
}

MLBActuatorQuitApp& MLBFactory::addMLBActuatorQuitApp(std::string name,
		std::string nparent) {
	if (!checkMLBName(nparent, name))
		throw "MLB name already exists " + name;

	MAO& parent = MAOFactory::getInstance()->getMAO(nparent);

	MLBActuatorQuitApp* a = new MLBActuatorQuitApp(name, parent);
	_vectorMLB.push_back(a);
	_vectorMLBActuator.push_back(a);

	return *a;
}

MLBActuatorProperty& MLBFactory::addMLBActuatorProperty(
		std::string name, std::string nparent, MAOProperty& property,
		MAOValue value, std::string type) {
	if (!checkMLBName(nparent, name))
		throw "MLB name already exists " + name;

	MAO& parent = MAOFactory::getInstance()->getMAO(nparent);

	int itype;

	if (type == "ASSIGN") {
		itype = MAOPROPERTY_ASSIGN;
	} else if (type == "ADD") {
		itype = MAOPROPERTY_ADD;
	} else if (type == "MINUS") {
		itype = MAOPROPERTY_MINUS;
	} else if (type == "MULTIPLY") {
		itype = MAOPROPERTY_MULTIPLY;
	} else if (type == "DIVIDE") {
		itype = MAOPROPERTY_DIVIDE;
	} else {
		throw "Invalid MLB Actuator Property type!: " + name;
	}

	MLBActuatorProperty* a = new MLBActuatorProperty(name, parent, property,
			value, itype);
	_vectorMLB.push_back(a);
	_vectorMLBActuator.push_back(a);

	return *a;
}

MLBActuatorProperty& MLBFactory::addMLBActuatorProperty(
		std::string name, std::string nparent, MAOProperty& property,
		MAOProperty& valueProp, std::string type) {
	if (!checkMLBName(nparent, name))
		throw "MLB name already exists " + name;

	MAO& parent = MAOFactory::getInstance()->getMAO(nparent);

	int itype;

	if (type == "ASSIGN") {
		itype = MAOPROPERTY_ASSIGN;
	} else if (type == "ADD") {
		itype = MAOPROPERTY_ADD;
	} else if (type == "MINUS") {
		itype = MAOPROPERTY_MINUS;
	} else if (type == "MULTIPLY") {
		itype = MAOPROPERTY_MULTIPLY;
	} else if (type == "DIVIDE") {
		itype = MAOPROPERTY_DIVIDE;
	} else {
		throw "Invalid MLB Actuator Property type!: " + name;
	}

	MLBActuatorProperty* a = new MLBActuatorProperty(name, parent, property,
			valueProp, itype);
	_vectorMLB.push_back(a);
	_vectorMLBActuator.push_back(a);

	return *a;
}

MLBActuatorChangePose& MLBFactory::addMLBActuatorChangePose(
		std::string name, std::string nparent, std::string locType,
		btVector3* loc, std::string rotType, btVector3* rot) {
	if (!checkMLBName(nparent, name))
		throw "MLB name already exists " + name;

	int ilocType;
	int irotType;

	if (locType == "LOCAL") {
		ilocType = CHANGEPOSE_LOCAL;
	} else if (locType == "GLOBAL") {
		ilocType = CHANGEPOSE_GLOBAL;
	} else {
		throw "Invalid location type for MLB Actuator Change Pose: " + name;
	}

	if (rotType == "LOCAL") {
		irotType = CHANGEPOSE_LOCAL;
	} else if (rotType == "GLOBAL") {
		irotType = CHANGEPOSE_GLOBAL;
	} else {
		throw "Invalid rotation type for MLB Actuator Change Pose: " + name;
	}

	float locX, locY, locZ;
	float rotX, rotY, rotZ;

	if (loc == 0) {
		locX = 0;
		locY = 0;
		locZ = 0;
	} else {
		locX = loc->x();
		locY = loc->y();
		locZ = loc->z();
	}

	if (rot == 0) {
		rotX = 0;
		rotY = 0;
		rotZ = 0;
	} else {
		rotX = rot->x();
		rotY = rot->y();
		rotZ = rot->z();
	}

	MAORenderable3D& parent = MAOFactory::getInstance()->getMAORenderable3D(
			nparent);

	MLBActuatorChangePose* a = new MLBActuatorChangePose(name, parent,
			ilocType, locX, locY, locZ, irotType, rotX, rotY, rotZ);
	_vectorMLB.push_back(a);
	_vectorMLBActuator.push_back(a);

	return *a;
}

MLBActuatorDistance& MLBFactory::addMLBActuatorDistance(
		std::string name, std::string nparent, std::string nmao,
		MAOProperty& property) {
	if (!checkMLBName(nparent, name))
		throw "MLB name already exists " + name;

	MAOPositionator3D& parent =
			MAOFactory::getInstance()->getMAOPositionator3D(nparent);
	MAOPositionator3D& mao = MAOFactory::getInstance()->getMAOPositionator3D(
			nmao);

	MLBActuatorDistance* a = new MLBActuatorDistance(name, parent, mao,
			property);
	_vectorMLB.push_back(a);
	_vectorMLBActuator.push_back(a);

	return *a;
}

MLBActuatorAng& MLBFactory::addMLBActuatorAng(std::string name,
		std::string nparent, MAOProperty& property, std::string angAxis) {
	if (!checkMLBName(nparent, name))
		throw "MLB name already exists " + name;

	MAOPositionator3D& parent =
			MAOFactory::getInstance()->getMAOPositionator3D(nparent);

	int iangAxis;
	if (angAxis == "X") {
		iangAxis = ANG_X;
	} else if (angAxis == "Y") {
		iangAxis = ANG_Y;
	}else if (angAxis == "Z") {
		iangAxis = ANG_Z;
	} else {
		throw "Invalid ang axis for MLB actuator ang: " + name;
	}

	MLBActuatorAng* a = new MLBActuatorAng(name, parent, property, iangAxis);
	_vectorMLB.push_back(a);
	_vectorMLBActuator.push_back(a);

	return *a;
}

MLBActuatorRandom& MLBFactory::addMLBActuatorRandom(std::string name,
		std::string nparent, MAOProperty& property) {
	if (!checkMLBName(nparent, name))
		throw "MLB name already exists " + name;

	MAO& parent = MAOFactory::getInstance()->getMAO(nparent);

	MLBActuatorRandom* a = new MLBActuatorRandom(name, parent, property);
	_vectorMLB.push_back(a);
	_vectorMLBActuator.push_back(a);

	return *a;
}

MLBActuatorSound& MLBFactory::addMLBActuatorSound(std::string name,
		std::string nparent, const std::string path) {
	if (!checkMLBName(nparent, name))
		throw "MLB name already exists " + name;

	MAO& parent = MAOFactory::getInstance()->getMAO(nparent);

	MLBActuatorSound* a = new MLBActuatorSound(name, parent, path);
	_vectorMLB.push_back(a);
	_vectorMLBActuator.push_back(a);

	return *a;
}



MLBActuatorRelativePose& MLBFactory::addMLBActuatorRelativePose(
		std::string name, std::string nparent, std::string nref,
		MAOProperty& property, bool inverse) {
	if (!checkMLBName(nparent, name))
		throw "MLB name already exists " + name;

	MAOPositionator3D& parent =
			MAOFactory::getInstance()->getMAOPositionator3D(nparent);
	MAOPositionator3D& ref = MAOFactory::getInstance()->getMAOPositionator3D(
			nref);

	MLBActuatorRelativePose* a = new MLBActuatorRelativePose(name, parent, ref,
			property, inverse);
	_vectorMLB.push_back(a);
	_vectorMLBActuator.push_back(a);

	return *a;
}

MLBActuatorAddDynamicObject& MLBFactory::addMLBActuatorAddDynamicObject(
		std::string name, std::string nparent, std::string nmao,
		int timeToExpire, Ogre::Matrix4* offset, btVector3* impulse) {

	if (!checkMLBName(nparent, name))
		throw "MLB name already exists " + name;

	MAOPositionator3D& parent =
			MAOFactory::getInstance()->getMAOPositionator3D(nparent);
	MAORenderable3D& mao = MAOFactory::getInstance()->getMAORenderable3D(nmao);

	MLBActuatorAddDynamicObject* a = new MLBActuatorAddDynamicObject(name,
			parent, mao, timeToExpire, offset, impulse);
	_vectorMLB.push_back(a);
	_vectorMLBActuator.push_back(a);

	return *a;
}

MLBActuatorAnim& MLBFactory::addMLBActuatorAnim(
		std::string name, const std::string nparent,
		std::string nanimChoice, std::string* nanimType) {

	if (!checkMLBName(nparent, name))
		throw "MLB name already exists " + name;

	int animType, animChoice;

	if (nanimChoice == "PLAY") {
		animChoice = PLAY;
	} else if (nanimChoice == "PAUSE") {
		animChoice = PAUSE;
	} else if (nanimChoice == "STOP") {
		animChoice = STOP;
	} else {
		throw "Invalid anim choice for MLB Actuator Anim: " + name;
	}

	if (nanimType != 0) {
		if (*nanimType == "SIMPLE") {
			animType = SIMPLE;
		} else if (*nanimType == "LOOP") {
			animType = LOOP;
		} else if (*nanimType == "PINGPONG") {
			animType = PINGPONG;
		} else {
			throw "Invalid anim type for MLB Actuator Anim: " + name;
		}
	} else {
		animType = SIMPLE;
	}

	MAORenderable3D& parent = MAOFactory::getInstance()->getMAORenderable3D(
			nparent);

	if (parent.getType() != T_MAORENDERABLE3DMODEL) {
		throw "MLB Actuator Anim Type just applicable to MAO Renderable 3D Model: "
				+ name;
	}

	MLBActuatorAnim* a = new MLBActuatorAnim(name,
			(MAORenderable3DModel&) parent, animChoice, animType);
	_vectorMLB.push_back(a);
	_vectorMLBActuator.push_back(a);

	return *a;

}

/* Links! */

void MLBFactory::addMLBLink(std::string parent, std::string a, std::string b) {

	try {
		MLBSensor& s = getMLBSensor(parent, a);
		MLBController& c = getMLBController(parent, b);
		c.addMLBSensor(s);
		return;
	} catch (std::string e) {
	}

	try {
		MLBController& c = getMLBController(parent, a);
		MLBActuator& ac = getMLBActuator(parent, b);
		c.addMLBActuator(ac);
		return;
	} catch (std::string e) {
	}

	throw "Malformed MLB Link between " + a + " and " + b + "!";
}

/* Getters */
MLB& MLBFactory::getMLB(std::string parent, std::string name) {
	for (unsigned int i = 0; i < _vectorMLB.size(); i++) {
		MLB* m = _vectorMLBSensor.at(i);
		MAO& p = m->getParent();
		if (m->getName() == name && parent == p.getName()) {
			return *_vectorMLB.at(i);
		}
	}
	throw "MLB not found exception";
}

MLBSensor& MLBFactory::getMLBSensor(std::string parent,
		std::string name) {
	for (unsigned int i = 0; i < _vectorMLBSensor.size(); i++) {
		MLB* m = _vectorMLBSensor.at(i);
		MAO& p = m->getParent();
		if (m->getName() == name && parent == p.getName()) {
			return *_vectorMLBSensor.at(i);
		}
	}
	throw "MLBSensor not found exception: " + name;
}

MLBController& MLBFactory::getMLBController(std::string parent,
		std::string name) {
	for (unsigned int i = 0; i < _vectorMLBController.size(); i++) {
		MLB* m = _vectorMLBController.at(i);
		MAO& p = m->getParent();

		if (name == m->getName() && parent == p.getName()) {
			return *_vectorMLBController.at(i);
		}
	}

	throw "MLBController not found exception: " + name;
}

MLBActuator& MLBFactory::getMLBActuator(std::string parent,
		std::string name) {
	for (unsigned int i = 0; i < _vectorMLBActuator.size(); i++) {
		MLB* m = _vectorMLBActuator.at(i);
		MAO& p = m->getParent();
		if (m->getName() == name && p.getName() == parent) {
			return *_vectorMLBActuator.at(i);
		}
	}
	throw "MLBActuator not found exception: " + name;
}

std::vector<MLBSensor*>& MLBFactory::getVectorMLBSensor() {
	return _vectorMLBSensor;
}

std::vector<MLBController*>& MLBFactory::getVectorMLBController() {
	return _vectorMLBController;
}

std::vector<MLBActuator*>& MLBFactory::getVectorMLBActuator() {
	return _vectorMLBActuator;
}

bool MLBFactory::checkMLBName(std::string parent,
		std::string name) {
	for (unsigned int i = 0; i < _vectorMLB.size(); i++) {
		MLB* m = _vectorMLB.at(i);
		MAO& p = m->getParent();
		if (name == m->getName() && parent == p.getName()) {
			Logger::getInstance()->error("The name of the MLB " + name
					+ " already exists!");
			return false;
		}
	}

	return true;
}



MLBFactory::~MLBFactory() {
	for (unsigned int i = 0; i < _vectorMLBSensor.size(); i++)
		delete _vectorMLBSensor.at(i);

	for (unsigned int i = 0; i < _vectorMLBActuator.size(); i++)
		delete _vectorMLBActuator.at(i);
	for (unsigned int i = 0; i < _vectorMLBController.size(); i++)
		delete _vectorMLBController.at(i);
}
