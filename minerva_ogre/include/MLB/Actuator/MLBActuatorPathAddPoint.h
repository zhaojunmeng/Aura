/*
 * MLBActuatorPathAddPoint.h
 *
 *  Created on: 02/03/2011
 *      Author: cesar
 */

#ifndef MLBACTUATORPATHADDPOINT_H_
#define MLBACTUATORPATHADDPOINT_H_

#include <MLB/Actuator/MLBActuator.h>
#include <MAO/MAORenderable3DPath.h>

class MLBActuatorPathAddPoint: public MLBActuator {
public:
	MLBActuatorPathAddPoint(const std::string& name, MAORenderable3DPath& parent);
	virtual ~MLBActuatorPathAddPoint();
	void specificActuate();
};

#endif /* MLBACTUATORPATHADDPOINT_H_ */
