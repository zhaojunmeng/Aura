/*
 * PhysicsController.cpp
 *
 *  Created on: 03/03/2011
 *      Author: cesar
 */

#include <Controllers/PhysicsController.h>

PhysicsController::PhysicsController() {
	_ground = NULL;
	_active = false;

	_colCollisionConf = new btDefaultCollisionConfiguration();
	_colDispatcher = new btCollisionDispatcher(_colCollisionConf);
	_colBroadphase = new btDbvtBroadphase();

	_colWorld = new btCollisionWorld(_colDispatcher, _colBroadphase,
			_colCollisionConf);
}

void PhysicsController::addStaticRigidBody(MAORenderable3D& body,
		std::string ncollisionShapeType) {
	if (!isActive()) {
		throw "Physics Controller is not active!: " + body.getName();
	}

	PhysicObject* po;

	body.setMass(0);

	body.setPhysic(true);

	//generateMAOCollisionShape(&body, ncollisionShapeType);

	if (body.getGlobalReference() == NULL) {
		Logger::getInstance()->error(
				"Trying to add a Class MAO as a Static Object! :"
						+ body.getName());

	} else {
		po = new PhysicObject(&body);
		_vectorPhysicStaticObject.push_back(po);

		_world->addRigidBody(po->getRigidBody());
	}
}

void PhysicsController::addDynamicRigidBody(MAORenderable3D& body, float mass,
		Ogre::Matrix4* offset, btVector3* impulse, std::string ncollisionShapeType) {

	MAOPositionator3D* creationRef = body.getGlobalReference();

	if (creationRef != NULL) {
		addDynamicRigidBody(body, *creationRef, mass, offset, impulse,
				ncollisionShapeType);
	} else {
		Logger::getInstance()->out(
				"Adding a Dynamic Object that is a Class MAO: "
						+ body.getName());
		if (mass == 0) {
			throw "Physic Dynamic Object should have Non-Zero Mass!: "
					+ body.getName();
		}

		body.setMass(mass);

		body.setActive(false); //Hay que determinar el momento de la creación!
		body.setPhysic(true);
	}
}

void PhysicsController::addDynamicRigidBody(MAORenderable3D& body,
		MAOPositionator3D& creationRef, float mass, Ogre::Matrix4* offset,
		btVector3* impulse, std::string ncollisionShapeType) {
	if (!isActive()) {
	  Logger::getInstance()->warning("Physics Controller is not active!: "+body.getName());
		throw "Physics Controller is not active!: " + body.getName();
	}

	PhysicDynamicObject* po;

	if (mass == 0) {
	  Logger::getInstance()->warning("Physics Dynamic Object should have Non-Zero Mass!: "+body.getName());
		throw "Physic Dynamic Object should have Non-Zero Mass!: "
				+ body.getName();
	}

	body.setMass(mass);

	body.setActive(false); //Hay que determinar el momento de la creación!
	body.setGlobalReference(*_maoGround);

	body.setPhysic(true);

	//generateMAOCollisionShape(&body, ncollisionShapeType);

	// TODO
	//po = new PhysicDynamicObject(&body, creationRef, offset, impulse);
	_vectorPhysicDynamicObject.push_back(po);
}

bool PhysicsController::isActive() {
	return _active;
}

bool PhysicsController::removeRigidBody(MAORenderable3D* mao) {
	if (!isActive()) {
		throw "Physics Controller is not active!: " + mao->getName();
	}

	return removeDynamicRigidBody(mao) || removeStaticRigidBody(mao);
}

bool PhysicsController::removeDynamicRigidBody(MAORenderable3D* mao) {
	if (!isActive()) {
		throw "Physics Controller is not active!: " + mao->getName();
	}

	std::vector<PhysicDynamicObject*>::iterator it;

	for (it = _vectorPhysicDynamicObject.begin(); it
			!= _vectorPhysicDynamicObject.end(); it++) {
		if ((*it)->getMAO() == mao) {
			_world->removeRigidBody((*it)->getRigidBody());

			PhysicDynamicObject* p = *it;

			_vectorPhysicDynamicObject.erase(it);

			delete p;

			return true;
		}
	}
	Logger::getInstance()->error("Error removing the dynamic rigid body: "
			+ mao->getName());

	return false;
}

bool PhysicsController::removeStaticRigidBody(MAORenderable3D* mao) {
	if (!isActive()) {
		throw "Physics Controller is not active!: " + mao->getName();
	}

	std::vector<PhysicObject*>::iterator it;

	for (it = _vectorPhysicStaticObject.begin(); it
			!= _vectorPhysicStaticObject.end(); it++) {
		if ((*it)->getMAO() == mao) {
			_world->removeRigidBody((*it)->getRigidBody());

			PhysicObject* p = *it;

			_vectorPhysicStaticObject.erase(it);

			delete p;

			return true;
		}
	}

	Logger::getInstance()->error("Error removing the dynamic rigid body: "
			+ mao->getName());

	return false;
}

