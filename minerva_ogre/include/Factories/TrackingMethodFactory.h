/*
 * TrackingMethodFactory.h
 *
 *  Created on: 20/02/2011
 *      Author: cesar
 */

#ifndef TRACKINGMETHODFACTORY_H_
#define TRACKINGMETHODFACTORY_H_

#include <Kernel/Singleton.h>
#include <Kernel/TrackingMethods/TrackingMethodARTK.h>
#include <MAO/MAOMark.h>

class TrackingMethodFactory: public Singleton<TrackingMethodFactory> {
public:
	TrackingMethodFactory();
	virtual ~TrackingMethodFactory();
	void pollMethods();
	TrackingMethodARTK& getTrackingMethodARTK();

private:
	TrackingMethodARTK tmARTK;
};

#endif /* TRACKINGMETHODFACTORY_H_ */
