/*
 * MLBActuatorAnimOrej.h
 *
 *  Created on: 02/04/2011
 *      Author: cesar
 */

#ifndef MLBACTUATORANIM_H_
#define MLBACTUATORANIM_H_

#include <MLB/Actuator/MLBActuator.h>
#include <MAO/MAORenderable3DModel.h>

enum AnimAction {PLAY, PAUSE, STOP};

class MLBActuatorAnim: public MLBActuator {
public:
	MLBActuatorAnim(const std::string& name, MAORenderable3DModel& parent, int animAction, int animType = 0);
	virtual ~MLBActuatorAnim();

	/* Python funcions! */
	int mPyGetAnimType();
	void mPySetAnimType(int animType);
	int mPyGetAnimAction();
	void mPySetAnimAction(int animAction);

private:
	void specificActuate();
	int _animType; /* Refers to the animation type: LOOP; SIMPLE, PING-PONG */
	int _animAction; /* Refers to the command: PLAY, PAUSE or STOP */
};

#endif /* MLBACTUATORANIM_H_ */
