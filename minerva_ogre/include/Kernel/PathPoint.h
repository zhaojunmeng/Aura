/*
 * MAORenderable3DPathPoint.h
 *
 *  Created on: 28/02/2011
 *      Author: cesar
 */

#ifndef PATHPOINT_H_
#define PATHPOINT_H_

class PathPoint {
public:
	PathPoint(float x, float y, float z, float size, int r, int g, int b, bool visible);
	virtual ~PathPoint();

	float getSize();
	float getX();
	float getY();
	float getZ();
	int getR();
	int getG();
	int getB();
	bool getVisible();

private:
	float _x, _y, _z;
	int _r, _g, _b;
	bool _visible;
	float _size;


};

#endif /* PATHPOINT_H_ */
