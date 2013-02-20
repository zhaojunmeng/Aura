/*
 * MLBActuatorRelativePose.h
 *
 *  Created on: 02/03/2011
 *      Author: cesar
 */

#ifndef MLBACTUATORRELATIVEPOSE_H_
#define MLBACTUATORRELATIVEPOSE_H_

#include <MLB/Actuator/MLBActuator.h>
#include <MAO/MAOPositionator3D.h>

class MLBActuatorRelativePose: public MLBActuator {
public:
	MLBActuatorRelativePose(const std::string& name, MAOPositionator3D& parent, MAOPositionator3D& ref, MAOProperty& property, bool inverse);
	virtual ~MLBActuatorRelativePose();

	bool mPyGetInverse();
	void mPySetInverse(bool inverse);

private:
	MAOPositionator3D* _ref;
	MAOProperty* _property;
	bool _inverse;

	void specificActuate();
};

#endif /* MLBACTUATORRELATIVEPOSE_H_ */
