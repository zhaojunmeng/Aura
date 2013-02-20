/*
 * MLBActuatorVisibility.h
 *
 *  Created on: 22/02/2011
 *      Author: cesar
 */

#ifndef MLBACTUATORVISIBILITY_H_
#define MLBACTUATORVISIBILITY_H_

#include <MLB/Actuator/MLBActuator.h>
#include <MAO/MAORenderable3D.h>
#include <MAO/MAORenderable2D.h>
#include <MAO/MAO.h>

class MLBActuatorVisibility: public MLBActuator {
public:
	MLBActuatorVisibility(const std::string& name, MAO& parent, bool value);
	virtual ~MLBActuatorVisibility();

	/* Python functions */
	bool mPyGetVisibility();
	void mPySetVisibility(bool v);

private:
	bool _value;
	void specificActuate();
};

#endif /* MLBACTUATORVISIBILITY_H_ */
