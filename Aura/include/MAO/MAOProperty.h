/*
 * MAOProperty.h
 *
 *  Created on: 24/02/2011
 *      Author: cesar
 */

#ifndef MAOPROPERTY_H_
#define MAOPROPERTY_H_

#include <sstream>
#include <string>

#include <MAO/MAOValue.h>

class MAOProperty: public MAOValue {
public:
	template<class T>
	MAOProperty(const std::string& name, int type, T value) :
		MAOValue(type, value) {
		_name = name;
	}
	MAOProperty(const MAOProperty& o) :
		MAOValue(o) {
		_name = o._name;
	}
	~MAOProperty();

	std::string getName();

protected:
	std::string _name;

};

template<class T>
struct MPYProperty {
	MAOProperty* _mp;

	MPYProperty(MAOProperty* mp) {
		_mp = mp;
	}

	std::string getName() {
		return _mp->getName();
	}

	T& getValue() {
		return _mp->getValue<T> ();
	}

	void setValue(T value) {
		_mp->setValue<T> (value);
	}
};

typedef MPYProperty<int> MPYPropertyInt;
typedef MPYProperty<float> MPYPropertyFloat;
typedef MPYProperty<std::string> MPYPropertyStr;
typedef MPYProperty<bool> MPYPropertyBool;
typedef MPYProperty<Ogre::Matrix4> MPYPropertyPose;

#endif /* MAOPROPERTY_H_ */
