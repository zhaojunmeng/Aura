/*
 * MLBActuatorAddDynamicObject.h
 *
 *  Created on: 14/03/2011
 *      Author: cesar
 */

#ifndef MLBACTUATORADDDYNAMICOBJECT_H_
#define MLBACTUATORADDDYNAMICOBJECT_H_

#include <Factories/MAOFactory.h>
#include <Controllers/PhysicsController.h>
#include <MLB/Actuator/MLBActuator.h>
#include <MAO/MAORenderable3D.h>
#include <MAO/MAORenderable3DModel.h>


class MLBActuatorAddDynamicObject: public MLBActuator {
public:
	MLBActuatorAddDynamicObject(const std::string& name, MAOPositionator3D& parent, MAORenderable3D& mao, int timeToExpire = -1, cv::Mat* offset = 0, btVector3* impulse = 0);
	virtual ~MLBActuatorAddDynamicObject();
	void specificActuate();

	/* Python functions! */
	int mPyGetTimeToExpire();
	void mPySetTimeToExpire(int timeToExpire);
	VectorFloat mPyGetImpulse();
	void mPySetImpulse(VectorFloat impulse);
	VectorFloat mPyGetOffset();
	void mPySetOffset(VectorFloat offset);

private:
	MAORenderable3D* _mao;
	cv::Mat _offset;
	btVector3 _impulse;
	int _timeToExpire;
};

#endif /* MLBACTUATORADDDYNAMICOBJECT_H_ */
