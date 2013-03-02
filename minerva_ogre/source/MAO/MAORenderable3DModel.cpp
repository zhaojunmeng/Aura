/*
 *  * MAORenderable3DModel.cpp
 *
 *  Created on: 04/02/2013
 *      Author: cesar
 */

#include <MAO/MAORenderable3DModel.h>

using namespace std;

MAORenderable3DModel::MAORenderable3DModel(const std::string& name,
		const boost::filesystem::path& file, float size) :
		MAORenderable3D(name, size), _file(file) {

	_ent = Ogre::Root::getSingleton().getSceneManager("SceneManager")->createEntity("Sinbad","Sinbad.mesh");
	_node->attachObject(_ent);

	_type = T_MAORENDERABLE3DMODEL;
}

btCollisionShape* MAORenderable3DModel::getCollisionShape() {
	return _collisionShape;
}

void MAORenderable3DModel::generateCollisionShape(int type) {

}

void MAORenderable3DModel::generateBoxShape() {

}
void MAORenderable3DModel::generateConvexTriangleMeshShape() {

}

void MAORenderable3DModel::generateCylinderShape() {
	Logger::getInstance()->error(
			"Generating Cylinder Shapes for Models is not implemented yet!!");
	throw "Generating Cylinder Shapes from Models is not implemented yet!!";

}
void MAORenderable3DModel::generateSphereShape() {
	Logger::getInstance()->error(
			"Generating Sphere Shapes from Models is not implemented yet!!");
	throw "Generating Sphere Shapes from Models is not implemented yet!!";
}




void MAORenderable3DModel::playAnim(int animType) {

}

void MAORenderable3DModel::pauseAnim() {

}

void MAORenderable3DModel::stopAnim() {

}

MAORenderable3DModel::~MAORenderable3DModel() {

}

