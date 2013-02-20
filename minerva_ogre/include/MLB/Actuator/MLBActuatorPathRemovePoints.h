/*
 * MLBActuatorPathRemovePoints.h
 *
 *  Created on: 01/03/2011
 *      Author: cesar
 */

#ifndef MLBACTUATORPATHREMOVEPOINTS_H_
#define MLBACTUATORPATHREMOVEPOINTS_H_

#include <MLB/Actuator/MLBActuator.h>
#include <MAO/MAORenderable3DPath.h>


class MLBActuatorPathRemovePoints: public MLBActuator {
public:
	MLBActuatorPathRemovePoints(const std::string& name, MAORenderable3DPath& parent);
	virtual ~MLBActuatorPathRemovePoints();

private:
	void specificActuate();
};

#endif /* MLBACTUATORPATHREMOVEPOINTS_H_ */
