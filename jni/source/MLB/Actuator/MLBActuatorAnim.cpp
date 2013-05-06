/*
 * MLBActuatorAnim.cpp
 *
 *  Created on: 02/04/2011
 *      Author: cesar
 */

#include <MLB/Actuator/MLBActuatorAnim.h>

MLBActuatorAnim::MLBActuatorAnim(const std::string& name,
		MAORenderable3DModel& parent, int animAction, int animType) :
		MLBActuator(name, parent) {
	_animType = animType;
	_animAction = animAction;
	_mlbType = T_MLBACTUATORANIM;
}

void MLBActuatorAnim::specificActuate() {
	switch (_animAction) {
	case PLAY:
		((MAORenderable3DModel&) getParent()).playAnim(_animType);
		break;
	case PAUSE:
		((MAORenderable3DModel&) getParent()).pauseAnim();
		break;
	case STOP:
		((MAORenderable3DModel&) getParent()).stopAnim();
		break;
	default:
		Logger::getInstance()->error(
				"Invalid animation type for MLB Actuator Anim Orej: "
						+ getName());
		break;
	}
}

/* Python functions! */
int MLBActuatorAnim::mPyGetAnimType() {
	return _animType;
}
void MLBActuatorAnim::mPySetAnimType(int animType) {
	_animType = animType;
}
int MLBActuatorAnim::mPyGetAnimAction() {
	return _animAction;
}
void MLBActuatorAnim::mPySetAnimAction(int animAction) {
	_animAction = animAction;
}

MLBActuatorAnim::~MLBActuatorAnim() {
}
