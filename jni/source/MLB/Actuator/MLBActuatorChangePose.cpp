/*
 * MLBActuatorChangePose.cpp
 *
 *  Created on: 25/02/2011
 *      Author: cesar
 */

#include <MLB/Actuator/MLBActuatorChangePose.h>

/* Rotation angles in degrees ;)*/
MLBActuatorChangePose::MLBActuatorChangePose(const std::string& name,
		MAORenderable3D& parent, int locType, float locX, float locY,
		float locZ, int rotType, float rotX, float rotY, float rotZ) :
		MLBActuator(name, parent) {
	_locType = locType;
	_loc = Ogre::Vector3(locX, locY, locZ);

	_rotType = rotType;

	Ogre::Quaternion qx, qy, qz;
	qx.FromAngleAxis(Ogre::Degree(rotX), Ogre::Vector3::UNIT_X);
	qy.FromAngleAxis(Ogre::Degree(rotY), Ogre::Vector3::UNIT_Y);
	qz.FromAngleAxis(Ogre::Degree(rotZ), Ogre::Vector3::UNIT_Z);

	_rot = qx * qy * qz;

	_mlbType = T_MLBACTUATORCHANGEPOSE;
}

void MLBActuatorChangePose::specificActuate() {
	if (((MAORenderable3D*) _parent)->getMass() != 0) {
		Logger::getInstance()->error(
				"Can not apply ChangePose Actuator to Dynamic Objects!: "
						+ getName());
		return;
	}

	if (((MAORenderable3D*) _parent)->isPositioned()) {
		// RotL * LocL * RenderablePosM * LocG * RotG * GlobalReferencePosM = res
		if (_rotType == CHANGEPOSE_GLOBAL)
			((MAORenderable3D*) _parent)->getSceneNode().rotate(_rot,
					Ogre::Node::TS_PARENT);
		if (_locType == CHANGEPOSE_GLOBAL)
			((MAORenderable3D*) _parent)->getSceneNode().translate(_loc,
					Ogre::Node::TS_PARENT);

		if (_locType == CHANGEPOSE_LOCAL)
			((MAORenderable3D*) _parent)->getSceneNode().translate(_loc,
					Ogre::Node::TS_LOCAL);
		if (_rotType == CHANGEPOSE_LOCAL)
			((MAORenderable3D*) _parent)->getSceneNode().rotate(_rot,
					Ogre::Node::TS_LOCAL);
	}
}


MLBActuatorChangePose::~MLBActuatorChangePose() {
}

