/*
 * TrackingMethodFactory.cpp
 *
 *  Created on: 20/02/2011
 *      Author: cesar
 */

#include <Factories/TrackingMethodFactory.h>

TrackingMethodFactory::TrackingMethodFactory() {


}

void TrackingMethodFactory::pollMethods(){
	if(tmARTK.isActive()) tmARTK.pollMethod();
}

TrackingMethodARTK& TrackingMethodFactory::getTrackingMethodARTK(){
	return tmARTK;
}

TrackingMethodFactory::~TrackingMethodFactory() {
}
