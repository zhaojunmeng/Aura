/*
 * MAOPositionable.h
 *
 *  Created on: 21/02/2011
 *      Author: cesar
 */

#ifndef MAOPOSITIONATOR3D_H_
#define MAOPOSITIONATOR3D_H_

#include <string>
#include <iostream>

#include <MAO/MAO.h>

class MAOPositionator3D: public MAO {
protected:
	bool _positioned;


public:
	MAOPositionator3D(const std::string& name);
	MAOPositionator3D(const MAOPositionator3D& o);
	virtual ~MAOPositionator3D();

	void setNodeMatrix(Ogre::Matrix4& posMatrix);

	Ogre::SceneNode& getSceneNode(){ return *_node;}

	/* Getters and Setters */
	bool isPositioned();
	void setPositioned(bool positioned);

	Ogre::SceneNode* _node;

};

#endif /* MAOPositionator3D_H_ */
