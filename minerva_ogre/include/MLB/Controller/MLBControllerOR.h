/*
 * MLBControllerOR.h
 *
 *  Created on: 22/02/2011
 *      Author: cesar
 */

#ifndef MLBCONTROLLEROR_H_
#define MLBCONTROLLEROR_H_

#include <MLB/Controller/MLBController.h>
#include <MAO/MAO.h>

class MLBControllerOR: public MLBController {
public:
	MLBControllerOR(const std::string& name, MAO& parent);
	virtual ~MLBControllerOR();
	void evaluate();
};

#endif /* MLBCONTROLLEROR_H_ */
