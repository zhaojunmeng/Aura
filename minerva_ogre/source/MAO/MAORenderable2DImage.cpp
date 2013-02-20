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

	generateTexFromSDLSurface();
}

void MAORenderable2DImage::generateTexFromSDLSurface() {

	/* Generate the image just one time */
	if (_texture != -1)
		return;

	SDL_Surface* surface;

	try {
		Resource& r = ResourcesManager::getInstance()->getResource(_filePath);
		SDL_RWops *rw = SDL_RWFromMem((void*) r.getData(), r.getSize());

		surface = IMG_Load_RW(rw, 1);

	} catch (std::string& e) {
		Logger::getInstance()->error("Unable to load image file: " + _filePath.generic_string());
		//Logger::getInstance()->error(IMG_GetError());
		throw "Unable to load image file: " + _filePath.generic_string();
	}

	genGlTexture(surface);

	SDL_FreeSurface(surface);
}

boost::filesystem::path& MAORenderable2DImage::getFilePath() {
	return _filePath;
}

MAORenderable2DImage::~MAORenderable2DImage() {
}
