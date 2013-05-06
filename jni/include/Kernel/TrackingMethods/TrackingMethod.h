/*
 * TrackingMethod.h
 *
 *  Created on: 20/02/2011
 *      Author: cesar
 */

#ifndef TRACKINGMETHOD_H_
#define TRACKINGMETHOD_H_

#include <iostream>

class TrackingMethod {
public:
	TrackingMethod();
	virtual ~TrackingMethod();
	virtual void pollMethod()=0;
	bool isActive();
	void active();
	void deactive();

protected:
	bool _active;
};

#endif /* TRACKINGMETHOD_H_ */
