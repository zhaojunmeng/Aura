/*
 * MLBActuatorAddDynamicObject.cpp
 *
 *  Created on: 14/03/2011
 *      Author: cesar
 */

#include <MLB/Actuator/MLBActuatorAddDynamicObject.h>

MLBActuatorAddDynamicObject::MLBActuatorAddDynamicObject(
		const std::string& name, MAOPositionator3D& parent,
		MAORenderable3D& mao, int timeToExpire, Ogre::Matrix4* offset,
		btVector3* impulse) :
	MLBActuator(name, parent) {
	if (mao.getMass() == 0) {
		throw "MLB Actuator Add Dynamic Object only applicable to Dynamic MAO's (Non-Zero mass): "
				+ name;
	}

	_mao = &mao;
	_timeToExpire = timeToExpire;

	if (offset == 0) { //Load an identity matrix
		_offset = Ogre::Matrix4::IDENTITY;
	} else {
		_offset = *offset;
	}

	if (impulse == 0) {
		_impulse = btVector3(0, 0, 0);
	} else {
		_impulse = *impulse;
	}
	_mlbType = T_MLBACTUATORADDDYNAMICOBJECT;
}

void MLBActuatorAddDynamicObject::specificActuate() {
	MAORenderable3D* m;

	if (!((MAOPositionator3D&) getParent()).isPositioned()) {
		Logger::getInstance()->out(
				"Can not add an object if it is NOT positioned!: " + getName());
		return;
	}

	switch (_mao->getType()) {
	case T_MAORENDERABLE3DMODEL:
		/*m = new MAORenderable3DOrj("", _mao->getSize(),
		 ((MAORenderable3DOrj*) _mao)->getPathOrj(),
		 ((MAORenderable3DOrj*) _mao)->getPathTex());*/
		m = new MAORenderable3DModel(*(MAORenderable3DModel*) _mao);
		break;
	default:
	  Logger::getInstance()->warning("MAO Type Not supported for Add Dynamic Object.. Yet! ;): "
					 + getName());
	  return;
		break;
	}

	MAOFactory::getInstance()->addInstMAORenderable3D(*m, _timeToExpire);
	PhysicsController::getInstance()->addDynamicRigidBody(*m,
			(MAOPositionator3D&) getParent(), _mao->getMass(), &_offset,
			&_impulse);

}


MLBActuatorAddDynamicObject::~MLBActuatorAddDynamicObject() {
}
