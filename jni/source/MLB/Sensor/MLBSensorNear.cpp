/*
 * MLBSensorNear.cpp
 *
 *  Created on: 22/02/2011
 *      Author: cesar
 */

#include <MLB/Sensor/MLBSensorNear.h>

MLBSensorNear::MLBSensorNear(const std::string& name, MAOPositionator3D& parent,
		const std::string& property, float minDistance) :
		MLBSensor(name, parent) {
	_minDistance = minDistance;
	_property = property;
	_mlbType = T_MLBSENSORNEAR;
}

void MLBSensorNear::evaluate() {
	if (((MAOPositionator3D*) _parent)->isPositioned()) {

		std::vector<MAOPositionator3D*>& vectorMAOPositionator3D =
				MAOFactory::getInstance()->getVectorMAOPositionator3D();

		for (unsigned int i = 0; i < vectorMAOPositionator3D.size(); i++) {
			MAOPositionator3D* m = vectorMAOPositionator3D.at(i);
			if (m->hasProperty(_property) && m->isPositioned()) {

				if (distance(*m) <= _minDistance) {
					_state = true;
					return;
				}
			}
		}
	}
}

float MLBSensorNear::mPyGetMinDistance() {
	return _minDistance;
}
void MLBSensorNear::mPySetMinDistance(float minDistance) {
	_minDistance = minDistance;
}
std::string MLBSensorNear::mPyGetNearProperty() {
	return _property;
}
void MLBSensorNear::mPySetNearProperty(std::string property) {
	_property = property;
}

float MLBSensorNear::distance(MAOPositionator3D& mao) {
	MAOPositionator3D& mao1 = (MAOPositionator3D&) *_parent;

	float dist = (mao.getSceneNode()._getDerivedPosition()
			- mao1.getSceneNode()._getDerivedPosition()).length();

	return dist;
}

MLBSensorNear::~MLBSensorNear() {

}
