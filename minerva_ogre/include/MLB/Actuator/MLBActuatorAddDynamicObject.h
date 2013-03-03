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
	MLBActuatorAddDynamicObject(const std::string& name,
			MAOPositionator3D& parent, MAORenderable3D& mao, int timeToExpire =
					-1, Ogre::Matrix4* offset = 0, Ogre::Vector3* impulse = 0);
	virtual ~MLBActuatorAddDynamicObject();
	void specificActuate();

private:
	MAORenderable3D* _mao;
	Ogre::Matrix4 _offset;
	Ogre::Vector3 _impulse;
	int _timeToExpire;
};

#endif /* MLBACTUATORADDDYNAMICOBJECT_H_ */
