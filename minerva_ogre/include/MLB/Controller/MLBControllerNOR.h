/*
 * MLBControllerNOR.h
 *
 *  Created on: 22/02/2011
 *      Author: cesar
 */

#ifndef MLBCONTROLLERNOR_H_
#define MLBCONTROLLERNOR_H_

#include <MLB/Controller/MLBController.h>
#include <MAO/MAO.h>

class MLBControllerNOR: public MLBController {
public:
	MLBControllerNOR(const std::string& name, MAO& parent);
	virtual ~MLBControllerNOR();
	void evaluate();
};

#endif /* MLBCONTROLLERNOR_H_ */
