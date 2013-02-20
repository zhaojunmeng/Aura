/*
 * MAORenderable3DLine.h
 *
 *  Created on: 28/02/2011
 *      Author: cesar
 */

#ifndef MAORENDERABLE3DLINE_H_
#define MAORENDERABLE3DLINE_H_

#include <MAO/MAORenderable3D.h>

class MAORenderable3DLine: public MAORenderable3D {
	float _x1, _y1, _z1;
	float _x2, _y2, _z2;
	MAOPositionator3D* _mao1;
	MAOPositionator3D* _mao2;

	void setPointsFromMao();

	void _drawMAO();
	void _drawMAONoTexture();

public:
	MAORenderable3DLine(const std::string& name, float size, int r, int g,
			int b);
	MAORenderable3DLine(const std::string& name, float size, int r, int g,
			int b, MAOPositionator3D& mao1, MAOPositionator3D& mao2);
	virtual ~MAORenderable3DLine();

	int getR();
	int getG();
	int getB();
	void setPoints(float x1, float y1, float z1, float x2, float y2, float z2);

	void generateCollisionShape(int type);

};

#endif /* MAORENDERABLE3DLINE_H_ */
