/*
 * TrackingMethodARTK.cpp
 *
 *  Created on: 20/02/2011
 *      Author: cesar
 */

#include <Kernel/TrackingMethods/TrackingMethodARTK.h>

using namespace std;

TrackingMethodARTK::TrackingMethodARTK() :
		TrackingMethod() {
	_vectorMAOMark = std::vector<MAOMark*>();
	_vectorMAOMarksGroup = std::vector<MAOMarksGroup*>();

	_thres = 100;
	_cfMin = (float) 0.8;

	initARTK();
}
void TrackingMethodARTK::pollMethod() {

	cv::Mat* temp = NULL;
	cv::Mat frame;

	temp = VideoFactory::getInstance()->getMainCamera().getLastFrame();

	if (temp == NULL) {
		Logger::getInstance()->error(
				"Error getting frames in tracking method.");
		return;
	}

	cv::flip(*temp, frame, -1);

	//arDetectMarkerLite(frame.data, _thres, &_markerInfo, &_markerNum);
	arDetectMarker(frame.data, _thres, &_markerInfo, &_markerNum);
	//arDetectMarker(temp->data, _thres, &_markerInfo, &_markerNum)

	for (unsigned int i = 0; i < _vectorMAOMark.size(); i++) {
		checkMarkVisibility(_vectorMAOMark.at(i));
	}

	/* Check if they are positioned */
	for (unsigned int i = 0; i < _vectorMAOMarksGroup.size(); i++) {
		_vectorMAOMarksGroup.at(i)->checkIfPositioned();
	}

}

void TrackingMethodARTK::addMAOMark(MAOMark& mark) {
	Logger::getInstance()->out(
			"[TrackingMethodARTK::addMAOMark] Adding a MAOMark");

	int id;

	_vectorMAOMark.push_back(&mark);
	//id = arLoadPatt(mark.getPath().c_str());
	id = loadPattFromResource(
			ResourcesManager::getInstance()->getResource(mark.getPath()));

	if (id == -1) {
		Logger::getInstance()->error("Unable to load mark " + mark.getName());
	}

	mark.setId(id);

}

void TrackingMethodARTK::addMAOMarksGroup(MAOMarksGroup& marksGroup) {
	Logger::getInstance()->out(
			"[TrackingMethodARTK::addMAOMark] Adding a MAOMarksGroup");

	_vectorMAOMarksGroup.push_back(&marksGroup);
}

void TrackingMethodARTK::initARTK() {
	ARParam cparam;

	//Camera parameters
//#ifdef WIN32
	//if (arParamLoad("data\\camera_para.dat", 1, &wparam) < 0) {
//#else
//	if (arParamLoad("./data/camera_para.dat", 1, &wparam) < 0) {
//#endif
//		Logger::getInstance()->error("Unable to init ARToolKit");
//		deactive();
//		return;
//	}

	initCameraParams();

	arParamChangeSize(&_wparam, 640, 480, &cparam);
	arInitCparam(&cparam);

	Logger::getInstance()->out("ARToolKit loaded successfully!");
}

void TrackingMethodARTK::initCameraParams() {
	_wparam.xsize = 640;
	_wparam.ysize = 480;

	_wparam.mat[0][0] = 584.338;
	_wparam.mat[1][0] = 0;
	_wparam.mat[2][0] = 0;
	_wparam.mat[0][1] = 0;
	_wparam.mat[1][1] = 570.865;
	_wparam.mat[2][1] = 0;
	_wparam.mat[0][2] = 324;
	_wparam.mat[1][2] = 235;
	_wparam.mat[2][2] = 1;
	_wparam.mat[0][3] = 0;
	_wparam.mat[1][3] = 0;
	_wparam.mat[2][3] = 0;

	_wparam.dist_factor[0] = 319;
	_wparam.dist_factor[1] = 185;
	_wparam.dist_factor[2] = -37.4;
	_wparam.dist_factor[3] = 0.965333;
}

