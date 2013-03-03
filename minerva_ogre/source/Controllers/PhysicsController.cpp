/*
 * PhysicsController.cpp *
 *  Created on: 03/03/2011
 *      Author: cesar
 */

#include <Controllers/PhysicsController.h>

PhysicsController::PhysicsController() :
		_active(false), _ground(NULL) {

}

void PhysicsController::addStaticRigidBody(MAORenderable3D& body) {
	if (!isActive()) {
		throw "Physics Controller is not active!: " + body.getName();
	}

	body.setMass(0);
	body.setPhysic(true);

	// TODO!
	//generateMAOCollisionShape(&body, ncollisionShapeType);

	if (body.getGlobalReference() == NULL) {
		Logger::getInstance()->error(
				"Trying to add a Class MAO as a Static Object! :"
						+ body.getName());
	} else {
		_listPhysicObjects.push_back(&body);
	}
}

void PhysicsController::addDynamicRigidBody(MAORenderable3D& body, float mass,
		Ogre::Matrix4* offset, Ogre::Vector3* impulse) {

	MAOPositionator3D* creationRef = body.getGlobalReference();

	// TODO is this method necessary?
	if (creationRef != NULL) {
		addDynamicRigidBody(body, *creationRef, mass, offset, impulse);
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
		Ogre::Vector3* impulse) {
	if (!isActive()) {
		Logger::getInstance()->warning(
				"Physics Controller is not active!: " + body.getName());
		throw "Physics Controller is not active!: " + body.getName();
	}

	if (mass == 0) {
		Logger::getInstance()->warning(
				"Physics Dynamic Object should have Non-Zero Mass!: "
						+ body.getName());
		throw "Physic Dynamic Object should have Non-Zero Mass!: "
				+ body.getName();
	}

	body.setMass(mass);
	body.setActive(false); //Hay que determinar el momento de la creación!
	body.setGlobalReference(*_ground);
	body.setPhysic(true);

	// TODO
	//generateMAOCollisionShape(&body, ncollisionShapeType);

	// TODO
	_listPhysicObjects.push_back(&body);
}

bool PhysicsController::isActive() {
	return _active;
}

bool PhysicsController::removeRigidBody(MAORenderable3D* mao) {
	if (!isActive()) {
		throw "Physics Controller is not active!: " + mao->getName();
	}

	std::list<MAORenderable3D*>::iterator it;

	// TODO does this work?
	_listPhysicObjects.remove(mao);
	/*for (it = _listPhysicObjects.begin();
	 it != _listPhysicObjects.end(); it++) {
	 if ((*it)->getMAO() == mao) {
	 // TODO
	 //_world->removeRigidBody((*it)->getRigidBody());

	 MAORenderable3D* p = *it;

	 _listPhysicObjects.erase(it);

	 delete p;

	 return true;
	 }
	 }
	 */Logger::getInstance()->error(
			"Error removing the dynamic rigid body: " + mao->getName());

	return false;
}

void PhysicsController::pollPhysics() {

	//if (isActive() && _maoGround->isPositioned()) {

	//TODO
	//Managing static MAO's (They are Kinemtic, so we have tu update its position!)
	for (unsigned int i = 0; i < _listPhysicObjects.size(); i++) {
		//PhysicObject* pO = _vectorPhysicStaticObject.at(i);
		Ogre::Matrix4 m;
		// TODO
		//m = pO->getMAO()->getGlobalReference()->getPosMatrix()
		//		* _maoGround->getPosMatrix().inv();

		//btTransform t;
		// TODO
		//t.setFromOpenGLMatrix((btScalar*) m.data);
		//pO->getRigidBody()->getMotionState()->setWorldTransform(t);

	}

	//_world->stepSimulation(1.f / 60, 10);
	//_world->stepSimulation(1.f / 60, 10);

	//Managing dynamics MAO's
	/*for (unsigned int i = 0; i < _vectorPhysicDynamicObject.size(); i++) {
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

	 The impulse should be in the local coordinates system of the reference
	 Some transforms :)
	 //TODO
	 Ogre::Vector3 localImpulse;
	 localImpulse.x = pO->getImpulse().x();
	 localImpulse.y = pO->getImpulse().y();
	 localImpulse.z = pO->getImpulse().z();

	 Ogre::Vector4 globalImpulse = m.inv()*localImpulse;


	 btVector3 btGlobalImpulse(globalImpulse.x,
	 globalImpulse.y,
	 globalImpulse.z;

	 pO->getRigidBody()->applyCentralImpulse(btGlobalImpulse);

	 _world->addRigidBody(pO->getRigidBody());

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
	 */}

void PhysicsController::createGround(MAOPositionator3D& refGround,
		Ogre::Vector3& gravity) {
	if (!isActive()) {
		throw "Physics Controller is not active!";
	}

	_gravity = gravity;

	// Define a floor plane mesh
	Ogre::Plane plane;
	plane.normal = Ogre::Vector3(0, 0, 1);
	plane.d = 0;
	Ogre::MeshManager::getSingleton().createPlane("groundPlane",
			Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, plane,
			200000, 200000, 20, 20, true, 1, 9000, 9000, Ogre::Vector3::UNIT_Z);

	// Create an entity (the floor)
	Ogre::Entity* ent = Ogre::Root::getSingleton().getSceneManager(
			"SceneManager")->createEntity("ground", "groundPlane");

	//ent->setMaterialName("Examples/BumpyMetal");

	_ground->setGlobalReference(refGround);
	_ground->setEntity(ent);
	_ground->setCollisionShape(
			new OgreBulletCollisions::StaticPlaneCollisionShape(
					Ogre::Vector3(0, 0, 1), 0)); // (normal vector, distance)
	_ground->setRigidBody(
			new OgreBulletDynamics::RigidBody("groundPlane", _colWorld));
	_ground->getRigidBody()->setStaticShape(_ground->getCollisionShape(), 0.1,
			0.8); // (shape, restitution, friction)

	_listPhysicObjects.push_back(_ground);
}

bool PhysicsController::collision(MAORenderable3D* m1, MAORenderable3D* m2) {
	bool collision = false;

	// TODO

	return collision;
}

void PhysicsController::initPhysics() {
	if (isActive()) {
		throw "Physics Controller is already active!";
	}
	_active = true;

	_colWorld = new OgreBulletDynamics::DynamicsWorld(
			Ogre::Root::getSingleton().getSceneManager("SceneManager"), _aabox,
			_gravity);
	_debugDrawer = new OgreBulletCollisions::DebugDrawer();
	_debugDrawer->setDrawWireframe(true);

	_colWorld->setDebugDrawer(_debugDrawer);
	_colWorld->setShowDebugShapes(true);

	Ogre::Root::getSingleton().getSceneManager("SceneManager")->getRootSceneNode()->createChildSceneNode(
			"debugDrawer", Ogre::Vector3::ZERO)->attachObject(
			static_cast<Ogre::SimpleRenderable*>(_debugDrawer));

}

PhysicsController::~PhysicsController() {
// Im a singleton.. do not need it :)
}
