/*
 * MAORenderable2DImage.h
 *
 *  Created on: 23/02/2011
 *      Author: cesar
 */

#ifndef MAORENDERABLE2DIMAGE_H_
#define MAORENDERABLE2DIMAGE_H_

#include <SDL.h>
#include <MAO/MAORenderable2D.h>

class MAORenderable2DImage: public MAORenderable2D {
public:
	MAORenderable2DImage(const std::string& name,
			const boost::filesystem::path& filePath, const int& x, const int& y,
			const int& width, const int& height);
	virtual ~MAORenderable2DImage();
	void generateTexFromSDLSurface();

	boost::filesystem::path& getFilePath();

private:

	boost::filesystem::path _filePath;
};

#endif /* MAORENDERABLE2DIMAGE_H_ */
