/*
 * PhysicsController.h
 *
 *  Created on: 03/03/2011
 *      Author: cesar
 */

#ifndef PHYSICSCONTROLLER_H_
#define PHYSICSCONTROLLER_H_

#define GROUND_HEIGHT 0.01

#ifdef WIN32
#include <windows.h>
#endif

#include <OgreBulletDynamicsRigidBody.h>
#include <OgreBulletCollisions.h>
#include <Shapes/OgreBulletCollisionsStaticPlaneShape.h>
#include <Kernel/Singleton.h>
#include <Kernel/Logger.h>
#include <MAO/MAORenderable3D.h>
#include <MAO/MAOPositionator3D.h>
#include <Factories/MAOFactory.h>

class PhysicsController: public Singleton<PhysicsController> {
public:
	PhysicsController();
	virtual ~PhysicsController();
	void initPhysics();

	bool collision(MAORenderable3D* m1, MAORenderable3D* m2);
	void addStaticRigidBody(MAORenderable3D& body);
	void addDynamicRigidBody(MAORenderable3D& body, float mass, 	Ogre::Matrix4* offset = 0, Ogre::Vector3* impulse = 0);
	void addDynamicRigidBody(MAORenderable3D& body,	MAOPositionator3D& creationRef, float mass, Ogre::Matrix4* offset = 0,	Ogre::Vector3* impulse = 0);

	void createGround(MAOPositionator3D& refGround, Ogre::Vector3& gravity);

	bool isActive();
	void pollPhysics();

	bool removeRigidBody(MAORenderable3D* mao);

private:
	bool _active;
	Ogre::Vector3 _gravity;
	MAORenderable3D* _ground;
	Ogre::AxisAlignedBox _aabox;
	std::list<MAORenderable3D*> _listPhysicObjects;

	OgreBulletDynamics::DynamicsWorld* _colWorld;
	OgreBulletCollisions::DebugDrawer* _debugDrawer;

};

#endif /* PHYSICSCONTROLLER_H_ */
