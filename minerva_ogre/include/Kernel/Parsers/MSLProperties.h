/*
 * MSLProperties.h
 *
 *  Created on: 23/03/2011
 *      Author: cesar
 */
//Auxiliar class used to pass properties through the sintactic tree!

#ifndef MSLPROPERTIES_H_
#define MSLPROPERTIES_H_

#include <string>
#include <iostream>
#include <btBulletDynamicsCommon.h>
#include <MAO/MAOProperty.h>

class MSLProperties {
public:
	MSLProperties();

	/*Special constructor that uses the "fill" function. It is not a strict copy constructor */
	MSLProperties(const MSLProperties& o);
	virtual ~MSLProperties();

	//Fill the structure with the non-default values of "o"
	void fill(const MSLProperties& o);

	std::string* string1;
	std::string* string2;
	std::string* string3;
	std::string* string4;
	float float1;
	float float2;
	float float3;
	int int1;
	int int2;
	int int3;
	int int4;
	bool bool1;
	btVector3* btvector1;
	btVector3* btvector2;
	Ogre::Matrix4* pose1;
	Ogre::Matrix4* pose2;
	MAOValue* maovalue1;
	MAOValue* maovalue2;
	MAOProperty* maoproperty1; //Don't delete!
	MAOProperty* maoproperty2; //Don't delete!
private:
	void init();
};

#endif /* MSLPROPERTIES_H_ */
