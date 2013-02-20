/*
 * PhysicDynamicObject.cpp
 *
 *  Created on: 10/03/2011
 *      Author: cesar
 */

#include <Kernel/PhysicDynamicObject.h>

PhysicDynamicObject::PhysicDynamicObject(MAORenderable3D* mao,
		MAOPositionator3D& creationRef, cv::Mat* offset, btVector3* impulse) :
	PhysicObject(mao) {
	_created = false;
	_creationRef = &creationRef;
	_offset = cv::Mat(4, 4, CV_32F, cv::Scalar(0.f));
	if (offset == 0) { //Load an identity matrix
		_offset.at<float> (0, 0) = 1;
		_offset.at<float> (1, 1) = 1;
		_offset.at<float> (2, 2) = 1;
		_offset.at<float> (3, 3) = 1;
	} else {
		//Copying!
		for(int i=0;i<4;i++){
			for(int j=0;j<4;j++){
				_offset.at<float>(i,j) = offset->at<float>(i,j);
			}
		}
	}

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

cv::Mat& PhysicDynamicObject::getOffset() {
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
