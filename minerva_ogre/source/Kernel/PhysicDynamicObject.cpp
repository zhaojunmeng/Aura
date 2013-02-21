/*
 * PhysicDynamicObject.cpp
 *
 *  Created on: 10/03/2011
 *      Author: cesar
 */

#include <Kernel/PhysicDynamicObject.h>

PhysicDynamicObject::PhysicDynamicObject(MAORenderable3D* mao,
		MAOPositionator3D& creationRef, Ogre::Matrix4* offset, btVector3* impulse) :
	PhysicObject(mao) {
	_created = false;
	_creationRef = &creationRef;
	_offset = Ogre::Matrix4::IDENTITY;

	// TODO
	//if (offset != 0) { //Load an identity matrix
	//	_offset = offset;
	//}

	if (impulse == 0) {
		_impulse = btVector3(0, 0, 0);
	} else {
		_impulse = *impulse;
	}


}

bool PhysicDynamicObject::isCreated() {
	return _created;
}

void PhysicDynamicObject::setCreated(bool created) {
	_created = created;
}

Ogre::Matrix4& PhysicDynamicObject::getOffset() {
	return _offset;
}

btVector3& PhysicDynamicObject::getImpulse() {
	return _impulse;
}

MAOPositionator3D& PhysicDynamicObject::getCreationRef() {
	return *_creationRef;
}

PhysicDynamicObject::~PhysicDynamicObject() {
}
