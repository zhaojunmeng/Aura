/*
 * MLBSensorProperty.cpp
 *
 *  Created on: 25/02/2011
 *      Author: cesar
 */

#include <MLB/Sensor/MLBSensorProperty.h>

MLBSensorProperty::MLBSensorProperty(const std::string& name, MAO& parent,
		const int& type, MAOProperty& property, MAOValue value1,
		MAOValue value2) :
	MLBSensor(name, parent) {

	//Checking types
	if (type == MAOPROPERTY_INTERVAL) {
		int pt = property.getType();
		if (pt != MAOPROPERTY_INT && pt != MAOPROPERTY_FLOAT)
			throw "MAO Property Sensor can not be applied for non Float or Int properties. Could not create "
					+ name;
	}

	_type = type;
	_property = &property;
	_value1 = value1;
	_value2 = value2;
	_valueProp = NULL;
	_mlbType = T_MLBSENSORPROPERTY;
}

MLBSensorProperty::MLBSensorProperty(const std::string& name, MAO& parent,
		const int& type, MAOProperty& property, MAOProperty& valueProp) :
	MLBSensor(name, parent) {
	//Checking types
	if (type == MAOPROPERTY_INTERVAL) {
		throw "Just EQUAL and NOT EQUAL types of Sensor Property are allowed for comparison between MAO Properties: "
				+ name;
	}

	_type = type;
	_property = &property;
	_valueProp = &valueProp;
}

void MLBSensorProperty::evaluate() {
	if (_valueProp != NULL)
		_value1 = *_valueProp;

	switch (_type) {
	case MAOPROPERTY_EQUAL:
		_state = equal();
		break;
	case MAOPROPERTY_NOTEQUAL:
		_state = !equal();
		break;
	case MAOPROPERTY_INTERVAL:
		_state = interval();
		break;
	}

}

bool MLBSensorProperty::equal() {
	switch (_property->getType()) {
	case MAOPROPERTY_INT: {
		return _value1.getValue<int> () == _property->getValue<int> ();
		break;
	}
	case MAOPROPERTY_FLOAT: {
		return _value1.getValue<float> () == _property->getValue<float> ();
		break;
	}
	case MAOPROPERTY_BOOLEAN: {
		return _value1.getValue<bool> () == _property->getValue<bool> ();
		break;
	}
	case MAOPROPERTY_STRING: {
		return _value1.getValue<std::string> () == _property->getValue<
				std::string> ();
		break;
	}

	}
	return false;
}

bool MLBSensorProperty::interval() {
	switch (_property->getType()) {
	case MAOPROPERTY_INT: {
		if (_property->getValue<int> () >= _value1.getValue<int> ()
				&& _property->getValue<int> () <= _value2.getValue<int> ())
			return true;
		break;
	}
	case MAOPROPERTY_FLOAT: {
		if (_property->getValue<float> () >= _value1.getValue<float> ()
				&& _property->getValue<float> () <= _value2.getValue<float> ())
			return true;
		break;
	}
	}

	return false;
}

int MLBSensorProperty::mPyGetType() {
	return _type;
}
void MLBSensorProperty::mPySetType(int type) {
	_type = type;
}

MLBSensorProperty::~MLBSensorProperty() {
}
