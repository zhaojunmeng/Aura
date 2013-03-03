/*
 * MAORenderable3D.h
 *
 *  Created on: 21/02/2011
 *      Author: cesar
 */

#ifndef MAORENDERABLE_H_
#define MAORENDERABLE_H_

#define MAO_BOX_SHAPE 0
#define MAO_SPHERE_SHAPE 1
#define MAO_CYLINDER_SHAPE 2
#define MAO_CONVEXTRIANGLEMESH_SHAPE 3

#include <string>
#include <list>
#include <GL/gl.h>
#include <OgreBulletDynamicsRigidBody.h>
#include <MAO/MAOPositionator3D.h>
#include <Kernel/Logger.h>

struct DynamicObjectState{
	bool created;
	Ogre::Matrix4 offset;
	Ogre::Vector3 impulse;
	int timeToExpire; //For instantiated MAO's

	DynamicObjectState():created(false), offset(Ogre::Matrix4::IDENTITY), impulse(0,0,1), timeToExpire(0){}
};


class MAORenderable3D: public MAOPositionator3D {
protected:

	MAOPositionator3D* _globalReference;
	Ogre::Entity* _ent;
	bool _active;

	/* Bullet stuff */
	OgreBulletDynamics::RigidBody* _rigidBody;
	OgreBulletCollisions::CollisionShape* _colShape;

	bool _physic;
	DynamicObjectState _dynamicState;

public:
	MAORenderable3D(const std::string& name, const float& size);
	MAORenderable3D(const MAORenderable3D& o);
	virtual ~MAORenderable3D();
	void setGlobalReference(MAOPositionator3D& globalReference);

	MAOPositionator3D* getGlobalReference();

	void update();

	bool isVisible();
	void setVisible(bool visible);

	void setSize(float size);
	float getSize();

	void setMass(float mass);
	float getMass();

	bool isPhysic();
	void setPhysic(bool physic);

	bool isStatic();
	void activeStatic();

	bool isActive();
	void setActive(bool active);

	int getTimeToExpire();
	void decrementTimeToExpire();
	void setTimeToExpire(int timeToExpire);

	void setEntity(Ogre::Entity* ent){ _ent = ent;}

	OgreBulletDynamics::RigidBody* getRigidBody();
	OgreBulletCollisions::CollisionShape* getCollisionShape();

	void setRigidBody(OgreBulletDynamics::RigidBody* rigidBody);
	void setCollisionShape(OgreBulletCollisions::CollisionShape* colShape);

};

#endif /* MAORENDERABLE_H_ */
