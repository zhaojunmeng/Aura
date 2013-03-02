/*
 * MAORenderable3DModel.h
 *
 *  Created on: 04/02/2013
 *      Author: cesar
 */

#ifndef MAORENDERABLE3DMODEL_H_
#define MAORENDERABLE3DMODEL_H_

#include <MAO/MAORenderable3D.h>

enum AnimType {SIMPLE, LOOP, PINGPONG};


class MAORenderable3DModel: public MAORenderable3D {
	boost::filesystem::path _file;
public:

	MAORenderable3DModel(const std::string& name, const boost::filesystem::path& file, float scale = 1.0f);
	virtual ~MAORenderable3DModel();

	void generateCollisionShape(int type);

	btCollisionShape* getCollisionShape();
	void generateBoxShape();
	void generateConvexTriangleMeshShape();
	void generateCylinderShape();
	void generateSphereShape();

	void playAnim(int animType = SIMPLE);
	void stopAnim();
	void pauseAnim();
};

#endif /* MAORENDERABLE3DMODEL_H_ */
