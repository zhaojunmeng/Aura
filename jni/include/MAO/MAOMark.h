/*
 * MAOMark.h
 *
 *  Created on: 21/02/2011
 *      Author: cesar
 */

#ifndef MAOMARK_H_
#define MAOMARK_H_

#define HIST_LENGTH 4

#include <string>

#include<MAO/MAOPositionator3D.h>

using namespace std;

const int _historicSize = 4;

class MAOMark: public MAOPositionator3D {

public:
	MAOMark(const std::string& name, const boost::filesystem::path& path,
			const float& size);
	virtual ~MAOMark();
	const boost::filesystem::path& getPath();
	float getSize();
	double* getCenter();

	void setTrackingMatrix(Ogre::Matrix4& m);

	void setOffsetMatrix(const Ogre::Matrix4* offsetMatrix);

	void setId(int id);
	int getId();

private:
	Ogre::Matrix4 _offsetMatrix;
	boost::filesystem::path _bPath;
	std::list<Ogre::Matrix4> _listPosMatrix;
	float _size;
	int _id;
	double* _center;


};

#endif /* MAOMARK_H_ */
