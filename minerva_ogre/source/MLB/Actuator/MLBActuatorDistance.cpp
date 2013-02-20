/*
 * MLBActuatorDistance.cpp
 *
 *  Created on: 26/02/2011
 *      Author: cesar
 */

#include <MLB/Actuator/MLBActuatorDistance.h>

MLBActuatorDistance::MLBActuatorDistance(const std::string& name,
		MAOPositionator3D& parent, MAOPositionator3D& mao,
		MAOProperty& property) :
	MLBActuator(name, parent) {

	_property = &property;

	if (_property->getType() != MAOPROPERTY_INT && _property->getType()
			!= MAOPROPERTY_FLOAT && _property->getType() != MAOPROPERTY_STRING)
		throw "Can not apply Boolean or Pose properties to MLB Actuator Distance: "
				+ name;

	_parent = &parent;
	_mao = &mao;
	_mlbType = T_MLBACTUATORDISTANCE;
}

void MLBActuatorDistance::specificActuate() {
	if (((MAOPositionator3D*) _parent)->isPositioned()
			&& ((MAOPositionator3D*) _mao)->isPositioned()) {
		float dist = distance();

		switch (_property->getType()) {
		case MAOPROPERTY_INT:
			_property->setValue<int> ((int)dist);
			break;
		case MAOPROPERTY_FLOAT:
			_property->setValue<float> (dist);
			break;
		case MAOPROPERTY_STRING:
			_property->setValue<std::string> (MAOProperty("",
					MAOPROPERTY_FLOAT, dist).toString());
			break;
		}
	}
}

float MLBActuatorDistance::distance() {
	float dist;

	dist = sqrt(  pow(((MAOPositionator3D*) _parent)->getPosMatrix().at<float> (3, 0) - _mao->getPosMatrix().at<float> (3, 0), 2)
		    + pow(((MAOPositionator3D*) _parent)->getPosMatrix().at<float> (3, 1) - _mao->getPosMatrix().at<float> (3, 1), 2)
		    + pow(((MAOPositionator3D*) _parent)->getPosMatrix().at<float> (3, 2) - _mao->getPosMatrix().at<float> (3, 2), 2));

	return dist;
}

MLBActuatorDistance::~MLBActuatorDistance() {

}
