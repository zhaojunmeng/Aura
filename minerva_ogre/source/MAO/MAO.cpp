/*
 * MAO.cpp
 *
 *  Created on: 21/02/2011
 *      Author: cesar
 */

#include <MAO/MAO.h>

MAO::MAO(std::string name) {
	_name = name;
	_type = T_MAO;
}

MAO::MAO(const MAO& o) {
	_type = o._type;
	for (unsigned int i = 0; i < o._vectorMAOProperty.size(); i++) {
		MAOProperty* p = new MAOProperty(*o._vectorMAOProperty.at(i));
		_vectorMAOProperty.push_back(p);
	}
}

std::string MAO::getName() {
	return _name;
}

//--Properties---------------

void MAO::addPropertyInt(std::string name, int value) {
	if (hasProperty(name))
		throw "Property already exists exception!: " + name;

	MAOProperty* p = new MAOProperty(name, MAOPROPERTY_INT, value);
	_vectorMAOProperty.push_back(p);
	_vectorMPYPropertyInt.push_back(new MPYPropertyInt(p));
}

void MAO::addPropertyFloat(std::string name, float value) {
	if (hasProperty(name))
		throw "Property already exists exception!: " + name;

	MAOProperty* p = new MAOProperty(name, MAOPROPERTY_FLOAT, value);
	_vectorMAOProperty.push_back(p);
	_vectorMPYPropertyFloat.push_back(new MPYPropertyFloat(p));
}

void MAO::addPropertyString(std::string name, const std::string& value) {
	if (hasProperty(name))
		throw "Property already exists exception!: " + name;

	MAOProperty* p = new MAOProperty(name, MAOPROPERTY_STRING, value);
	_vectorMAOProperty.push_back(p);
	_vectorMPYPropertyStr.push_back(new MPYPropertyStr(p));
}

void MAO::addPropertyBoolean(std::string name, bool value) {
	if (hasProperty(name))
		throw "Property already exists exception!: " + name;

	MAOProperty* p = new MAOProperty(name, MAOPROPERTY_BOOLEAN, value);
	_vectorMAOProperty.push_back(p);
	_vectorMPYPropertyBool.push_back(new MPYPropertyBool(p));
}

void MAO::addPropertyPose(std::string name) {
	if (hasProperty(name))
		throw "Property already exists exception!: " + name;

	MAOProperty* p = new MAOProperty(name, MAOPROPERTY_POSE, Ogre::Matrix4());
	_vectorMAOProperty.push_back(p);
	_vectorMPYPropertyPose.push_back(new MPYPropertyPose(p));
}

void MAO::addPropertyPose(std::string name, Ogre::Matrix4& m) {
	if (hasProperty(name))
		throw "Property already exists exception!: " + name;

	MAOProperty* p = new MAOProperty(name, MAOPROPERTY_POSE, m);
	_vectorMAOProperty.push_back(p);
	_vectorMPYPropertyPose.push_back(new MPYPropertyPose(p));

}

/* Getters */
MAOProperty& MAO::getProperty(std::string name) {
	for (unsigned int i = 0; i < _vectorMAOProperty.size(); i++) {
		if (_vectorMAOProperty.at(i)->getName() == name)
			return *_vectorMAOProperty.at(i);
	}

	Logger::getInstance()->error("Not property found exception: " + name);
	throw "Not property found exception: " + name;
}

int MAO::getType() {
	return _type;
}

/* Utils */
bool MAO::hasProperty(std::string name) {
	for (unsigned int i = 0; i < _vectorMAOProperty.size(); i++) {
		MAOProperty* p = _vectorMAOProperty.at(i);
		if (p->getName() == name)
			return true;
	}
	return false;
}

