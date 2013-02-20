/*
 * ParserObj.h
 *
 *  Created on: 14/02/2013
 *      Author: cesar
 */
/*
 * Implements the 3.0 specification of Wavefront's OBJ
 * http://www.martinreddy.net/gfx/3d/OBJ.spec
 *
 * Not supported features:
 * - Free-form Curves/Surfaces
 *
 */
#ifndef PARSEROBJ_H_
#define PARSEROBJ_H_

#include <Kernel/Parsers/Parser.h>

class ParserObj: public Singleton<ParserObj>, public Parser{
	void _loadTextureFile(const boost::filesystem::path&, MAOMaterial& mat);
	void _getFaceIndices(std::string& line, int& v, int& vt, int& vn);
public:

	void loadModel(const boost::filesystem::path& file, MAORenderable3DModel& model);

	ParserObj();
	virtual ~ParserObj();
};

#endif /* PARSEROBJ_H_ */
