/*
 * MAO.h
 *
 *  Created on: 21/02/2011
 *      Author: cesar
 */

#ifndef MAO_H_
#define MAO_H_

//MAO Types
#define T_MAO 0
#define T_MAOPOSITIONATOR3D 1
#define T_MAOMARK 2
#define T_MAOMARKSGROUP 3
#define T_MAORENDERABLE2D 4
#define T_MAORENDERABLE2DIMAGE 5
#define T_MAORENDERABLE2DTEXT 6
#define T_MAORENDERABLE3D 7
//#define T_MAORENDERABLE3DLINE 8
#define T_MAORENDERABLE3DMODEL 9
//#define T_MAORENDERABLE3DPATH 10

#include <string>
#include <vector>
#include <cv.h>
#include <SDL.h>
#include <python.hpp>
#include <filesystem.hpp>

#include <MPY/WrapperTypes.h>
#include <Kernel/Logger.h>
#include <MAO/MAOProperty.h>

class MAO {
public:
	MAO(std::string name);
	MAO(const MAO& o);
	virtual ~MAO();
	std::string getName();

	/* Properties */
	/* Add properties */
	void addPropertyInt(std::string name, int value = 0);
	void addPropertyFloat(std::string name, float value = 0);
	void addPropertyString(std::string name, const std::string& value = "");
	void addPropertyBoolean(std::string name, bool value = false);
	void addPropertyPose(std::string name);
	void addPropertyPose(std::string name, cv::Mat& m);

	MAOProperty& getProperty(std::string name);
	int getType();

	/* Util */
	bool hasProperty(std::string name);

	/* Python functions! */
	boost::python::object mPyGetProperty(std::string name);
	MPYPropertyInt& getMPYPropertyInt(std::string name);
	MPYPropertyFloat& getMPYPropertyFloat(std::string name);
	MPYPropertyStr& getMPYPropertyStr(std::string name);
	MPYPropertyBool& getMPYPropertyBool(std::string name);
	MPYPropertyPose& getMPYPropertyPose(std::string name);

	std::vector<MPYPropertyInt*> _vectorMPYPropertyInt;
	std::vector<MPYPropertyFloat*> _vectorMPYPropertyFloat;
	std::vector<MPYPropertyStr*> _vectorMPYPropertyStr;
	std::vector<MPYPropertyBool*> _vectorMPYPropertyBool;
	std::vector<MPYPropertyPose*> _vectorMPYPropertyPose;

protected:
	std::string _name;
	std::vector<MAOProperty*> _vectorMAOProperty;
	int _type;
};

#endif /* MAO_H_ */
