/*
 * MLBActuatorRelativePose.cpp
 *
 *  Created on: 02/03/2011
 *      Author: cesar
 */

#include <MLB/Actuator/MLBActuatorRelativePose.h>

MLBActuatorRelativePose::MLBActuatorRelativePose(const std::string& name,
		MAOPositionator3D& parent, MAOPositionator3D& ref,
		MAOProperty& property, bool inverse) :
	MLBActuator(name, parent) {
	if (property.getType() != MAOPROPERTY_POSE)
		throw "MLB Actuator Relative Pose is just applicable to Pose Properties";

	_inverse = inverse;
	_ref = &ref;
	_property = &property;
	_mlbType = T_MLBACTUATORRELATIVEPOSE;
}

void MLBActuatorRelativePose::specificActuate() {
	cv::Mat r;

	if (((MAOPositionator3D*) _parent)->isPositioned()
			&& ((MAOPositionator3D*) _ref)->isPositioned()) {

		//TODO Maybe bug here! (
		r = ((MAOPositionator3D*) _parent)->getPosMatrix()
				* ((MAOPositionator3D*) _ref)->getPosMatrix().inv();

		if (_inverse) {
			_property->setValue<cv::Mat> (r.inv());
		} else {
			_property->setValue<cv::Mat> (r);
		}
	}
}

bool MLBActuatorRelativePose::mPyGetInverse() {
	return _inverse;
}
void MLBActuatorRelativePose::mPySetInverse(bool inverse) {
	_inverse = inverse;
}

MLBActuatorRelativePose::~MLBActuatorRelativePose() {

}
