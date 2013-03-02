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
}

void MAO::addPropertyFloat(std::string name, float value) {
	if (hasProperty(name))
		throw "Property already exists exception!: " + name;

	MAOProperty* p = new MAOProperty(name, MAOPROPERTY_FLOAT, value);
	_vectorMAOProperty.push_back(p);
}

void MAO::addPropertyString(std::string name, const std::string& value) {
	if (hasProperty(name))
		throw "Property already exists exception!: " + name;

	MAOProperty* p = new MAOProperty(name, MAOPROPERTY_STRING, value);
	_vectorMAOProperty.push_back(p);
}

void MAO::addPropertyBoolean(std::string name, bool value) {
	if (hasProperty(name))
		throw "Property already exists exception!: " + name;

	MAOProperty* p = new MAOProperty(name, MAOPROPERTY_BOOLEAN, value);
	_vectorMAOProperty.push_back(p);
}

void MAO::addPropertyPose(std::string name) {
	if (hasProperty(name))
		throw "Property already exists exception!: " + name;

	MAOProperty* p = new MAOProperty(name, MAOPROPERTY_POSE, Ogre::Matrix4());
	_vectorMAOProperty.push_back(p);
}

void MAO::addPropertyPose(std::string name, Ogre::Matrix4& m) {
	if (hasProperty(name))
		throw "Property already exists exception!: " + name;

	MAOProperty* p = new MAOProperty(name, MAOPROPERTY_POSE, m);
	_vectorMAOProperty.push_back(p);
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


MAO::~MAO() {
	for (unsigned int i = 0; i < _vectorMAOProperty.size(); i++)
		delete _vectorMAOProperty.at(i);
}
