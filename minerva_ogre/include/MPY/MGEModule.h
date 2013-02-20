/*
 * MGEModule.h
 *
 *  Created on: 06/04/2011
 *      Author: cesar
 */

#ifndef MGEMODULE_H_
#define MGEMODULE_H_

#include <python.hpp>
#include <MLB/Controller/MLBControllerScript.h>
#include <Factories/MAOFactory.h>

using namespace boost::python;

class MGEModule {
public:
	MGEModule();
	virtual ~MGEModule();
	void setCurrentController(MLBControllerScript* c);

	/* Python functions! cool! */
	object mPyGetCurrentController();
	object mPyGetMAO(std::string name);

private:
	MLBControllerScript* _currentControllerScript;
};

#endif /* MGEMODULE_H_ */
