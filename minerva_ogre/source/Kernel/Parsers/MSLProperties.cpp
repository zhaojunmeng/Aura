/*
 * MSLProperties.cpp
 *
 *  Created on: 23/NULL3/2NULL11
 *      Author: cesar
 */

#include <Kernel/Parsers/MSLProperties.h>

MSLProperties::MSLProperties() {
	init();
}

MSLProperties::MSLProperties(const MSLProperties& o){
	init();
	fill(o);
}

void MSLProperties::fill(const MSLProperties& o){
	if(o.string1 != NULL) string1 = o.string1;
	if(o.string2 != NULL) string2 = o.string2;
	if(o.string3 != NULL) string3 = o.string3;
	if(o.string4 != NULL) string4 = o.string4;

	if(o.float1 != 0.) float1 = o.float1;
	if(o.float2 != 0.) float2 = o.float2;
	if(o.float3 != 0.) float3 = o.float3;

	if(o.int1 != 0L) int1 = o.int1;
	if(o.int2 != 0) int2 = o.int2;
	if(o.int3 != 0) int3 = o.int3;
	if(o.int4 != 0) int4 = o.int4;

	if(o.bool1 != false) bool1 = o.bool1;

	if(o.btvector1 != NULL) btvector1 = o.btvector1;
	if(o.btvector2 != NULL) btvector2 = o.btvector2;

	//if(o.pose1 != NULL) pose1 = new cv::Mat(*o.pose1);
	//if(o.pose2 != NULL) pose2= new cv::Mat(*o.pose2);
	if(o.pose1 != NULL) pose1 = o.pose1;
	if(o.pose2 != NULL) pose2 = o.pose2;

	if(o.maovalue1 != NULL) maovalue1 = o.maovalue1;
	if(o.maovalue2 != NULL) maovalue2 = o.maovalue2;

	//Dont copy!
	if(o.maoproperty1 == NULL) maoproperty1 = o.maoproperty1;
	if(o.maoproperty2 == NULL) maoproperty2 = o.maoproperty2;

}

void MSLProperties::init(){
	string1 = NULL;
	string2 = NULL;
	string3 = NULL;
	string4 = NULL;
	float1 = 0.;
	float2 = 0.;
	float3 = 0.;
	int1 = 0;
	int2 = 0;
	int3 = 0;
	int4 = 0;
	bool1 = false;
	btvector1 = NULL;
	btvector2 = NULL;
	pose1 = NULL;
	pose2 = NULL;
	maovalue1 = NULL;
	maovalue2 = NULL;
	maoproperty1 = NULL;
	maoproperty2 = NULL;
}

MSLProperties::~MSLProperties() {
  /* Do not delete anything */
}
