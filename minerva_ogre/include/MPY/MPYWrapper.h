/*
 * MGEModule.h
 *
 *  Created on: 04/04/2011
 *      Author: cesar
 *  Proxy class for bind MAOProperties to Python Api!
 */

#ifndef MPYWRAPPER_H_
#define MPYWRAPPER_H_


#include <vector>

#include <Kernel/Singleton.h>
#include <Kernel/Logger.h>
#include <Factories/MAOFactory.h>
#include <Factories/MLBFactory.h>
#include <MPY/MGEModule.h>
//#include <MPY/WrapperTypes.h>

using namespace boost::python;

class MPYWrapper: public Singleton<MPYWrapper> {
public:
	MPYWrapper();
	virtual ~MPYWrapper();

	void initPython();
	void runScripts();

private:
	MGEModule mge;
	object main_module;
	object main_namespace;
	object mge_module;
};

#endif /* MPYWRAPPER_H_ */
