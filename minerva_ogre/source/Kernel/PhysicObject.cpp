/*
 * PhysicObject.cpp
 *
 *  Created on: 07/03/2011
 *      Author: cesar
 */

#include <Kernel/PhysicObject.h>

PhysicObject::PhysicObject(MAORenderable3D* mao) {
	_mao = mao;

	//Creating the rigid body!
	float mass = mao->getMass();

	btVector3 localInertia(0,0,0);

	btCollisionShape* cs = mao->getCollisionShape();

	if(mass!=0.f){ //Is dynamic!
		cs->calculateLocalInertia(mass,localInertia);
	}

	btTransform t;
	t.setIdentity();

	btDefaultMotionState* ms = new btDefaultMotionState(t);

	btRigidBody::btRigidBodyConstructionInfo rbInfo(mass,ms,cs,localInertia);
	_rigidBody = new btRigidBody(rbInfo);


	//Kinematic object? (Static!)
	if(mass==0.f){
		_rigidBody->setCollisionFlags(_rigidBody->getCollisionFlags() | btCollisionObject::CF_KINEMATIC_OBJECT);
		_rigidBody->setActivationState(DISABLE_DEACTIVATION);
	}


}

MAORenderable3D* PhysicObject::getMAO(){
	return _mao;
}

btRigidBody* PhysicObject::getRigidBody(){
	return _rigidBody;
}

PhysicObject::~PhysicObject() {
	delete _rigidBody->getMotionState();
	delete _rigidBody;
}
