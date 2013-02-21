/*
 * MAORenderable2D.h
 *
 *  Created on: 23/02/2011
 *      Author: cesar
 */

#ifndef MAORENDERABLE2D_H_
#define MAORENDERABLE2D_H_

#ifdef WIN32
#include <windows.h>
#endif

#include <MAO/MAO.h>
#include <Factories/VideoFactory.h>

class MAORenderable2D: public MAO {
public:
	MAORenderable2D(const std::string& name, const int& x, const int& y, const int& width, const int& height);
	virtual ~MAORenderable2D();
	virtual void generateTexFromSDLSurface()=0;
	void draw();

	bool isVisible();
	void setVisible(bool visible);

	int getX();
	void setX(int x);

	int getY();
	void setY(int y);

	void setWidth(int width);
	int getWidth();

	void setHeight(int height);
	int getHeight();

protected:
	void genGlTexture(SDL_Surface* surface);
	void setOrtho2D();
};

#endif /* MAORENDERABLE2D_H_ */
