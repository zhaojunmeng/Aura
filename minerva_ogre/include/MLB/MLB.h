/*
 * MLB.h
 *
 *  Created on: 22/02/2011
 *      Author: cesar
 */

#ifndef MLB_H_
#define MLB_H_

#include <MAO/MAO.h>
#include <Kernel/Logger.h>

#include <filesystem.hpp>
#include <Ogre.h>

/* Types of MLB's */
#define T_MLBACTUATOR 0
#define T_MLBACTUATORADDDYNAMICOBJECT 1
#define T_MLBACTUATORANG 2
#define T_MLBACTUATORANIM 3
#define T_MLBACTUATORCHANGEPOSE 4
#define T_MLBACTUATORDISTANCE 5
//#define T_MLBACTUATORPATHADDPOINT 6
//#define T_MLBACTUATORPATHREMOVEPOINTS 7
#define T_MLBACTUATORPROPERTY 8
#define T_MLBACTUATORQUITAPP 9
#define T_MLBACTUATORRANDOM 10
#define T_MLBACTUATORRELATIVEPOSE 11
#define T_MLBACTUATORSOUND 12
#define T_MLBACTUATORVISIBILITY 13

#define T_MLBCONTROLLER 14
#define T_MLBCONTROLLERAND 15
#define T_MLBCONTROLLERNAND 16
#define T_MLBCONTROLLEROR 17
#define T_MLBCONTROLLERNOR 18
//#define T_MLBCONTROLLERSCRIPT 19

#define T_MLBSENSOR 20
#define T_MLBSENSORACTUATOR 21
#define T_MLBSENSORALWAYS 22
#define T_MLBSENSORCOLLISION 23
#define T_MLBSENSORDELAY 24
#define T_MLBSENSORKEYBOARD 25
#define T_MLBSENSORNEAR 26
#define T_MLBSENSORPROPERTY 27
#define T_MLBSENSORRANDOM 28

#include <string>
class MLB {
public:
	MLB(const std::string& name, MAO& parent);
	virtual ~MLB();

	MAO& getParent();
	std::string getName();
	int getMLBType();

protected:
	std::string _name;
	MAO* _parent;
	int _mlbType;
};

#endif /* MLB_H_ */
