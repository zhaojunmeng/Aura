/*
 * MLBActuatorChangePose.h
 *
 *  Created on: 25/02/2011
 *      Author: cesar
 */

#ifndef MLBACTUATORCHANGEPOSE_H_
#define MLBACTUATORCHANGEPOSE_H_

#define CHANGEPOSE_LOCAL 0
#define CHANGEPOSE_GLOBAL 1
#define DEGREES 3.14159264/180
#include <MLB/Actuator/MLBActuator.h>
#include <MAO/MAOPositionator3D.h>
#include <MAO/MAOMark.h>
#include <MAO/MAORenderable3D.h>

class MLBActuatorChangePose: public MLBActuator {
public:
	MLBActuatorChangePose(const std::string& name, MAORenderable3D& parent,
			int locType, float locX, float locY, float locZ, int rotType,
			float rotX, float rotY, float rotZ);
	virtual ~MLBActuatorChangePose();

	/* Python functions! */
	int mPyGetLocType();
	void mPySetLocType(int locType);
	int mPyGetRotType();
	void mPySetRotType(int rotType);

	VectorFloat mPyGetLoc();
	void mPySetLoc(VectorFloat loc);
	VectorFloat mPyGetRot();
	void mPySetRot(VectorFloat rot);


private:
	int _locType, _rotType;
	float _locX, _locY, _locZ;
	float _rotX, _rotY, _rotZ;

	void specificActuate();
};

#endif /* MLBACTUATORChangePose_H_ */