/*Checks visibility and sets up relative matrix */
void TrackingMethodARTK::checkMarkVisibility(MAOMark* mark) {
	int k = -1;
	for (int i = 0; i < _markerNum; i++) {
		if (mark->getId() == _markerInfo[i].id) {
			if (k == -1)
				k = i;
			else if (_markerInfo[k].cf < _markerInfo[i].cf)
				k = i;
		}
	}

	if (_markerInfo[k].cf < _cfMin)
		k = -1;

	if (k != -1) {
		double glAuxd[16];
		double arRelativeTrans[3][4];
		mark->setPositioned(true);
		arGetTransMat(&_markerInfo[k], mark->getCenter(), mark->getSize(),
				arRelativeTrans);
		argConvGlpara(arRelativeTrans, glAuxd);

		//Rotate 180º through y-axis ;)
		glAuxd[0] *= -1;
		glAuxd[2] *= -1;
		glAuxd[4] *= -1;
		glAuxd[6] *= -1;
		glAuxd[8] *= -1;
		glAuxd[10] *= -1;
		glAuxd[12] *= -1;
		glAuxd[14] *= -1;

		mark->setTrackingMatrix(glAuxd);

	} else {
		mark->setPositioned(false);
	}
}

/* Modified function of ARToolKit to load
 * patterns from a zip file Resource
 */
int TrackingMethodARTK::loadPattFromResource(Resource& r) {
	int patno;
	int h, i, j, l, m;
	int i1, i2, i3;

	extern int pattern_num;
	extern int patf[AR_PATT_NUM_MAX];
	extern int pat[AR_PATT_NUM_MAX][4][AR_PATT_SIZE_Y * AR_PATT_SIZE_X * 3];
	extern double patpow[AR_PATT_NUM_MAX][4];
	extern int patBW[AR_PATT_NUM_MAX][4][AR_PATT_SIZE_Y * AR_PATT_SIZE_X * 3];
	extern double patpowBW[AR_PATT_NUM_MAX][4];

	if (pattern_num == -1) {
		for (i = 0; i < AR_PATT_NUM_MAX; i++)
			patf[i] = 0;
		pattern_num = 0;
	}

	for (i = 0; i < AR_PATT_NUM_MAX; i++) {
		if (patf[i] == 0)
			break;
	}
	if (i == AR_PATT_NUM_MAX)
		return -1;
	patno = i;

	stringstream ss;
	ss<<string(r.getData());

	for (h = 0; h < 4; h++) {
		l = 0;
		for (i3 = 0; i3 < 3; i3++) {
			for (i2 = 0; i2 < AR_PATT_SIZE_Y; i2++) {
				for (i1 = 0; i1 < AR_PATT_SIZE_X; i1++) {
					ss>>j;
					j = 255 - j;
					pat[patno][h][(i2 * AR_PATT_SIZE_X + i1) * 3 + i3] = j;
					if (i3 == 0)
						patBW[patno][h][i2 * AR_PATT_SIZE_X + i1] = j;
					else
						patBW[patno][h][i2 * AR_PATT_SIZE_X + i1] += j;
					if (i3 == 2)
						patBW[patno][h][i2 * AR_PATT_SIZE_X + i1] /= 3;
					l += j;
				}
			}
		}
		l /= (AR_PATT_SIZE_Y * AR_PATT_SIZE_X * 3);

		m = 0;
		for (i = 0; i < AR_PATT_SIZE_Y * AR_PATT_SIZE_X * 3; i++) {
			pat[patno][h][i] -= l;
			m += (pat[patno][h][i] * pat[patno][h][i]);
		}
		patpow[patno][h] = sqrt((double) m);
		if (patpow[patno][h] == 0.0)
			patpow[patno][h] = 0.0000001;

		m = 0;
		for (i = 0; i < AR_PATT_SIZE_Y * AR_PATT_SIZE_X; i++) {
			patBW[patno][h][i] -= l;
			m += (patBW[patno][h][i] * patBW[patno][h][i]);
		}
		patpowBW[patno][h] = sqrt((double) m);
		if (patpowBW[patno][h] == 0.0)
			patpowBW[patno][h] = 0.0000001;
	}

	patf[patno] = 1;
	pattern_num++;

	return (patno);
}

TrackingMethodARTK::~TrackingMethodARTK() {

}
