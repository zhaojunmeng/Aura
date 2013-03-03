/*
 * MAORenderable3D.cpp
 *
 *  Created on: 21/02/2011
 *      Author: cesar
 */

#include <MAO/MAORenderable3D.h>

MAORenderable3D::MAORenderable3D(const std::string& name, const float& size) :
		MAOPositionator3D(name),_globalReference(NULL), _active(true), _physic(false) {

	addPropertyFloat("size", size);
	addPropertyBoolean("visible", false); //At first, is a MAO Class
	addPropertyPose("relative");
	addPropertyFloat("mass", 0.f);

	setVisible(false);
	setSize(size);

	_type = T_MAORENDERABLE3D;
}

MAORenderable3D::MAORenderable3D(const MAORenderable3D& o) :
		MAOPositionator3D(o) {
	_globalReference = o._globalReference;
	_type = o._type;
	_physic = o._physic;
	_active = o._active;
}

void MAORenderable3D::update(){
	if(_globalReference != NULL){
		setActive(_globalReference->isPositioned());
	}else{
		setActive(false);
	}
}

OgreBulletDynamics::RigidBody* MAORenderable3D::getRigidBody(){
	return _rigidBody;
}

OgreBulletCollisions::CollisionShape* MAORenderable3D::getCollisionShape(){
	return _colShape;
}


bool MAORenderable3D::isPhysic() {
	return _physic;
}

void MAORenderable3D::setPhysic(bool physic) {
	_physic = physic;
}

int MAORenderable3D::getTimeToExpire() {
	return _dynamicState.timeToExpire;
}

void MAORenderable3D::decrementTimeToExpire() {
	if (_dynamicState.timeToExpire > 0)
		_dynamicState.timeToExpire--;
}

void MAORenderable3D::setTimeToExpire(int timeToExpire) {
	_dynamicState.timeToExpire = _dynamicState.timeToExpire;
}

bool MAORenderable3D::isActive() {
	return _active;
}

void MAORenderable3D::setActive(bool active) {
	_active = active;
	setVisible(active);
}

void MAORenderable3D::setGlobalReference(MAOPositionator3D& globalReference) {
	getProperty("visible").setValue<bool>(true);
	_globalReference = &globalReference;
	Ogre::Root::getSingleton().getSceneManager("SceneManager")->getSceneNode(
			_globalReference->getName())->addChild(_node);
}

MAOPositionator3D* MAORenderable3D::getGlobalReference() {
	return _globalReference;
}

void MAORenderable3D::setMass(float mass) {
	getProperty("mass").setValue<float>(mass);
}

float MAORenderable3D::getMass() {
	return getProperty("mass").getValue<float>();
}



bool MAORenderable3D::isVisible() {
	return getProperty("visible").getValue<bool>();
}

void MAORenderable3D::setVisible(bool visible) {
	getProperty("visible").setValue<bool>(visible);
	_node->setVisible(visible);
}

void MAORenderable3D::setSize(float size) {
	_node->setScale(size, size, size);
	getProperty("size").setValue<float>(size);
}
float MAORenderable3D::getSize() {
	return getProperty("size").getValue<float>();
}

void MAORenderable3D::setRigidBody(OgreBulletDynamics::RigidBody* rigidBody){
	if(_rigidBody) delete _rigidBody;
	_rigidBody =  rigidBody;
}

void MAORenderable3D::setCollisionShape(OgreBulletCollisions::CollisionShape* colShape){
	if(_colShape) delete _colShape;
	_colShape = colShape;
}


MAORenderable3D::~MAORenderable3D() {
}
