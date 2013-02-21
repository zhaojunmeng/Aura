/*
 * MAOMarksGroup.cpp
 *
 *  Created on: 21/02/2011
 *      Author: cesar
 */

#include <MAO/MAOMarksGroup.h>

MAOMarksGroup::MAOMarksGroup(const std::string& name): MAOPositionator3D(name) {
  _vectorMAOMark = std::vector<MAOMark*>();
  _type = T_MAOMARKSGROUP;
}

void MAOMarksGroup::addMarktoGroup(MAOMark& mark){
	/* Check if is already in the vector */
  	for(unsigned int i=0;i<_vectorMAOMark.size();i++){
		MAOMark* m = _vectorMAOMark.at(i);
		if(m->getName()==mark.getName())
			throw "Mark already in MarksGroup: "+mark.getName();
	}

	_vectorMAOMark.push_back(&mark);
}

Ogre::Matrix4& MAOMarksGroup::getPosMatrix(){
// TODO
	//int nDetected = 0;
	//cv::Mat temp = cv::Mat(4,4,CV_32F,cv::Scalar(0));

	//for(unsigned int i=0;i<_vectorMAOMark.size();i++){
		//if(_vectorMAOMark.at(i)->isPositioned()){
		  //nDetected++;
		  //temp = temp + _vectorMAOMark.at(i)->getPosMatrix();
		  //setNodeMatrix(_vectorMAOMark.at(i)->getPosMatrix());
		  //break;
	//	}
	//}

	//if(nDetected>0){
	//	temp = temp / nDetected;
	//setPosMatrix(temp);
	//}


	/*for(unsigned int i=0;i<_vectorMAOMark.size();i++){
		if(_vectorMAOMark.at(i)->isPositioned()){
			nDetected++;
			temp = temp + _vectorMAOMark.at(i)->getPosMatrix();
		}
	}

	if(nDetected>0){
		temp = temp / nDetected;
		setPosMatrix(temp);
	}*/

	//return _posMatrix;
}

void MAOMarksGroup::checkIfPositioned(){
  bool positioned = false;
  for(unsigned int i=0;i<_vectorMAOMark.size() && !positioned;i++){
    positioned|=_vectorMAOMark.at(i)->isPositioned();
  }
  setPositioned(positioned);
}

MAOMarksGroup::~MAOMarksGroup() {
}