void PhysicsController::pollPhysics() {

	if (isActive() && _maoGround->isPositioned()) {

		//Managing static MAO's (They are Kinemtic, so we have tu update its position!)
		for (unsigned int i = 0; i < _vectorPhysicStaticObject.size(); i++) {
			PhysicObject* pO = _vectorPhysicStaticObject.at(i);
			Ogre::Matrix4 m;
			// TODO
			//m = pO->getMAO()->getGlobalReference()->getPosMatrix()
			//		* _maoGround->getPosMatrix().inv();

			btTransform t;
			// TODO
			//t.setFromOpenGLMatrix((btScalar*) m.data);
			//pO->getRigidBody()->getMotionState()->setWorldTransform(t);

		}

		//_world->stepSimulation(1.f / 60, 10);
		_world->stepSimulation(1.f / 60, 10);

		//Managing dynamics MAO's
		for (unsigned int i = 0; i < _vectorPhysicDynamicObject.size(); i++) {
			PhysicDynamicObject* pO = _vectorPhysicDynamicObject.at(i);
			if (!pO->isCreated()) { //Creating the dynamic object!!
				if (pO->getCreationRef().isPositioned()) {
					pO->setCreated(true);
					pO->getMAO()->setActive(true);

					Ogre::Matrix4 m;
					// TODO
					//m = pO->getOffset() * pO->getCreationRef().getPosMatrix()* _maoGround->getPosMatrix().inv();

					btTransform t;
					// TODO
					//t.setFromOpenGLMatrix((btScalar*) m.data);

					delete pO->getRigidBody()->getMotionState();
					btDefaultMotionState* ms = new btDefaultMotionState(t);
					pO->getRigidBody()->setMotionState(ms);

					/* The impulse should be in the local coordinates system of the reference */
					/* Some transforms :)*/
					//TODO
					/*Ogre::Vector3 localImpulse;
					localImpulse.x = pO->getImpulse().x();
					localImpulse.y = pO->getImpulse().y();
					localImpulse.z = pO->getImpulse().z();

					Ogre::Vector4 globalImpulse = m.inv()*localImpulse;


					btVector3 btGlobalImpulse(globalImpulse.x,
											  globalImpulse.y,
											  globalImpulse.z;

					pO->getRigidBody()->applyCentralImpulse(btGlobalImpulse);

					_world->addRigidBody(pO->getRigidBody());
*/
//					pO->getMAO()->setRelativeMatrix(m);
				}
			} else {
				float m[16];
				btTransform t;
				pO->getRigidBody()->getMotionState()->getWorldTransform(t);
				t.getOpenGLMatrix(m);

	//			pO->getMAO()->setRelativeMatrix(m);

			}
		}



	}
}



void PhysicsController::setMAOGround(MAOPositionator3D& ground,
		std::string& axis, float gravity) {
	if (!isActive()) {
		throw "Physics Controller is not active!: " + ground.getName();
	}

	_maoGround = &ground;

	int iaxis;
	if (axis == "X") {
		iaxis = GROUND_X;
	} else if (axis == "Y") {
		iaxis = GROUND_Y;
	} else if (axis == "Z") {
		iaxis = GROUND_Z;
	} else {
		throw "Invalid axis for the ground!: " + axis;
	}

	//Deleting ground!
	if (_ground != NULL) {
		delete _ground->getCollisionShape();
		delete _ground->getMotionState();
		delete _ground;
	}

	btBoxShape* s;

	switch (iaxis) {
	case GROUND_X:
		_world->setGravity(btVector3(gravity, 0, 0));
		s = new btBoxShape(btVector3(GROUND_HEIGHT, 20., 20.));
		break;

	case GROUND_Y:
		_world->setGravity(btVector3(0, gravity, 0));
		s = new btBoxShape(btVector3(20., GROUND_HEIGHT, 20.));
		break;

	case GROUND_Z:
		_world->setGravity(btVector3(0, 0, gravity));
		s = new btBoxShape(btVector3(20., 20.,GROUND_HEIGHT));
		break;
	}

	float mass = 0;

	btTransform gT;
	gT.setIdentity();

	btDefaultMotionState* ms = new btDefaultMotionState(gT);

	btVector3 localInertia(0, 0, 0);

	btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, ms, s, localInertia);

	_ground = new btRigidBody(rbInfo);

	_world->addRigidBody(_ground);

}

MAOPositionator3D& PhysicsController::getMAOGround() {
	if (_ground == NULL) {
		throw "There is no Ground in Physics Controller!";
	}
	return *_maoGround;
}


