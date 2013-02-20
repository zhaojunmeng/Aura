/*
 * PhysicObject.h
 *
 *  Created on: 07/03/2011
 *      Author: cesar
 */

/*
 * Mainly used for Static Rigid Bodies
 */

#ifndef PHYSICOBJECT_H_
#define PHYSICOBJECT_H_

#ifdef WIN32
#include <windows.h>
#endif

#include <MAO/MAORenderable3D.h>
#include <btBulletDynamicsCommon.h>

class PhysicObject {
public:
	PhysicObject(MAORenderable3D* mao);
	virtual ~PhysicObject();

	MAORenderable3D* getMAO();
	btRigidBody* getRigidBody();

private:
	MAORenderable3D* _mao;
	btRigidBody* _rigidBody;

};

#endif /* PHYSICOBJECT_H_ */
