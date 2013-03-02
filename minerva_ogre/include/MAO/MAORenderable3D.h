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
#include <GL/gl.h>
#include <btBulletCollisionCommon.h>
#include <BulletCollision/CollisionShapes/btScaledBvhTriangleMeshShape.h>
#include <MAO/MAOPositionator3D.h>
#include <Kernel/Logger.h>
#include <list>

class MAORenderable3D: public MAOPositionator3D {
protected:

	Ogre::Entity* _ent;

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

	btCollisionShape* getCollisionShape();
	int getCollisionShapeType();

	void setCollisionShapeType(int collisionShapeType);
	void setCollisionShapeType(std::string sCollisionShapeType);

	virtual void generateCollisionShape(int type)=0;

protected:


	void setBoxShape(btCollisionShape* b); //From an Instantiated Box Shape
	void setSphereShape(btCollisionShape* b);
	void setCylinderShape(btCollisionShape* b);
	void setConvexTriangleMeshShape(btCollisionShape* b);

	MAOPositionator3D* _globalReference;
	btCollisionShape* _collisionShape;
	int _collisionShapeType;
	bool _physic;
	bool _active;
	int _timeToExpire; //For instantiated MAO's
};

#endif /* MAORENDERABLE_H_ */
