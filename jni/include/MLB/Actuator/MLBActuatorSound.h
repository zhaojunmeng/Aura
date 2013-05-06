/*
 * MLBActuatorSound.h
 *
 *  Created on: 28/02/2011
 *      Author: cesar
 */

#ifndef MLBACTUATORSOUND_H_
#define MLBACTUATORSOUND_H_

#include <SDL_mixer.h>
#include <MLB/Actuator/MLBActuator.h>

class MLBActuatorSound: public MLBActuator {
public:
	MLBActuatorSound(const std::string& name, MAO& parent, const std::string& path);
	virtual ~MLBActuatorSound();


private:
	std::string _path;
	Mix_Chunk* _chunk;

	void specificActuate();
};

#endif /* MLBACTUATORSOUND_H_ */
