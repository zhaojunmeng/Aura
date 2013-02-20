/*
 * MLBControllerScript.cpp
 *
 *  Created on: 04/04/2011
 *      Author: cesar
 */

#include <MLB/Controller/MLBControllerScript.h>

using namespace std;

MLBControllerScript::MLBControllerScript(const std::string& name, MAO& parent,
		const boost::filesystem::path& path) :
	MLBController(name, parent) {
	_path = path;
	_compiled = false;

	compileScript();
	_mlbType = T_MLBCONTROLLERSCRIPT;
}

void MLBControllerScript::evaluate() {
	/* Intentionally empty ;) */
}

boost::python::object* MLBControllerScript::getCompiledObj() {
	if (_compiled)
		return &_compiledObj;
	else
		return NULL;
}

void MLBControllerScript::setCompiled(bool compiled) {
	_compiled = compiled;
}

void MLBControllerScript::compileScript() {
	//Allocating the memory!
	Resource& r = ResourcesManager::getInstance()->getResource(_path);
	char buf [r.getSize() + 2]; //Allocating the memory!

	for(unsigned int i = 0; i<r.getSize(); i++)
		buf[i] = r.getData()[i];

	buf[r.getSize()] = '\n';
	buf[r.getSize() + 1] = '\0';

	try {
		_compiledObj = boost::python::object(boost::python::handle<>(
				boost::python::borrowed(Py_CompileString((char*) &buf,
						_path.generic_string().c_str(), Py_file_input))));
	} catch (boost::python::error_already_set e) {
		Logger::getInstance()->error("Error compiling the script: " + getName());
		PyErr_Print();
		//delete[] buf;
		_compiled = false;
		return;
	}

	//delete[] buf;
	_compiled = true;

}

/* Python functions! */

object MLBControllerScript::mPyGetSensor(std::string name) {
	MLBSensor* s = NULL;

	//Search the sensor
	for (unsigned int i = 0; i < _vectorMLBSensor.size(); i++) {
		MLBSensor* a = _vectorMLBSensor.at(i);
		if (a->getName() == name) {
			s = a;
			break;
		}
	}

	if(s==NULL){
		Logger::getInstance()->error("MLB Sensor not found in script!: "+getName());
		throw "MLB Sensor "+name+" not found in script!: "+getName();
	}

	//Looking for the converter type
	PyObject* pyObj;
	switch (s->getMLBType()) {
	case T_MLBSENSORALWAYS: {
		reference_existing_object::apply<MLBSensorAlways*>::type converter;
		pyObj = converter((MLBSensorAlways*)s);
	}
		break;
	case T_MLBSENSORACTUATOR: {
		reference_existing_object::apply<MLBSensorActuator*>::type converter;
		pyObj = converter((MLBSensorActuator*)s);
	}
		break;
	case T_MLBSENSORCOLLISION: {
		reference_existing_object::apply<MLBSensorCollision*>::type converter;
		pyObj = converter((MLBSensorCollision*)s);
	}
		break;
	case T_MLBSENSORDELAY: {
		reference_existing_object::apply<MLBSensorDelay*>::type converter;
		pyObj = converter((MLBSensorDelay*)s);
	}
		break;
	case T_MLBSENSORKEYBOARD: {
		reference_existing_object::apply<MLBSensorKeyboard*>::type converter;
		pyObj = converter((MLBSensorKeyboard*)s);
	}
		break;
	case T_MLBSENSORNEAR: {
		reference_existing_object::apply<MLBSensorNear*>::type converter;
		pyObj = converter((MLBSensorNear*)s);
	}
		break;
	case T_MLBSENSORPROPERTY: {
		reference_existing_object::apply<MLBSensorProperty*>::type converter;
		pyObj = converter((MLBSensorProperty*)s);
	}
		break;
	case T_MLBSENSORRANDOM: {
		reference_existing_object::apply<MLBSensorRandom*>::type converter;
		pyObj = converter((MLBSensorRandom*)s);
	}
		break;
	default: {
		Logger::getInstance()->error("Unrecognized MLBSensor Type!: "
				+ getName());
		throw "Unrecognized MLBSensor Type!: "+getName();
		break;
	}
	}

