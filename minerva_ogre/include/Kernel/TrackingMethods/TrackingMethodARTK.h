/*
 * TrackingMethodARTK.h
 *
 *  Created on: 20/02/2011
 *      Author: cesar
 */

#ifndef TRACKINGMETHODARTK_H_
#define TRACKINGMETHODARTK_H_

#include <Kernel/TrackingMethods/TrackingMethod.h>
#include <Kernel/Logger.h>
#include <Factories/VideoFactory.h>
#include <MAO/MAOMark.h>
#include <MAO/MAOMarksGroup.h>

#include <cv.h>
#include <AR/ar.h>
//#include <AR/gsub.h>

class TrackingMethodARTK: public TrackingMethod {
public:
	TrackingMethodARTK();
	virtual ~TrackingMethodARTK();
	void pollMethod();
	void addMAOMark(MAOMark& mark);
	void addMAOMarksGroup(MAOMarksGroup& marksGroup);

private:

	int loadPatt(std::string& r);
	void initARTK();
	void initCameraParams();
	void checkMarkVisibility(MAOMark* mark);

	std::vector<MAOMark*> _vectorMAOMark;
	std::vector<MAOMarksGroup*> _vectorMAOMarksGroup;

	/* ARToolKit variables */
	ARMarkerInfo* _markerInfo;
	int _markerNum;
	int _thres;
	float _cfMin;

	/* Camera params */
	ARParam _wparam;
};

#endif /* TRACKINGMETHODARTK_H_ */
