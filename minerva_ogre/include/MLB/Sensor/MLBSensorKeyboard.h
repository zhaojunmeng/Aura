/*
 * MLBSensorKeyboard.h
 *
 *  Created on: 22/02/2011
 *      Author: cesar
 */

#ifndef MLBSENSORKEYBOARD_H_
#define MLBSENSORKEYBOARD_H_

#include <MLB/Sensor/MLBSensor.h>

class MLBSensorKeyboard: public MLBSensor {
public:
	MLBSensorKeyboard(const std::string& name, MAO& parent,std::string& type, std::string& key);
	virtual ~MLBSensorKeyboard();
	void evaluate();
	std::string& getKey();
	std::string& getType();
	void setKeyDown(bool keyDown);
private:
	std::string _key;
	bool _keyDown;
	std::string _type;
};

#endif /* MLBSENSORKEYBOARD_H_ */
