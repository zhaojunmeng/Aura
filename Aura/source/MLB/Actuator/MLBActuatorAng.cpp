/*
 * MLBActuatorAng.cpp
 *
 *  Created on: 28/02/2011
 *      Author: cesar
 */

#include <MLB/Actuator/MLBActuatorAng.h>

MLBActuatorAng::MLBActuatorAng(const std::string& name,
		MAOPositionator3D& parent, MAOProperty& property, int angAxis) :
	MLBActuator(name, parent) {
	if (property.getType() != MAOPROPERTY_INT && property.getType()!=MAOPROPERTY_FLOAT && property.getType()!=MAOPROPERTY_STRING)
		throw "Properties Boolean or Pose are not applicable to MLB Actuator Angle: "
				+ name;

	_property = &property;
	_angAxis = angAxis;
	_mlbType = T_MLBACTUATORANG;
}

void MLBActuatorAng::specificActuate() {
// TODO

/*
	cv::Mat v1(1, 3, CV_32F);
	cv::Mat v2(1, 3, CV_32F);

	float ang;

	if(!((MAOPositionator3D*)_parent)->isPositioned()){
	  ang = -1;
	}else{
	  switch (_angAxis) {
	  case ANG_X:
	    v1.at<float> (0, 0) = 1.;
	    v1.at<float> (0, 1) = 0.;
	    v1.at<float> (0, 2) = 0.;

	    v2.at<float> (0, 0) = ((MAOPositionator3D*) _parent)->getPosMatrix().at<float> (0,0);
	    v2.at<float> (0, 1) = ((MAOPositionator3D*) _parent)->getPosMatrix().at<float> (0,1);
	    v2.at<float> (0, 2) = ((MAOPositionator3D*) _parent)->getPosMatrix().at<float> (0,2);

	    break;
	  case ANG_Y:
	    v1.at<float> (0, 0) = 0.;
	    v1.at<float> (0, 1) = 1.;
	    v1.at<float> (0, 2) = 0.;

	    v2.at<float> (0, 0)
	      = ((MAOPositionator3D*) _parent)->getPosMatrix().at<float> (1,
									  0);
	    v2.at<float> (0, 1)
	      = ((MAOPositionator3D*) _parent)->getPosMatrix().at<float> (1,
									  1);
	    v2.at<float> (0, 2)
	      = ((MAOPositionator3D*) _parent)->getPosMatrix().at<float> (1,
									  2);
	    break;
	  case ANG_Z:
	    v1.at<float> (0, 0) = 0.;
	    v1.at<float> (0, 1) = 0.;
	    v1.at<float> (0, 2) = 1.;

	    v2.at<float> (0, 0)
	      = ((MAOPositionator3D*) _parent)->getPosMatrix().at<float> (2,
									  0);
	    v2.at<float> (0, 1)
	      = ((MAOPositionator3D*) _parent)->getPosMatrix().at<float> (2,
									  1);
	    v2.at<float> (0, 2)
	      = ((MAOPositionator3D*) _parent)->getPosMatrix().at<float> (2,
									  2);
	    break;
	  default:
	    break;
	  }

	  ang = angle(v1, v2);
	}

	switch (_property->getType()) {
	case MAOPROPERTY_INT:
	  _property->setValue<int> ((int)ang);
	  break;
	case MAOPROPERTY_FLOAT:
	  _property->setValue<float> (ang);
	  break;

	case MAOPROPERTY_STRING:
	  _property->setValue<std::string> (MAOProperty("",MAOPROPERTY_FLOAT,ang).toString());
	  break;

	}
*/
}

float MLBActuatorAng::module(Ogre::Matrix4 v) {
	float mod;

	// TOD
	//mod = sqrt(pow(v.at<float> (0, 0), 2) + pow(v.at<float> (0, 1), 2) + pow(
			//v.at<float> (0, 2), 2));

	return mod;
}

float MLBActuatorAng::angle(Ogre::Matrix4 v1, Ogre::Matrix4 v2) {
	float ang;

	//ang = acos((v1.at<float> (0, 0) * v2.at<float> (0, 0) + v1.at<float> (0, 1)
		//	* v2.at<float> (0, 1) + v1.at<float> (0, 2) * v2.at<float> (0, 2))
	//		/ (module(v1) * module(v2)));

	return ang;
}

MLBActuatorAng::~MLBActuatorAng() {
}
