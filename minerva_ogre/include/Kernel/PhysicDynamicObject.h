/*
 * PhysicDynamicObject.h
 *
 *  Created on: 10/03/2011
 *      Author: cesar
 */

/*
 * The diference between a PhysicObject and a PhysicDynamicObject
 * is that the last should have place to be created!
 */
#ifndef PHYSICDYNAMICOBJECT_H_
#define PHYSICDYNAMICOBJECT_H_

#ifdef WIN32
#include <windows.h>
#endif

#include <Kernel/PhysicObject.h>

class PhysicDynamicObject: public PhysicObject {
public:
	PhysicDynamicObject(MAORenderable3D* mao, MAOPositionator3D& creationRef, cv::Mat* offset=0, btVector3* impulse=0);
	virtual ~PhysicDynamicObject();

	bool isCreated();
	void setCreated(bool created);

	cv::Mat& getOffset();
	btVector3& getImpulse();

	MAOPositionator3D& getCreationRef();
private:
	bool _created;
	MAOPositionator3D* _creationRef;
	cv::Mat _offset;
	btVector3 _impulse;
};

#endif /* PHYSICDYNAMICOBJECT_H_ */
