/*
 * MLBActuatorProperty.cpp
 *
 *  Created on: 24/02/2011
 *      Author: cesar
 */

#include <MLB/Actuator/MLBActuatorProperty.h>

MLBActuatorProperty::MLBActuatorProperty(const std::string& name, MAO& parent,
		MAOProperty& property, MAOValue value, int type) :
	MLBActuator(name, parent) {

	if (type != MAOPROPERTY_ASSIGN && property.getType() != MAOPROPERTY_FLOAT
			&& property.getType() != MAOPROPERTY_INT)
		throw "Aritmetics operations in MLB Actuator Property are just allowed for Int or Float Properties: "
				+ name;

	_property = &property;
	_valueProp = NULL;
	_value = value;
	_type = type;
	_mlbType = T_MLBACTUATORPROPERTY;
}

MLBActuatorProperty::MLBActuatorProperty(const std::string& name, MAO& parent,
		MAOProperty& property, MAOProperty& valueProp, int type) :
	MLBActuator(name, parent) {
	if (type != MAOPROPERTY_ASSIGN && property.getType() != MAOPROPERTY_FLOAT
			&& property.getType() != MAOPROPERTY_INT)
		throw "Aritmetics operations in MLB Actuator Property are just allowed for Int or Float Properties: "
				+ name;

	_property = &property;
	_valueProp = &valueProp;
	_type = type;
}

void MLBActuatorProperty::specificActuate() {
	if (_valueProp != NULL)
		_value = *_valueProp;

	switch (_property->getType()) {
	case MAOPROPERTY_INT: {
		switch (_type) {
		case MAOPROPERTY_ASSIGN:
			_property->setValue<int> (_value.getValue<int> ());
			break;
		case MAOPROPERTY_ADD:
			_property->setValue<int> (_property->getValue<int> ()
					+ _value.getValue<int> ());
			break;
		case MAOPROPERTY_MINUS:
			_property->setValue<int> (_property->getValue<int> ()
					- _value.getValue<int> ());
			break;
		case MAOPROPERTY_MULTIPLY:
			_property->setValue<int> (_property->getValue<int> ()
					* _value.getValue<int> ());
			break;
		case MAOPROPERTY_DIVIDE:
			if (_value.getValue<int> () == 0) {
				Logger::getInstance()->error(
						"Error in MLB ACtuator Property: Can't divide by zero!: "
								+ getName());
				return;
			}
			_property->setValue<int> (_property->getValue<int> ()
					/ _value.getValue<int> ());
			break;
		}

		break;
	}
	case MAOPROPERTY_FLOAT: {
		switch (_type) {
		case MAOPROPERTY_ASSIGN:
			_property->setValue<float> (_value.getValue<float> ());
			break;
		case MAOPROPERTY_ADD:
			_property->setValue<float> (_property->getValue<float> ()
					+ _value.getValue<float> ());
			break;
		case MAOPROPERTY_MINUS:
			_property->setValue<float> (_property->getValue<float> ()
					- _value.getValue<float> ());
			break;
		case MAOPROPERTY_MULTIPLY:
			_property->setValue<float> (_property->getValue<float> ()
					* _value.getValue<float> ());
			break;
		case MAOPROPERTY_DIVIDE:
			if (_value.getValue<float> () == 0) {
				Logger::getInstance()->error(
						"Error in MLB ACtuator Property: Can't divide by zero!: "
								+ getName());
				return;
			}
			_property->setValue<float> (_property->getValue<float> ()
					/ _value.getValue<float> ());
			break;
		}
		break;
	}
	case MAOPROPERTY_STRING: {
		_property->setValue<std::string> (_value.getValue<std::string> ());
		break;
	}
	case MAOPROPERTY_BOOLEAN: {
		_property->setValue<bool> (_value.getValue<bool> ());
		break;
	}
	case MAOPROPERTY_POSE: {
		_property->setValue<cv::Mat> (_value.getValue<cv::Mat> ());
	}

	}
}

MAOProperty& MLBActuatorProperty::getProperty() {
	return *_property;
}

/* Python functions! */
int MLBActuatorProperty::mPyGetOpType() {
	return _type;
}
void MLBActuatorProperty::mPySetOpType(int type) {
	_type = type;
}

MLBActuatorProperty::~MLBActuatorProperty() {
}
