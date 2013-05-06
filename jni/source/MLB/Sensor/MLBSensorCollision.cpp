/*
 * MLBSensorCollision.cpp
 *
 *  Created on: 07/03/2011
 *      Author: cesar
 */

#include <MLB/Sensor/MLBSensorCollision.h>

MLBSensorCollision::MLBSensorCollision(const std::string& name,
		MAORenderable3D& parent, const std::string& property) :
	MLBSensor(name, parent) {
	_property = property;
	_mlbType = T_MLBSENSORCOLLISION;
}

void MLBSensorCollision::evaluate() {
	if (((MAOPositionator3D*) _parent)->isPositioned()) {
		std::vector<MAORenderable3D*> vectorMAORenderable3D =
				MAOFactory::getInstance()->getVectorMAORenderable3D();

		for (unsigned int i = 0; i < vectorMAORenderable3D.size(); i++) {
			MAORenderable3D* m = vectorMAORenderable3D.at(i);
			if (m->hasProperty(_property) && m->getName() != getName()
					&& m->getName() != _name && m->isPositioned()) {
				if (PhysicsController::getInstance()->collision(
						(MAORenderable3D*) _parent, m)) {
					_state = true;
					return;
				}
			}
		}
	}

	_state = false;
}

std::string MLBSensorCollision::mPyGetCollisionProperty() {
	return _property;
}

void MLBSensorCollision::mPySetCollisionProperty(std::string property) {
	_property = property;
}

MLBSensorCollision::~MLBSensorCollision() {
}
