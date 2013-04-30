/*
 * MBLActuatorSound.cpp
 *
 *  Created on: 28/02/2011
 *      Author: cesar
 */

#include <MLB/Actuator/MLBActuatorSound.h>

MLBActuatorSound::MLBActuatorSound(const std::string& name, MAO& parent,
		const std::string& path) :
	MLBActuator(name, parent) {
	_path = path;
	_chunk = NULL;

//	Resource& r = ResourcesManager::getInstance()->getResource(path);
	//SDL_RWops *rw = SDL_RWFromMem((void*) r.getData(), r.getSize());

	//_chunk = Mix_LoadWAV_RW(rw, 1);

	if (_chunk == NULL) {
		Logger::getInstance()->error(
				"Error creating MLB Actuator Sound with SDL_Mixer: " + name + " looking for file: "+path);
		throw "Error creating MLB Actuator Sound: " + name+ " looking for file: "+path;
	}

	Mix_VolumeChunk(_chunk, MIX_MAX_VOLUME);
	_mlbType = T_MLBACTUATORSOUND;
}

void MLBActuatorSound::specificActuate() {
	Mix_PlayChannel(-1,_chunk,0);
}

MLBActuatorSound::~MLBActuatorSound() {
	Mix_FreeChunk(_chunk);
}
