/*
 * MAORenderable2DImage.cpp
 *
 *  Created on: 23/02/2011
 *      Author: cesar
 */

#include <MAO/MAORenderable2DImage.h>

MAORenderable2DImage::MAORenderable2DImage(const std::string& name,
		const boost::filesystem::path& filePath, const int& x, const int& y,
		const int& width, const int& height) :
		MAORenderable2D(name, x, y, width, height) {
	_filePath = filePath;
	_type = T_MAORENDERABLE2DIMAGE;


}

void MAORenderable2DImage::generateTexFromSDLSurface() {
}

boost::filesystem::path& MAORenderable2DImage::getFilePath() {
	return _filePath;
}

MAORenderable2DImage::~MAORenderable2DImage() {
}
