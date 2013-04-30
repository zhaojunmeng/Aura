/*
 * MLBSensorProperty.h
 *
 *  Created on: 25/02/2011
 *      Author: cesar
 */

#ifndef MLBSENSORPROPERTY_H_
#define MLBSENSORPROPERTY_H_

#include <MLB/Sensor/MLBSensor.h>

#define MAOPROPERTY_EQUAL 0
#define MAOPROPERTY_NOTEQUAL 1
#define MAOPROPERTY_INTERVAL 2

class MLBSensorProperty: public MLBSensor {
public:
	MLBSensorProperty(const std::string& name, MAO& parent, const int& type, MAOProperty& property, MAOValue value1, MAOValue value2);
	MLBSensorProperty(const std::string& name, MAO& parent, const int& type, MAOProperty& property, MAOProperty& valueProp);
	virtual ~MLBSensorProperty();

	void evaluate();

	/* Python functions*/
	int mPyGetType();
	void mPySetType(int type);

private:
	MAOProperty* _property;
	MAOValue _value1;
	MAOValue _value2;
	MAOProperty* _valueProp;

	int _type;

	bool equal();
	bool interval();
};

#endif /* MLBSENSORPROPERTY_H_ */
