/*
 * MAOMarksGroup.cpp
 *
 *  Created on: 21/02/2011
 *      Author: cesar
 */

#include <MAO/MAOMarksGroup.h>

MAOMarksGroup::MAOMarksGroup(const std::string& name) :
		MAOPositionator3D(name) {
	_type = T_MAOMARKSGROUP;

	Ogre::Root::getSingleton().getSceneManager("SceneManager")->getRootSceneNode()->addChild(
			_node);
}

void MAOMarksGroup::addMarktoGroup(MAOMark& mark) {
	/* Check if is already in the vector */
	std::list<MAOMark*>::iterator ptrMark;
	for (ptrMark = _listMAOMark.begin(); ptrMark != _listMAOMark.end();
			++ptrMark) {
		MAOMark* m = *ptrMark;
		if (m->getName() == mark.getName())
			throw "Mark already in MarksGroup: " + mark.getName();
	}

	_listMAOMark.push_back(&mark);
}

void MAOMarksGroup::updatePosition() {
	bool positioned = false;

	Ogre::Vector3 finalPos;
	Ogre::Quaternion finalRot;

	int nMarks = 0;

	std::list<MAOMark*>::iterator ptrMark;
	for (ptrMark = _listMAOMark.begin(); ptrMark != _listMAOMark.end();
			++ptrMark) {
		MAOMark* m = *ptrMark;
		if(m->isPositioned()){
			positioned = true;
			nMarks++;
			finalPos += m->getSceneNode().getPosition();
			finalRot = m->getSceneNode().getOrientation();
		}
	}
	setPositioned(positioned);

	finalPos /= nMarks;

	_node->setPosition(finalPos);
	_node->setOrientation(finalRot);
}

MAOMarksGroup::~MAOMarksGroup() {
}
