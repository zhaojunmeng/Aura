/*
 * MLBActuatorDistance.h
 *
 *  Created on: 26/02/2011
 *      Author: cesar
 */

#ifndef MLBACTUATORDISTANCE_H_
#define MLBACTUATORDISTANCE_H_

#include <MLB/Actuator/MLBActuator.h>
#include <MAO/MAOPositionator3D.h>

class MLBActuatorDistance: public MLBActuator {
public:
	MLBActuatorDistance(const std::string& name, MAOPositionator3D& parent, MAOPositionator3D& mao, MAOProperty& property);
	virtual ~MLBActuatorDistance();


private:
	MAOPositionator3D* _mao;
	MAOProperty* _property;

	float distance();
	void specificActuate();
};

#endif /* MLBACTUATORDISTANCE_H_ */
