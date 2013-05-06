/*
 * MLBActuatorProperty.h
 *
 *  Created on: 24/02/2011
 *      Author: cesar
 */

#ifndef MLBACTUATORPROPERTY_H_
#define MLBACTUATORPROPERTY_H_

#define MAOPROPERTY_ASSIGN 0
#define MAOPROPERTY_ADD 1
#define MAOPROPERTY_MINUS 2
#define MAOPROPERTY_MULTIPLY 3
#define MAOPROPERTY_DIVIDE 4

#include <MLB/Actuator/MLBActuator.h>
#include <MAO/MAOPositionator3D.h>
#include <MAO/MAOProperty.h>

class MLBActuatorProperty:public MLBActuator {
public:
	MLBActuatorProperty(const std::string& name, MAO& parent, MAOProperty& property, MAOValue value, int type);
	MLBActuatorProperty(const std::string& name, MAO& parent, MAOProperty& property, MAOProperty& valueProp, int type);
	virtual ~MLBActuatorProperty();

	MAOProperty& getProperty();

	/* Python functions! */
	int mPyGetOpType();
	void mPySetOpType(int type);

private:
	MAOProperty* _property;
	MAOProperty* _valueProp;
	MAOValue _value;
	int _type;

	void specificActuate();
};

#endif /* MLBACTUATORPROPERTY_H_ */
