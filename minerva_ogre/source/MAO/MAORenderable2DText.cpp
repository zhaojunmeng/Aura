/*
 * MAORenderable2DText.cpp
 *
 *  Created on: 23/02/2011
 *      Author: cesar
 */

#include <MAO/MAORenderable2DText.h>

MAORenderable2DText::MAORenderable2DText(const std::string& name,
		const boost::filesystem::path& fontPath, const int& ptSize,
		const std::string& text, const int& x, const int& y, const int& style) :
	MAORenderable2D(name, x, y, 1, 1) {
	addPropertyString("text", text);
	addPropertyInt("ptSize", ptSize);
	addPropertyInt("r", 250);
	addPropertyInt("g", 50);
	addPropertyInt("b", 50);
	_type = T_MAORENDERABLE2DTEXT;

	_fontPath = fontPath;
	_style = style;

	loadFont();

	generateTexFromSDLSurface();


}

void MAORenderable2DText::generateTexFromSDLSurface() {
 	//SDL_Color color;
	//SDL_Surface* surface;

	//color.r = getR();
	//color.g = getG();
	//color.b = getB();

	//surface = TTF_RenderUTF8_Blended(_font,
	//		getProperty("text").getValue<std::string>().c_str(),
	//				  color);

	//texto = TTF_RenderText_UTF8_Shaded(_font,_text.c_str(),color);
	//texto = TTF_RenderText_UTF8_Blended(_font,_text.c_str(),color);

	//if (surface == NULL) {
		//Logger::getInstance()->error("Error generating SDL_Surface for a MAORenderable2DText");
		//throw "Error generating SDL_Surface for a MAORenderable2DText"+getName();
	//}

	//setWidth(surface->w);
	//setHeight(surface->h);

	//genGlTexture(surface);

	//SDL_FreeSurface(surface);
}

std::string& MAORenderable2DText::getText() {
	return getProperty("text").getValue<std::string>();
}

void MAORenderable2DText::setText(const std::string& text) {
	getProperty("text").setValue<std::string>(text);
	generateTexFromSDLSurface();
}

int MAORenderable2DText::getStyle() {
	return _style;
}

void MAORenderable2DText::setStyle(int style) {
	_style = style;
}

void MAORenderable2DText::setColor(int r, int b, int g) {
	getProperty("r").setValue<int>(r);
	getProperty("g").setValue<int>(g);
	getProperty("b").setValue<int>(b);
}

int MAORenderable2DText::getPtSize() {
	return getProperty("ptSize").getValue<int>();

}

void MAORenderable2DText::setPtSize(int ptSize) {
	getProperty("ptSize").setValue<int>(ptSize);
}
int MAORenderable2DText::getR() {
	return getProperty("r").getValue<int>();
}
int MAORenderable2DText::getG() {
	return getProperty("g").getValue<int>();
}
int MAORenderable2DText::getB() {
	return getProperty("b").getValue<int>();
}

void MAORenderable2DText::loadFont() {
	//Resource& r = ResourcesManager::getInstance()->getResource(_fontPath);
	//SDL_RWops *rw = SDL_RWFromMem((void*) r.getData(), r.getSize());

	//_font = TTF_OpenFontRW(rw, 1, getPtSize());

	if (_font == NULL) {
		Logger::getInstance()->error("Error loading the font: "+_fontPath.generic_string());
	//	Logger::getInstance()->error(TTF_GetError());
		throw "Error loading the font "+_fontPath.generic_string();
	}
}

MAORenderable2DText::~MAORenderable2DText() {
	//TTF_CloseFont(_font);
}
