#include <MAO/MAOValue.h>

//Default constructor
MAOValue::MAOValue() {
	_value = NULL;
	_type = MAOPROPERTY_EMPTY;
}

//Copy constructor
MAOValue::MAOValue(const MAOValue& o) {
	_type = o._type;
	_value = NULL;

	switch (_type) {
	case MAOPROPERTY_INT:
		_value = (void*) new int(*(int*)o._value);
		break;
	case MAOPROPERTY_FLOAT:
		_value = (void*) new float(*(float*)o._value);
		break;
	case MAOPROPERTY_BOOLEAN:
		_value = (void*) new bool(*(bool*)o._value);
		break;
	case MAOPROPERTY_STRING:
		_value = (void*) new std::string(*(std::string*)o._value);
		break;
	case MAOPROPERTY_POSE:{
		Ogre::Matrix4* m;
		Ogre::Matrix4* m2 = (Ogre::Matrix4*)o._value;

		m = m2;
		_value = (void*)m;
		break;
	}
	default:
		throw "Unrecognized value type in MAO value copy constructor!";
	}
}

MAOValue& MAOValue::operator=(const MAOValue& o){
	if(&o!=this){ //No copiar sobre sí mismo
		_type = o._type;

		switch (_type) {
			case MAOPROPERTY_INT:
				_value = (void*) new int(*(int*)o._value);
				break;
			case MAOPROPERTY_FLOAT:
				_value = (void*) new float(*(float*)o._value);
				break;
			case MAOPROPERTY_BOOLEAN:
				_value = (void*) new bool(*(bool*)o._value);
				break;
			case MAOPROPERTY_STRING:
				_value = (void*) new std::string(*(std::string*)o._value);
				break;
			case MAOPROPERTY_POSE:
				_value = (void*) new Ogre::Matrix4(*(Ogre::Matrix4*)o._value);
				break;
			}
	}

	return *this;
}

//Returns the String representations of the value
std::string MAOValue::toString() {
	std::ostringstream stm;

	switch (_type) {
	case MAOPROPERTY_INT:
		stm << *(int*) _value;
		return stm.str();
		break;

	case MAOPROPERTY_FLOAT:
		stm << *(float*) _value;
		return stm.str();
		break;

	case MAOPROPERTY_BOOLEAN:
		bool v;
		v = *(bool*) _value;
		if (v) {
			return "true";
		} else {
			return "false";
		}
		break;

	case MAOPROPERTY_STRING:
		stm << *(std::string*) _value;
		return stm.str();
		break;

	case MAOPROPERTY_POSE:
		Logger::getInstance()->error(
				"Unimplemented toString for Pose Properties!");
		break;
	default:
		break;
	}

	return "";
}

int MAOValue::getType() {
	return _type;
}

MAOValue::~MAOValue() {
		if (_value != NULL){
		switch(_type){
		case MAOPROPERTY_INT:
			delete (int*) _value;
			break;
		case MAOPROPERTY_FLOAT:
				delete (float*) _value;
				break;
		case MAOPROPERTY_STRING:
				delete (std::string*) _value;
				break;
		case MAOPROPERTY_BOOLEAN:
				delete (bool*) _value;
				break;
				delete (Ogre::Matrix4*) _value;
		case MAOPROPERTY_POSE:
				break;
		}
	}

}

