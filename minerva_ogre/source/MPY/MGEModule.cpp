/*
 * MGEModule.cpp
 *
 *  Created on: 06/04/2011
 *      Author: cesar
 */

#include <MPY/MGEModule.h>

MGEModule::MGEModule() {
}

void MGEModule::setCurrentController(MLBControllerScript* c){
	_currentControllerScript = c;
}

object MGEModule::mPyGetCurrentController() {
	if (_currentControllerScript != NULL) {
		reference_existing_object::apply<MLBControllerScript*>::type converter;
		PyObject* pyObj = converter(_currentControllerScript);
		return object(handle<> (pyObj));

	} else {
		Logger::getInstance()->error(
				"This should never happen. _currentControllerScript is NULL!");
		exit(-1);
	}
}

object MGEModule::mPyGetMAO(std::string name){
  MAO* mao = NULL;

  try{
    mao = &(MAOFactory::getInstance()->getMAO(name));
  }catch(const char* e){
    Logger::getInstance()->error("MGEModule: Can't find the MAO: "+name);
    exit(-1);
  }

  reference_existing_object::apply<MAO*>::type converter;
  PyObject* pyObj = converter(mao);
  return object(handle<> (pyObj));


}
MGEModule::~MGEModule() {
}
