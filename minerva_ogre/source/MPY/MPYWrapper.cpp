/*
 * MGEModule.cpp
 *
 *  Created on: 04/04/2011
 *      Author: cesar
 */

#include <MPY/MPYWrapper.h>

/* Boost Macro's ;) */
BOOST_PYTHON_MODULE(MGE) {
	/*--- MAO --*/
	object MAO_class = class_<MAO>("MAO",no_init)
	.def("getName",&MAO::getName)
	.def("getProperty",&MAO::mPyGetProperty)
	;

	/*--- MLBControllerScript --*/
	object MLBControllerScript_class = class_<MLBControllerScript>("MLBControllerScript",no_init)
	.def("getName",&MLB::getName)
	.def("getParent",&MLB::mPyGetParent)
	.def("getSensor",&MLBControllerScript::mPyGetSensor)
	.def("getActuator",&MLBControllerScript::mPyGetActuator)
	;

	/* ---------------- MLBSensorX -------------- */
	object MLBSensorActuator_class = class_<MLBSensorActuator>("MLBSensorActuator",no_init)
	.def("getName",&MLB::getName)
	.def("getState",&MLBSensorActuator::getState)
	;

	object MLBSensorAlways_class = class_<MLBSensorAlways>("MLBSensorAlways",no_init)
	.def("getName",&MLB::getName)
	.def("getState",&MLBSensorAlways::getState)
	;

	object MLBSensorCollision_class = class_<MLBSensorCollision>("MLBSensorCollision",no_init)
	.def("getName",&MLB::getName)
	.def("getState",&MLBSensorCollision::getState)
	.def("getCollisionProperty",&MLBSensorCollision::mPyGetCollisionProperty)
	.def("setCollisionProperty",&MLBSensorCollision::mPySetCollisionProperty)
	;

	object MLBSensorDelay_class = class_<MLBSensorDelay>("MLBSensorDelay",no_init)
	.def("getName",&MLB::getName)
	.def("getState",&MLBSensorDelay::getState)
	.def("getDelayFrames",&MLBSensorDelay::mPyGetDelayFrames)
	.def("setDelayFrames",&MLBSensorDelay::mPySetDelayFrames)
	;

	object MLBSensorKeyboard_class = class_<MLBSensorKeyboard>("MLBSensorKeyboard",no_init)
	.def("getName",&MLBSensorKeyboard::getName)
	.def("getState",&MLBSensorKeyboard::getState)
	;

	object MLBSensorNear_class = class_<MLBSensorNear>("MLBSensorNear",no_init)
	.def("getName",&MLB::getName)
	.def("getState",&MLBSensorNear::getState)
	.def("getMinDistance",&MLBSensorNear::mPyGetMinDistance)
	.def("setMinDistance",&MLBSensorNear::mPySetMinDistance)
	.def("getNearProperty",&MLBSensorNear::mPyGetNearProperty)
	.def("setNearProperty",&MLBSensorNear::mPySetNearProperty)
	;

	object MLBSensorProperty_class = class_<MLBSensorProperty>("MLBSensorProperty",no_init)
	.def("getName",&MLB::getName)
	.def("getState",&MLBSensorProperty::getState)
	.def("getType",&MLBSensorProperty::mPyGetType)
	.def("setType",&MLBSensorProperty::mPySetType)
	;

	object MLBSensorRandom_class = class_<MLBSensorRandom>("MLBSensorRandom",no_init)
	.def("getName",&MLB::getName)
	.def("getState",&MLBSensorRandom::getState)
	.def("getProbability",&MLBSensorRandom::mPySetProbability)
	.def("setProbability",&MLBSensorRandom::mPyGetProbability)
	;

	/* ---------------- MLBActuatorX -------------- */
#ifndef WIN32
	object MLBActuatorAddDynamicObject_class = class_<MLBActuatorAddDynamicObject>("MLBActuatorAddDynamicObject",no_init)
	.def("getName",&MLB::getName)
	.def("actuate",&MLBActuatorAddDynamicObject::actuate)
	.def("getTimeToExpire",&MLBActuatorAddDynamicObject::mPyGetTimeToExpire)
	.def("getTimeToExpire",&MLBActuatorAddDynamicObject::mPySetTimeToExpire)
	.def("getImpulse",&MLBActuatorAddDynamicObject::mPyGetImpulse)
	.def("setImpulse",&MLBActuatorAddDynamicObject::mPySetImpulse)
	  .def("getOffset",&MLBActuatorAddDynamicObject::mPyGetOffset)
	.def("setOffset",&MLBActuatorAddDynamicObject::mPySetOffset)
	;
#endif

	object MLBActuatorAng_class = class_<MLBActuatorAng>("MLBActuatorAng",no_init)
	.def("getName",&MLB::getName)
	.def("actuate",&MLBActuatorAng::actuate)
	;

	object MLBActuatorAnim_class = class_<MLBActuatorAnim>("MLBActuatorAnim",no_init)
	.def("getName",&MLB::getName)
	.def("actuate",&MLBActuatorAnim::actuate)
	.def("getAnimType",&MLBActuatorAnim::mPyGetAnimType)
	.def("setAnimType",&MLBActuatorAnim::mPySetAnimType)
	.def("getAnimAction",&MLBActuatorAnim::mPyGetAnimAction)
	.def("setAnimAction",&MLBActuatorAnim::mPySetAnimAction)
	;

	object MLBActuatorChangePose_class = class_<MLBActuatorChangePose>("MLBActuatorChangePose",no_init)
	.def("getName",&MLB::getName)
	.def("actuate",&MLBActuatorChangePose::actuate)
	.def("getLocType",&MLBActuatorChangePose::mPyGetLocType)
	.def("getRotType",&MLBActuatorChangePose::mPyGetRotType)
	.def("setLoctype",&MLBActuatorChangePose::mPySetLocType)
	.def("setRotType",&MLBActuatorChangePose::mPySetRotType)
	.def("getLoc",&MLBActuatorChangePose::mPyGetLoc)
	.def("setLoc",&MLBActuatorChangePose::mPySetLoc)
	.def("getRot",&MLBActuatorChangePose::mPyGetRot)
	.def("setRot",&MLBActuatorChangePose::mPySetRot)
	;

	object MLBActuatorDistance_class = class_<MLBActuatorDistance>("MLBActuatorDistance",no_init)
	.def("getName",&MLB::getName)
	.def("actuate",&MLBActuatorDistance::actuate)
	;

	object MLBActuatorPathAddPoint_class = class_<MLBActuatorPathAddPoint>("MLBActuatorPathAddPoint",no_init)
	.def("getName",&MLB::getName)
	.def("actuate",&MLBActuatorPathAddPoint::actuate)
	;

	object MLBActuatorPathRemovePoints_class = class_<MLBActuatorPathRemovePoints>("MLBActuatorPathRemovePoints",no_init)
	.def("getName",&MLB::getName)
	.def("actuate",&MLBActuatorPathRemovePoints::actuate)
	;

	object MLBActuatorProperty_class = class_<MLBActuatorProperty>("MLBActuatorProperty",no_init)
	.def("getName",&MLB::getName)
	.def("actuate",&MLBActuatorProperty::actuate)
	.def("getOpType",&MLBActuatorProperty::mPyGetOpType)
	.def("setOpType",&MLBActuatorProperty::mPySetOpType)
	;

	object MLBActuatorQuitApp_class = class_<MLBActuatorQuitApp>("MLBActuatorQuitApp",no_init)
	.def("getName",&MLB::getName)
	.def("actuate",&MLBActuatorQuitApp::actuate)
	;

	object MLBActuatorRandom_class = class_<MLBActuatorRandom>("MLBActuatorRandom",no_init)
	.def("getName",&MLB::getName)
	.def("actuate",&MLBActuatorRandom::actuate)
	;

	object MLBActuatorRelativePose_class = class_<MLBActuatorRelativePose>("MLBActuatorRelativePose",no_init)
	.def("getName",&MLB::getName)
	.def("actuate",&MLBActuatorRelativePose::actuate)
	.def("getInverse",&MLBActuatorRelativePose::mPyGetInverse)
	.def("setInverse",&MLBActuatorRelativePose::mPySetInverse)
	;
	object MLBActuatorSound_class = class_<MLBActuatorSound>("MLBActuatorSound",no_init)
	.def("getName",&MLB::getName)
	.def("actuate",&MLBActuatorSound::actuate)
	;
	object MLBActuatorVisibility_class = class_<MLBActuatorVisibility>("MLBActuatorVisibility",no_init)
	.def("getName",&MLB::getName)
	.def("actuate",&MLBActuatorVisibility::actuate)
	.def("getVisibility",&MLBActuatorVisibility::mPyGetVisibility)
	.def("setVisibility",&MLBActuatorVisibility::mPySetVisibility)
	;

	/*--- MGEModule ---*/
	object MGEModule_class = class_<MGEModule>("MGEModule")
	.def("getCurrentController",&MGEModule::mPyGetCurrentController)
	.def("getMAO",&MGEModule::mPyGetMAO)
	;

	/*-- MAOProperties! *--*/
	object MPYPropertyInt_class = class_<MPYPropertyInt>("MPYPropertyInt",no_init)
	.def("getName",&MPYPropertyInt::getName)
	.def("getValue",&MPYPropertyInt::getValue,return_value_policy<copy_non_const_reference>())
	.def("setValue",&MPYPropertyInt::setValue)
	;

	object MPYPropertyFloat_class = class_<MPYPropertyFloat>("MPYPropertyFloat",no_init)
	.def("getName",&MPYPropertyFloat::getName)
	.def("getValue",&MPYPropertyFloat::getValue,return_value_policy<copy_non_const_reference>())
	.def("setValue",&MPYPropertyFloat::setValue)
	;

	object MPYPropertyStr_class = class_<MPYPropertyStr>("MPYPropertyStr",no_init)
	.def("getName",&MPYPropertyStr::getName)
	.def("getValue",&MPYPropertyStr::getValue,return_value_policy<copy_non_const_reference>())
	.def("setValue",&MPYPropertyStr::setValue)
	;

	object MPYPropertyBool_class = class_<MPYPropertyBool>("MPYPropertyBool",no_init)
	.def("getName",&MPYPropertyBool::getName)
	.def("getValue",&MPYPropertyBool::getValue,return_value_policy<copy_non_const_reference>())
	.def("setValue",&MPYPropertyBool::setValue)
	;

	/*-- STL Types definition --*/
	object VectorStr_class = class_<VectorStr>("VectorStr")
	.def("__len__",&VectorStr::size)
	.def("clear",&VectorStr::clear)
	.def("append",&vector_item<std::string>::add,with_custodian_and_ward<1,2>())
	.def("__getitem__",&vector_item<std::string>::get,return_value_policy<copy_non_const_reference>())
	.def("__setitem__",&vector_item<std::string>::set,with_custodian_and_ward<1,2>())
	.def("__delitem__",&vector_item<std::string>::del)
	.def("__iter__",boost::python::iterator<VectorStr>())
	;

	object VectorInt_class = class_<VectorInt>("VectorInt")
	.def("__len__",&VectorInt::size)
	.def("clear",&VectorInt::clear)
	.def("append",&vector_item<int>::add,with_custodian_and_ward<1,2>())
	.def("__getitem__",&vector_item<int>::get,return_value_policy<copy_non_const_reference>())
	.def("__setitem__",&vector_item<int>::set,with_custodian_and_ward<1,2>())
	.def("__delitem__",&vector_item<int>::del)
	.def("__iter__",boost::python::iterator<VectorInt>())
	;
	object VectorFloat_class = class_<VectorFloat>("VectorFloat")
	.def("__len__",&VectorFloat::size)
	.def("clear",&VectorFloat::clear)
	.def("append",&vector_item<float>::add,with_custodian_and_ward<1,2>())
	.def("__getitem__",&vector_item<float>::get,return_value_policy<copy_non_const_reference>())
	.def("__setitem__",&vector_item<float>::set,with_custodian_and_ward<1,2>())
	.def("__delitem__",&vector_item<float>::del)
	.def("__iter__",boost::python::iterator<VectorFloat>())
	;
}

