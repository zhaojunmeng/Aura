/*
 * MLBSensorRandom.h
 *
 *  Created on: 28/02/2011
 *      Author: cesar
 */

#ifndef MLBSENSORRANDOM_H_
#define MLBSENSORRANDOM_H_

#include <MLB/Sensor/MLBSensor.h>
#include <time.h>

class MLBSensorRandom: public MLBSensor {
public:
	MLBSensorRandom(const std::string& name, MAO& parent, float prob);
	virtual ~MLBSensorRandom();
	void evaluate();

	/* Python functions!*/
	float mPyGetProbability();
	void mPySetProbability(float prob);

private:
	float _prob;
};

#endif /* MLBSENSORRANDOM_H_ */
