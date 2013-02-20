/*
 * MLBSensorDelay.h
 *
 *  Created on: 28/02/2011
 *      Author: cesar
 */

#ifndef MLBSENSORDELAY_H_
#define MLBSENSORDELAY_H_

#include <MLB/Sensor/MLBSensor.h>

class MLBSensorDelay: public MLBSensor {
public:
	MLBSensorDelay(const std::string& name, MAO& parent, int delayFrames);
	virtual ~MLBSensorDelay();
	void evaluate();

	/* Python functions! */
	int mPyGetDelayFrames();
	void mPySetDelayFrames(int delayFrames);

private:
	int _delayFrames;
	int _frames;
};

#endif /* MLBSENSORDELAY_H_ */
