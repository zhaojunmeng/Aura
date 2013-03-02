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
}


std::string& MAORenderable2DText::getText() {
	return getProperty("text").getValue<std::string>();
}

void MAORenderable2DText::setText(const std::string& text) {
	getProperty("text").setValue<std::string>(text);
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



MAORenderable2DText::~MAORenderable2DText() {
}
