/*
 * MLBActuatorVisibility.cpp
 *
 *  Created on: 22/02/2011
 *      Author: cesar
 */

#include <MLB/Actuator/MLBActuatorVisibility.h>

MLBActuatorVisibility::MLBActuatorVisibility(const std::string& name,
		MAO& parent, bool value) :
		MLBActuator(name, parent) {
	_value = value;
	_mlbType = T_MLBACTUATORVISIBILITY;
	if (parent.getType() != T_MAORENDERABLE2DTEXT
			&& parent.getType() != T_MAORENDERABLE3DMODEL
			&& parent.getType() != T_MAORENDERABLE2DIMAGE
			&& parent.getType() != T_MAORENDERABLE3DLINE
			&& parent.getType() != T_MAORENDERABLE3DPATH) {
		Logger::getInstance()->error(
				"MAO type is not applicable to MLBActuatorVisibility!: "
						+ parent.getName());
		throw "MAO type is not applicable to MLBActuatorVisibility!: "
				+ parent.getName();
	}
}

void MLBActuatorVisibility::specificActuate() {
	switch (_parent->getType()) {
	case T_MAORENDERABLE2DIMAGE:
	case T_MAORENDERABLE2DTEXT:
		((MAORenderable2D*) _parent)->setVisible(_value);
		break;
	case T_MAORENDERABLE3DLINE:
	case T_MAORENDERABLE3DPATH:
	case T_MAORENDERABLE3DMODEL:
		((MAORenderable3D*) _parent)->setVisible(_value);
		break;
	default:
		throw "Strange MAO Type in MLBActuatorVisibility!";
	}

}

bool MLBActuatorVisibility::mPyGetVisibility() {
	return _value;
}

void MLBActuatorVisibility::mPySetVisibility(bool v) {
	_value = v;
}

MLBActuatorVisibility::~MLBActuatorVisibility() {
}
