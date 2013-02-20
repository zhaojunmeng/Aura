/*
 * Parser.h
 *
 *  Created on: 04/02/2013
 *      Author: cesar
 */

#ifndef PARSER_H_
#define PARSER_H_

#include <iostream>
#include <fstream>
#include <GL/gl.h>
#include <SDL_image.h>
#include <Kernel/Logger.h>
#include <MAO/MAORenderable3DModel.h>
#include <Kernel/Resources/ResourcesManager.h>
#include <boost/filesystem.hpp>

class Parser{
protected:
	bool _loadResourceToMaterial(MAOMaterial& mat);
	void _generateCallList(MAORenderable3DModel& model);
public:
	Parser();
	virtual ~Parser();

	virtual void loadModel(const boost::filesystem::path& file, MAORenderable3DModel& model) = 0;

};

#endif /* PARSER_H_ */
