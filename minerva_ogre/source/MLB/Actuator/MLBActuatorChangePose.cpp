/*
 * MLBActuatorChangePose.cpp
 *
 *  Created on: 25/02/2011
 *      Author: cesar
 */

#include <MLB/Actuator/MLBActuatorChangePose.h>

/* Rotation angles in degrees ;)*/
MLBActuatorChangePose::MLBActuatorChangePose(const std::string& name,
		MAORenderable3D& parent, int locType, float locX, float locY,
		float locZ, int rotType, float rotX, float rotY, float rotZ) :
	MLBActuator(name, parent) {
	_locType = locType;
	_locX = locX;
	_locY = locY;
	_locZ = locZ;

	_rotType = rotType;
	_rotX = (float) (rotX * DEGREES);
	_rotY = (float) (rotY * DEGREES);
	_rotZ = (float) (rotZ * DEGREES);
	_mlbType = T_MLBACTUATORCHANGEPOSE;
}

void MLBActuatorChangePose::specificActuate() {
// TODO
	/*
	if (((MAORenderable3D*) _parent)->getMass() != 0) {
		Logger::getInstance()->error(
				"Can not apply ChangePose Actuator to Dynamic Objects!: "
						+ getName());
		return;
	}

	if (((MAORenderable3D*) _parent)->isPositioned()) {

		cv::Mat locMat(4, 4, CV_32F);
		cv::Mat rotMat(4, 4, CV_32F);
		cv::Mat res(4, 4, CV_32F);

		//Loc Matrix
		locMat.at<float> (0, 0) = 1.;
		locMat.at<float> (0, 1) = 0.;
		locMat.at<float> (0, 2) = 0.;
		locMat.at<float> (0, 3) = 0.;
		locMat.at<float> (1, 0) = 0.;
		locMat.at<float> (1, 1) = 1.;
		locMat.at<float> (1, 2) = 0.;
		locMat.at<float> (1, 3) = 0.;
		locMat.at<float> (2, 0) = 0.;
		locMat.at<float> (2, 1) = 0.;
		locMat.at<float> (2, 2) = 1.;
		locMat.at<float> (2, 3) = 0.;
		locMat.at<float> (3, 0) = _locX;
		locMat.at<float> (3, 1) = _locY;
		locMat.at<float> (3, 2) = _locZ;
		locMat.at<float> (3, 3) = 1.;

		//Rot Matrix
		rotMat.at<float> (0, 0) = cos(_rotY) * cos(_rotZ);
		rotMat.at<float> (0, 1) = sin(_rotX) * sin(_rotY) * cos(_rotZ) + cos(
				_rotX) * sin(_rotZ);
		rotMat.at<float> (0, 2) = -cos(_rotX) * sin(_rotY) * cos(_rotZ) + sin(
				_rotX) * sin(_rotZ);
		rotMat.at<float> (0, 3) = 0.;
		rotMat.at<float> (1, 0) = -cos(_rotY) * sin(_rotZ);
		rotMat.at<float> (1, 1) = -sin(_rotX) * sin(_rotY) * sin(_rotZ) + cos(
				_rotX) * cos(_rotZ);
		rotMat.at<float> (1, 2) = cos(_rotX) * sin(_rotY) * sin(_rotZ) + sin(
				_rotX) * cos(_rotZ);
		rotMat.at<float> (1, 3) = 0.;
		rotMat.at<float> (2, 0) = sin(_rotY);
		rotMat.at<float> (2, 1) = -sin(_rotX) * cos(_rotY);
		rotMat.at<float> (2, 2) = cos(_rotX) * cos(_rotY);
		rotMat.at<float> (2, 3) = 0.;
		rotMat.at<float> (3, 0) = 0.;
		rotMat.at<float> (3, 1) = 0.;
		rotMat.at<float> (3, 2) = 0.;
		rotMat.at<float> (3, 3) = 1.;

		//Res Matrix (Identity Matrix)
		res.at<float> (0, 0) = 1.;
		res.at<float> (0, 1) = 0.;
		res.at<float> (0, 2) = 0.;
		res.at<float> (0, 3) = 0.;
		res.at<float> (1, 0) = 0.;
		res.at<float> (1, 1) = 1.;
		res.at<float> (1, 2) = 0.;
		res.at<float> (1, 3) = 0.;
		res.at<float> (2, 0) = 0.;
		res.at<float> (2, 1) = 0.;
		res.at<float> (2, 2) = 1.;
		res.at<float> (2, 3) = 0.;
		res.at<float> (3, 0) = 0.;
		res.at<float> (3, 1) = 0.;
		res.at<float> (3, 2) = 0.;
		res.at<float> (3, 3) = 1.;

		// RotL * LocL * RenderablePosM * LocG * RotG * GlobalReferencePosM = res
		if (_rotType == CHANGEPOSE_GLOBAL)
			res = rotMat * res;
		if (_locType == CHANGEPOSE_GLOBAL)
			res = locMat * res;

		res = ((MAORenderable3D*) _parent)->getRelativeMatrix() * res;

		if (_locType == CHANGEPOSE_LOCAL)
			res = locMat * res;
		if (_rotType == CHANGEPOSE_LOCAL)
			res = rotMat * res;

		((MAORenderable3D*) _parent)->setRelativeMatrix(res);
	}
*/}

/* Python functions! */
int MLBActuatorChangePose::mPyGetLocType() {
	return _locType;
}
void MLBActuatorChangePose::mPySetLocType(int locType) {
	_locType = locType;
}
int MLBActuatorChangePose::mPyGetRotType() {
	return _rotType;
}
void MLBActuatorChangePose::mPySetRotType(int rotType) {
	_rotType = rotType;
}

VectorFloat MLBActuatorChangePose::mPyGetLoc() {
	VectorFloat v;
	v.push_back(_locX);
	v.push_back(_locY);
	v.push_back(_locZ);
	return v;
}
void MLBActuatorChangePose::mPySetLoc(VectorFloat loc) {
	if(loc.size()!=3){
		Logger::getInstance()->error("Loc vector size should be 3 in MLB Actuator Change Pose: "+getName());
		throw "Loc vector size should be 3 in MLB Actuator Change Pose: "+getName();
	}else{
		_locX = loc.at(0);
		_locY = loc.at(1);
		_locZ = loc.at(2);
	}
}
VectorFloat MLBActuatorChangePose::mPyGetRot() {
	VectorFloat v;
		v.push_back(_rotX);
		v.push_back(_rotY);
		v.push_back(_rotZ);
		return v;

}
void MLBActuatorChangePose::mPySetRot(VectorFloat rot) {
	if(rot.size()!=3){
			Logger::getInstance()->error("Rotvector size should be 3 in MLB Actuator Change Pose: "+getName());
			throw "Rot vector size should be 3 in MLB Actuator Change Pose: "+getName();
		}else{
			_rotX = rot.at(0);
			_rotY = rot.at(1);
			_rotZ = rot.at(2);
		}
}

MLBActuatorChangePose::~MLBActuatorChangePose() {
}