bool PhysicsController::collision(MAORenderable3D* m1, MAORenderable3D* m2) {
	bool collision = false;

	btCollisionObject ob1 = btCollisionObject();
	btCollisionObject ob2 = btCollisionObject();

	btCollisionShape* cs1 = NULL;
	btCollisionShape* cs2 = NULL;

	//Getting m1 Collision Shape
	switch (m1->getCollisionShapeType()) {
	case MAO_BOX_SHAPE: {
		btBoxShape* bs1 =
				new btBoxShape(*(btBoxShape*) m1->getCollisionShape());
		cs1 = bs1;
		break;
	}
	case MAO_SPHERE_SHAPE: {
		btSphereShape* bs1 = new btSphereShape(
				*(btSphereShape*) m1->getCollisionShape());
		cs1 = bs1;
		break;
	}
	case MAO_CYLINDER_SHAPE: {
		btCylinderShape* bs1 = new btCylinderShape(
				*(btCylinderShape*) m1->getCollisionShape());
		cs1 = bs1;
		break;
	}
	case MAO_CONVEXTRIANGLEMESH_SHAPE: {
		btConvexHullShape* bs1 = new btConvexHullShape(
				*(btConvexHullShape*) m1->getCollisionShape());
		cs1 = bs1;
		break;
	}
	}
	Logger::getInstance()->warning(
			"Arreglar los shape en collision de physics controller!!!");
	//Getting m2 Collision Shape
	switch (m2->getCollisionShapeType()) {
	case MAO_BOX_SHAPE: {
		btBoxShape* bs2 =
				new btBoxShape(*(btBoxShape*) m2->getCollisionShape());
		cs2 = bs2;
		break;
	}
	case MAO_SPHERE_SHAPE: {
		btSphereShape* bs2 = new btSphereShape(
				*(btSphereShape*) m2->getCollisionShape());
		cs2 = bs2;
		break;
	}
	case MAO_CYLINDER_SHAPE: {
		btCylinderShape* bs2 = new btCylinderShape(
				*(btCylinderShape*) m2->getCollisionShape());
		cs2 = bs2;
		break;
	}
	case MAO_CONVEXTRIANGLEMESH_SHAPE: {
		btConvexHullShape* bs2 = new btConvexHullShape(
				*(btConvexHullShape*) m1->getCollisionShape());
		cs2 = bs2;
		break;
	}

	}

	ob1.setCollisionShape(cs1);
	ob2.setCollisionShape(cs2);

	float d1[16];
	float d2[16];

	// TODO
	/*FOR (INT I = 0; I < 16; I++) {
		D1[I] = ((FLOAT*) M1->GETPOSMATRIX().DATA)[I];
		D2[I] = ((FLOAT*) M2->GETPOSMATRIX().DATA)[I];
	}*/

	ob1.getWorldTransform().setFromOpenGLMatrix((btScalar*) d1);
	ob2.getWorldTransform().setFromOpenGLMatrix((btScalar*) d2);

	//btCollisionAlgorithm* algo = _colWorld->getDispatcher()->findAlgorithm(
		//	&ob1, &ob2);

 	//btManifoldResult contactPointResult(&ob1, &ob2);
	//algo->processCollision(&ob1, &ob2, _colWorld->getDispatchInfo(),
			//&contactPointResult);

	//btManifoldArray manifoldArray;
	//algo->getAllContactManifolds(manifoldArray);

	//for (int i = 0; i < manifoldArray.size() && !collision; i++) {
		//btPersistentManifold* contactManifold = manifoldArray[i];
		//int numContacts = contactManifold->getNumContacts();
		//if (numContacts > 0) {
		//	collision = true;
		//}
	//}

	delete cs1;
	delete cs2;

	return collision;
}

void PhysicsController::initPhysics() {
	if (isActive()) {
		throw "Physics Controller is already active!";
	}

	_collisionConf = new btDefaultCollisionConfiguration();
	_dispatcher = new btCollisionDispatcher(_collisionConf);
	_broadphase = new btDbvtBroadphase();
	_solver = new btSequentialImpulseConstraintSolver();

	_world = new btDiscreteDynamicsWorld(_dispatcher, _broadphase, _solver,
			_collisionConf);

	_active = true;

}


PhysicsController::~PhysicsController() {
	//Deleting in reverse order
	if (isActive()) {
		for (unsigned int i = 0; i < _vectorPhysicDynamicObject.size(); i++) {
			// TODO
			//if (_vectorPhysicDynamicObject.at(i)->isCreated()) {
			//	_world->removeRigidBody(
			//			_vectorPhysicDynamicObject.at(i)->getRigidBody());
			//}

			delete _vectorPhysicDynamicObject.at(i);
		}

		for (unsigned int i = 0; i < _vectorPhysicStaticObject.size(); i++) {
			_world->removeRigidBody(
					_vectorPhysicStaticObject.at(i)->getRigidBody());
			delete _vectorPhysicStaticObject.at(i);
		}

		//Deleting ground!
		if (_ground != NULL) {
			delete _ground->getCollisionShape();
			delete _ground->getMotionState();
			delete _ground;
		}
#ifndef WIN32
		delete _world;
#endif
		delete _solver;
		delete _broadphase;
		delete _dispatcher;
		delete _collisionConf;
	}
	delete _colWorld;
	delete _colBroadphase;
	delete _colDispatcher;
	delete _colCollisionConf;
}