/* Python functions! */
boost::python::object MAO::mPyGetProperty(std::string name) {
	try {
		PyObject* pyObj = NULL;
		MAOProperty& prop = getProperty(name);

		switch (prop.getType()) {
		case MAOPROPERTY_INT: {
			MPYPropertyInt& p = getMPYPropertyInt(name);
			boost::python::reference_existing_object::apply<MPYPropertyInt*>::type
					converter;
			pyObj = converter(&p);

		}
			break;

		case MAOPROPERTY_FLOAT: {
			MPYPropertyFloat& p = getMPYPropertyFloat(name);
			boost::python::reference_existing_object::apply<MPYPropertyFloat*>::type
					converter;
			pyObj = converter(&p);

		}
			break;

		case MAOPROPERTY_BOOLEAN: {
			MPYPropertyBool& p = getMPYPropertyBool(name);
			boost::python::reference_existing_object::apply<MPYPropertyBool*>::type
					converter;
			pyObj = converter(&p);

		}
			break;

		case MAOPROPERTY_STRING: {
			MPYPropertyStr& p = getMPYPropertyStr(name);
			boost::python::reference_existing_object::apply<MPYPropertyStr*>::type
					converter;
			pyObj = converter(&p);

		}
			break;
		case MAOPROPERTY_POSE: {
			Logger::getInstance()->warning(
					"MAO Property Pose not supported yet by Python API: "
							+ getName());
		}
			break;
		default:
			Logger::getInstance()->error("Unrecognized MAO Property type: "
					+ getName());
			break;
		}

		return boost::python::object(boost::python::handle<>(pyObj));

	} catch (const char* e) {
		Logger::getInstance()->error("Property " + name + " not found!: "
				+ getName());
		boost::python::throw_error_already_set();

	}
}

MPYPropertyInt& MAO::getMPYPropertyInt(std::string name) {
	for (unsigned int i = 0; i < _vectorMPYPropertyInt.size(); i++) {
		if (_vectorMPYPropertyInt.at(i)->getName() == name) {
			return *_vectorMPYPropertyInt.at(i);
		}
	}
}
MPYPropertyFloat& MAO::getMPYPropertyFloat(std::string name) {
	for (unsigned int i = 0; i < _vectorMPYPropertyFloat.size(); i++) {
		if (_vectorMPYPropertyFloat.at(i)->getName() == name) {
			return *_vectorMPYPropertyFloat.at(i);
		}
	}
}
MPYPropertyStr& MAO::getMPYPropertyStr(std::string name) {
	for (unsigned int i = 0; i < _vectorMPYPropertyStr.size(); i++) {
		if (_vectorMPYPropertyStr.at(i)->getName() == name) {
			return *_vectorMPYPropertyStr.at(i);
		}
	}
}
MPYPropertyBool& MAO::getMPYPropertyBool(std::string name) {
	for (unsigned int i = 0; i < _vectorMPYPropertyBool.size(); i++) {
		if (_vectorMPYPropertyBool.at(i)->getName() == name) {
			return *_vectorMPYPropertyBool.at(i);
		}
	}
}
MPYPropertyPose& MAO::getMPYPropertyPose(std::string name) {
	for (unsigned int i = 0; i < _vectorMPYPropertyPose.size(); i++) {
		if (_vectorMPYPropertyPose.at(i)->getName() == name) {
			return *_vectorMPYPropertyPose.at(i);
		}
	}
}

MAO::~MAO() {
	for (unsigned int i = 0; i < _vectorMAOProperty.size(); i++)
		delete _vectorMAOProperty.at(i);

	for (unsigned int i = 0; i < _vectorMPYPropertyInt.size(); i++)
		delete _vectorMPYPropertyInt.at(i);
	for (unsigned int i = 0; i < _vectorMPYPropertyFloat.size(); i++)
			delete _vectorMPYPropertyFloat.at(i);
	for (unsigned int i = 0; i < _vectorMPYPropertyStr.size(); i++)
			delete _vectorMPYPropertyStr.at(i);
	for (unsigned int i = 0; i < _vectorMPYPropertyBool.size(); i++)
			delete _vectorMPYPropertyBool.at(i);
	for (unsigned int i = 0; i < _vectorMPYPropertyPose.size(); i++)
			delete _vectorMPYPropertyPose.at(i);

}
