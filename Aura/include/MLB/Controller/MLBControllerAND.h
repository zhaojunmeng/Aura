/*
 * MLBControllerAND.h
 *
 *  Created on: 22/02/2011
 *      Author: cesar
 */

#ifndef MLBCONTROLLERAND_H_
#define MLBCONTROLLERAND_H_

#include <MLB/MLB.h>
#include <MLB/Controller/MLBController.h>
#include <MAO/MAO.h>

class MLBControllerAND: public MLBController {
public:
	MLBControllerAND(const std::string& name, MAO& parent);
	virtual ~MLBControllerAND();
	void evaluate();
};

#endif /* MLBCONTROLLERAND_H_ */
