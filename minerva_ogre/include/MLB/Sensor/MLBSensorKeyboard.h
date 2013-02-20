/*
 * MLBSensorKeyboard.h
 *
 *  Created on: 22/02/2011
 *      Author: cesar
 */

#ifndef MLBSENSORKEYBOARD_H_
#define MLBSENSORKEYBOARD_H_

#include <SDL.h>
#include <MLB/Sensor/MLBSensor.h>

class MLBSensorKeyboard: public MLBSensor {
public:
	MLBSensorKeyboard(const std::string& name, MAO& parent,SDL_EventType& type, SDLKey& key);
	virtual ~MLBSensorKeyboard();
	void evaluate();
	SDLKey& getKey();
	SDL_EventType& getType();
	void setKeyDown(bool keyDown);
private:
	SDLKey _key;
	bool _keyDown;
	SDL_EventType _type;
};

#endif /* MLBSENSORKEYBOARD_H_ */