	return object(handle<> (pyObj));
}

object MLBControllerScript::mPyGetActuator(std::string name) {
	MLBActuator* a = NULL;

	//Search the actuator
	for (unsigned int i = 0; i < _vectorMLBActuator.size(); i++) {
		MLBActuator* s = _vectorMLBActuator.at(i);
		if (s->getName() == name) {
			a = s;
			break;
		}
	}

	if(a==NULL){
		Logger::getInstance()->error("MLBActuator \""+name+"\" not found in script!: "+ getName());
		throw "MLBActuator "+name+" not found in script!: "+getName();
	}
	//Looking for the converter type

	PyObject* pyObj;
	switch (a->getMLBType()) {
	case T_MLBACTUATORADDDYNAMICOBJECT: {
		reference_existing_object::apply<MLBActuatorAddDynamicObject*>::type
				converter;
		pyObj = converter((MLBActuatorAddDynamicObject*)a);
	}
		break;
	case T_MLBACTUATORANG: {
		reference_existing_object::apply<MLBActuatorAng*>::type converter;
		pyObj = converter((MLBActuatorAng*)a);
	}
		break;
	case T_MLBACTUATORANIM: {
		reference_existing_object::apply<MLBActuatorAnim*>::type converter;
		pyObj = converter((MLBActuatorAnim*)a);
	}
		break;
	case T_MLBACTUATORCHANGEPOSE: {
		reference_existing_object::apply<MLBActuatorChangePose*>::type
				converter;
		pyObj = converter((MLBActuatorChangePose*)a);
	}
		break;
	case T_MLBACTUATORDISTANCE: {
		reference_existing_object::apply<MLBActuatorDistance*>::type converter;
		pyObj = converter((MLBActuatorDistance*)a);
	}
		break;
	case T_MLBACTUATORPATHADDPOINT: {
		reference_existing_object::apply<MLBActuatorPathAddPoint*>::type
				converter;
		pyObj = converter((MLBActuatorPathAddPoint*)a);
	}
		break;
	case T_MLBACTUATORPATHREMOVEPOINTS: {
		reference_existing_object::apply<MLBActuatorPathRemovePoints*>::type
				converter;
		pyObj = converter((MLBActuatorPathRemovePoints*)a);
	}
		break;
	case T_MLBACTUATORPROPERTY: {
		reference_existing_object::apply<MLBActuatorProperty*>::type converter;
		pyObj = converter((MLBActuatorProperty*)a);
	}
		break;
	case T_MLBACTUATORQUITAPP: {
		reference_existing_object::apply<MLBActuatorQuitApp*>::type converter;
		pyObj = converter((MLBActuatorQuitApp*)a);
	}
		break;
	case T_MLBACTUATORRANDOM: {
		reference_existing_object::apply<MLBActuatorRandom*>::type converter;
		pyObj = converter((MLBActuatorRandom*)a);
	}
		break;
	case T_MLBACTUATORRELATIVEPOSE: {
		reference_existing_object::apply<MLBActuatorRelativePose*>::type
				converter;
		pyObj = converter((MLBActuatorRelativePose*)a);
	}
		break;
	case T_MLBACTUATORSOUND: {
		reference_existing_object::apply<MLBActuatorSound*>::type converter;
		pyObj = converter((MLBActuatorSound*)a);
	}
		break;
	case T_MLBACTUATORVISIBILITY: {
		reference_existing_object::apply<MLBActuatorVisibility*>::type
				converter;
		pyObj = converter((MLBActuatorVisibility*)a);
	}
		break;
	default:
		Logger::getInstance()->error("Unrecognized MLBActuator Type!: "
				+ getName());
		throw "Unrecognized MLBActuator Type!: "+getName();
		break;
	}

	return object(handle<> (pyObj));
}

MLBControllerScript::~MLBControllerScript() {
}