MPYWrapper::MPYWrapper() {
}

void MPYWrapper::initPython() {
	try {
		/* Init stuff */
		Logger::getInstance()->out("Initializing python subsystem");
		PyImport_AppendInittab("MGE", &initMGE);
		Py_Initialize();
		main_module = object((handle<> (
				borrowed(PyImport_AddModule("__main__")))));
		main_namespace = main_module.attr("__dict__");
		mge_module = object((handle<> (PyImport_ImportModule("MGE"))));
		(main_namespace)["MGE"] = mge_module;

		/* Inserting objects! */
		scope(mge_module).attr("mge") = ptr(&mge);

		/* This is the last thing to do! */
		PyRun_SimpleString("from MGE import *");

		/*-------- Importing constants! --------*/
		/* Anim!! */
		PyRun_SimpleString("MGE_PLAY=0");
		PyRun_SimpleString("MGE_PAUSE=1");
		PyRun_SimpleString("MGE_STOP=2");
		PyRun_SimpleString("MGE_SIMPLE=0");
		PyRun_SimpleString("MGE_LOOP=1");
		PyRun_SimpleString("MGE_PINGPONG=2");
		/* Change pose! */
		PyRun_SimpleString("MGE_LOCAL=0");
		PyRun_SimpleString("MGE_GLOBAL=1");
		/*ActuatorProperty!*/
		PyRun_SimpleString("MGE_ASSIGN=0");
		PyRun_SimpleString("MGE_ADD=1");
		PyRun_SimpleString("MGE_MINUS=2");
		PyRun_SimpleString("MGE_MULTIPLY=3");
		PyRun_SimpleString("MGE_DIVIDE=4");
		/*ASensorProperty*/
		PyRun_SimpleString("MGE_EQUAL=0");
		PyRun_SimpleString("MGE_NOTEQUAL=1");
		PyRun_SimpleString("MGE_INTERVAL=2");

	} catch (error_already_set e) {
		Logger::getInstance()->error("Can't initialize Python subsystem");
		PyErr_Print();
		exit(0);
	}
}

void MPYWrapper::runScripts() {
	std::vector<MLBControllerScript*>& v =
			MLBFactory::getInstance()->getVectorMLBControllerScript();
	for (unsigned int i = 0; i < v.size(); i++) {
		MLBControllerScript* c = v.at(i);
		object* o = c->getCompiledObj();
		if (o != NULL) {
			mge.setCurrentController(c);
			try {
				handle<> ignore((PyEval_EvalCode((PyCodeObject*) o->ptr(),
						main_namespace.ptr(), main_namespace.ptr())));
			} catch (error_already_set e) {
				Logger::getInstance()->error("Error executing the script: "
						+ c->getName());
				PyErr_Print();
				c->setCompiled(false);
			}
		}
	}
}

MPYWrapper::~MPYWrapper() {
	Py_Finalize();
}
