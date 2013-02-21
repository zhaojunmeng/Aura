/*
 * MAOMarksGroup.h
 *
 *  Created on: 21/02/2011
 *      Author: cesar
 */

#ifndef MAOMARKSGROUP_H_
#define MAOMARKSGROUP_H_

#include <string>
#include <MAO/MAOMark.h>

class MAOMarksGroup: public MAOPositionator3D {
public:
	MAOMarksGroup(const std::string& name);
	virtual ~MAOMarksGroup();
	void addMarktoGroup(MAOMark& mark);
	Ogre::Matrix4& getPosMatrix();
	void checkIfPositioned();

private:
	std::vector<MAOMark*> _vectorMAOMark;
};

#endif /* MAOMARKSGROUP_H_ */
