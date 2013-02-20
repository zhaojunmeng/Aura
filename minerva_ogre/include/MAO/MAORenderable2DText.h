/*
 * MAORenderable2DText.h
 *
 *  Created on: 23/02/2011
 *      Author: cesar
 */

#ifndef MAORENDERABLE2DTEXT_H_
#define MAORENDERABLE2DTEXT_H_

#include <MAO/MAORenderable2D.h>
#include <SDL_ttf.h>

class MAORenderable2DText: public MAORenderable2D {
public:
	MAORenderable2DText(const std::string& name,
			const boost::filesystem::path& fontPath, const int& ptSize,
			const std::string& text, const int& x, const int& y,
			const int& style);
	virtual ~MAORenderable2DText();
	void generateTexFromSDLSurface();

	std::string& getText();
	void setText(const std::string& text);

	int getStyle();
	void setStyle(int style);

	int getPtSize();
	void setPtSize(int ptSize);
	void setColor(int r, int b, int g);
	int getR();
	int getG();
	int getB();
private:

	void loadFont();
	TTF_Font* _font;
	boost::filesystem::path _fontPath;
	int _style;
};

#endif /* MAORENDERABLE2DTEXT_H_ */
