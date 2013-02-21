/*
 * MAORenderable3DModel.cpp
 *
 *  Created on: 04/02/2013
 *      Author: cesar
 */

#include <MAO/MAORenderable3DModel.h>

using namespace std;

MAORenderable3DModel::MAORenderable3DModel(const std::string& name,
		const boost::filesystem::path& file, float size) :
		MAORenderable3D(name, size), _file(file) {

	_type = T_MAORENDERABLE3DMODEL;
}

btCollisionShape* MAORenderable3DModel::getCollisionShape() {
	return _collisionShape;
}

void MAORenderable3DModel::generateCollisionShape(int type) {
	if (_collisionShape == NULL) {
		switch (type) {
		case MAO_BOX_SHAPE:
			generateBoxShape();
			setBoxShape(getCollisionShape());
			break;
		case MAO_SPHERE_SHAPE:
			generateSphereShape();
			setSphereShape(getCollisionShape());
			break;
		case MAO_CYLINDER_SHAPE:
			generateCylinderShape();
			setCylinderShape(getCollisionShape());
			break;

			break;
		case MAO_CONVEXTRIANGLEMESH_SHAPE:
			generateConvexTriangleMeshShape();
			setConvexTriangleMeshShape(getCollisionShape());
			break;

			break;
		default:
			Logger::getInstance()->warning(
					"MAO has not defined a Collision Shape type: " + getName());
			break;
		}
	}
}

void MAORenderable3DModel::generateBoxShape() {
	//For box shape ;)
	float x[] = { 100, -100 };
	float y[] = { 100, -100 };
	float z[] = { 100, -100 };

	vector<MAOVector3>::iterator ptr;
	for (ptr = _meshes.back().vertex.begin(); ptr != _meshes.back().vertex.end(); ++ptr) {
		float& vx = ptr->x;
		float& vy = ptr->y;
		float& vz = ptr->z;

		//Box Shapes
		if (vx < x[0])
			x[0] = vx;
		else if (vx > x[1])
			x[1] = vx;

		if (vy < y[0])
			y[0] = vy;
		else if (vy > y[1])
			y[1] = vy;

		if (vz < z[0])
			z[0] = vz;
		else if (vz > z[1])
			z[1] = vz;

		_collisionShape = new btBoxShape(
				btVector3((x[1] - x[0]) / 2, (y[1] - y[0]) / 2,
						(z[1] - z[0]) / 2));
	}
}
void MAORenderable3DModel::generateConvexTriangleMeshShape() {
	btConvexHullShape* ch = new btConvexHullShape();
	ch->setMargin(btScalar(0.005f));

	vector<MAOVector3>::iterator ptr;
	for (ptr = _meshes.back().vertex.begin(); ptr != _meshes.back().vertex.end(); ++ptr) {
		((btConvexHullShape*) ch)->addPoint(btVector3(ptr->x, ptr->y, ptr->z));
	}

	_collisionShape = ch;

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

void MAORenderable3DModel::_drawMesh(const MAOMesh& mesh) {
/*
	glEnable(GL_TEXTURE_2D);

		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

		if (mesh.materialId != -1) {
			glBindTexture(GL_TEXTURE_2D, _materials[mesh.materialId].texId);
		} else {
			glColor3f(1.0, 0.0, 0.0);
		}
		glPolygonMode(GL_FRONT, GL_FILL);

		_drawMeshNoTexture(mesh);

		glDisable(GL_TEXTURE_2D);
*/
}

void MAORenderable3DModel::_drawMeshNoTexture(const MAOMesh& mesh) {
/*	glPushMatrix();

	//Refresh anim!
	if (_anim.frames > 0) {
		glMultMatrixf(mesh.animMatrix[_anim.currentFrame]);

		if (_anim.playing) {
			_anim.currentFrame += _anim.dir;
			if (_anim.currentFrame == (_anim.frames - 1)) {
				switch (_anim.type) {
				case SIMPLE:
					stopAnim();
					break;
				case LOOP:
					_anim.currentFrame = 0;
					break;
				case PINGPONG:
					_anim.dir *= -1;
					break;
				}
			}

			//For Ping-Pong mode!
			if (_anim.currentFrame == -1) {
				_anim.dir *= -1;
			}
		}
	}

	glCallList (mesh.idListMesh);
	glPopMatrix();*/
}


void MAORenderable3DModel::_drawMAO() {
	list<MAOMesh>::iterator meshPtr;
	for(meshPtr = _meshes.begin(); meshPtr != _meshes.end(); ++meshPtr){
		_drawMesh(*meshPtr);
	}

}

void MAORenderable3DModel::_drawMAONoTexture() {
	list<MAOMesh>::iterator meshPtr;
		for(meshPtr = _meshes.begin(); meshPtr != _meshes.end(); ++meshPtr){
			_drawMeshNoTexture(*meshPtr);
		}
}

void MAORenderable3DModel::playAnim(int animType) {
	if (!_anim.playing) {
		_anim.playing = true;
	}
}

void MAORenderable3DModel::pauseAnim() {
	if (_anim.playing) {
		_anim.playing = false;
	}
}

void MAORenderable3DModel::stopAnim() {
	if (_anim.playing) {
		_anim.playing = false;
	}
	_anim.currentFrame = 0;
	_anim.dir = 1;
}

MAORenderable3DModel::~MAORenderable3DModel() {

}

