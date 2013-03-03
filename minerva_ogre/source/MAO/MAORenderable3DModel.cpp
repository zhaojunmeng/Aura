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


void MAORenderable3DModel::playAnim(int animType) {

}

void MAORenderable3DModel::pauseAnim() {

}

void MAORenderable3DModel::stopAnim() {

}

MAORenderable3DModel::~MAORenderable3DModel() {

}

