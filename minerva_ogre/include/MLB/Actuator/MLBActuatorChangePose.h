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


private:
	int _locType, _rotType;
	Ogre::Vector3 _loc;
	Ogre::Quaternion _rot;

	void specificActuate();
};

#endif /* MLBACTUATORChangePose_H_ */
