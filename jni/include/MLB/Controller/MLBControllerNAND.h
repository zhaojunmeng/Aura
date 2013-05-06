/*
 * MLBControllerNAND.h
 *
 *  Created on: 22/02/2011
 *      Author: cesar
 */

#ifndef MLBCONTROLLERNAND_H_
#define MLBCONTROLLERNAND_H_

#include <MLB/MLB.h>
#include <MLB/Controller/MLBController.h>
#include <MAO/MAO.h>

class MLBControllerNAND: public MLBController {
public:
	MLBControllerNAND(const std::string& name, MAO& parent);
	virtual ~MLBControllerNAND();
	void evaluate();
};

#endif /* MLBCONTROLLERNAND_H_ */
