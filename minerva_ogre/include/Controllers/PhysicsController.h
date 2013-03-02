/*
 * PhysicsController.h
 *
 *  Created on: 03/03/2011
 *      Author: cesar
 */

#ifndef PHYSICSCONTROLLER_H_
#define PHYSICSCONTROLLER_H_

#define GROUND_X 0
#define GROUND_Y 1
#define GROUND_Z 2

#define GROUND_HEIGHT 0.01

#ifdef WIN32
#include <windows.h>
#endif

#include <OgreBulletDynamicsRigidBody.h>
#include <Kernel/Singleton.h>
#include <Kernel/Logger.h>
#include <Kernel/PhysicObject.h>
#include <Kernel/PhysicDynamicObject.h>
#include <MAO/MAORenderable3D.h>
#include <MAO/MAOPositionator3D.h>
#include <Factories/MAOFactory.h>

class PhysicsController: public Singleton<PhysicsController> {
public:
	PhysicsController();
	virtual ~PhysicsController();
	void initPhysics();

	bool collision(MAORenderable3D* m1, MAORenderable3D* m2);
	void addStaticRigidBody(MAORenderable3D& body,
			std::string ncollisionShapeType=std::string("BOX"));
	void addDynamicRigidBody(MAORenderable3D& body, float mass,
			Ogre::Matrix4* offset = 0, btVector3* impulse = 0,
			std::string ncollisionShapeType=std::string("BOX"));
	void addDynamicRigidBody(MAORenderable3D& body,
			MAOPositionator3D& creationRef, float mass, Ogre::Matrix4* offset = 0,
			btVector3* impulse = 0,
			std::string ncollisionShapeType=std::string("BOX"));

	void setMAOGround(MAOPositionator3D& ground, std::string& axis,
			float gravity = -9.8f);

	MAOPositionator3D& getMAOGround();

	bool isActive();

	void pollPhysics();

	bool removeRigidBody(MAORenderable3D* mao);
	bool removeDynamicRigidBody(MAORenderable3D* mao);
	bool removeStaticRigidBody(MAORenderable3D* mao);

	btDiscreteDynamicsWorld* _world;


private:
	bool _active;

	std::vector<PhysicDynamicObject*> _vectorPhysicDynamicObject;
	std::vector<PhysicObject*> _vectorPhysicStaticObject;

	MAOPositionator3D* _maoGround;
	btRigidBody* _ground;

	btDispatcher* _dispatcher;
	btBroadphaseInterface* _broadphase;
	btConstraintSolver* _solver;
	btCollisionConfiguration* _collisionConf;

	btCollisionWorld* _colWorld;
	btDispatcher* _colDispatcher;
	btBroadphaseInterface* _colBroadphase;
	btCollisionConfiguration* _colCollisionConf;


};

#endif /* PHYSICSCONTROLLER_H_ */
