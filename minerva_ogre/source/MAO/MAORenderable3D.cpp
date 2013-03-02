/*
 * MAORenderable3D.cpp
 *
 *  Created on: 21/02/2011
 *      Author: cesar
 */

#include <MAO/MAORenderable3D.h>

MAORenderable3D::MAORenderable3D(const std::string& name, const float& size) :
		MAOPositionator3D(name) {

	addPropertyFloat("size", size);
	addPropertyBoolean("visible", false); //At first, is a MAO Class
	addPropertyPose("relative");
	addPropertyFloat("mass", 0.f);

	setVisible(false);
	setSize(size);

	_type = T_MAORENDERABLE3D;
	_globalReference = NULL;
	_collisionShape = NULL;
	_collisionShapeType = -1;

	_physic = false;
	_active = true;
	_timeToExpire = 0;
}

MAORenderable3D::MAORenderable3D(const MAORenderable3D& o) :
		MAOPositionator3D(o) {
	_globalReference = o._globalReference;
	_type = o._type;
	_collisionShape = o._collisionShape;
	_collisionShapeType = o._collisionShapeType;
	_physic = o._physic;
	_active = o._active;
	_timeToExpire = 0;
}

void MAORenderable3D::update(){
	if(_globalReference != NULL){
		setActive(_globalReference->isPositioned());
	}else{
		setActive(false);
	}
}

bool MAORenderable3D::isPhysic() {
	return _physic;
}

void MAORenderable3D::setPhysic(bool physic) {
	_physic = physic;
}

int MAORenderable3D::getTimeToExpire() {
	return _timeToExpire;
}

void MAORenderable3D::decrementTimeToExpire() {
	if (_timeToExpire > 0)
		_timeToExpire--;
}

void MAORenderable3D::setTimeToExpire(int timeToExpire) {
	_timeToExpire = timeToExpire;
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


btCollisionShape* MAORenderable3D::getCollisionShape() {
	return _collisionShape;
}

void MAORenderable3D::setBoxShape(btCollisionShape* b) {
	_collisionShape = b;
	_collisionShapeType = MAO_BOX_SHAPE;
}

void MAORenderable3D::setSphereShape(btCollisionShape* b) {
	_collisionShape = b;
	_collisionShapeType = MAO_SPHERE_SHAPE;
}
void MAORenderable3D::setCylinderShape(btCollisionShape* b) {
	_collisionShape = b;
	_collisionShapeType = MAO_CYLINDER_SHAPE;
}

void MAORenderable3D::setConvexTriangleMeshShape(btCollisionShape* b) {
	_collisionShape = b;
	_collisionShapeType = MAO_CONVEXTRIANGLEMESH_SHAPE;

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

void MAORenderable3D::setCollisionShapeType(int collisionShapeType) {
	_collisionShapeType = collisionShapeType;
	generateCollisionShape(_collisionShapeType);
}

void MAORenderable3D::setCollisionShapeType(std::string sCollisionShapeType) {
	if (sCollisionShapeType == "BOX") {
		_collisionShapeType = MAO_BOX_SHAPE;
	} else if (sCollisionShapeType == "SPHERE") {
		_collisionShapeType = MAO_SPHERE_SHAPE;
	} else if (sCollisionShapeType == "CYLINDER") {
		_collisionShapeType = MAO_CYLINDER_SHAPE;
	} else if (sCollisionShapeType == "TRIANGLE_MESH") {
		_collisionShapeType = MAO_CONVEXTRIANGLEMESH_SHAPE;
	} else {
		throw "Invalid Collision Shape type for MAO: " + getName();
		return;
	}
	generateCollisionShape(_collisionShapeType);

}

int MAORenderable3D::getCollisionShapeType() {
	return _collisionShapeType;
}

MAORenderable3D::~MAORenderable3D() {
}
