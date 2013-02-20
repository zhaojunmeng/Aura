/*
 * Parser3ds.h
 *
 *  Created on: 14/02/2013
 *      Author: cesar
 */

#ifndef PARSER3DS_H_
#define PARSER3DS_H_

#include <lib3ds/file.h>
#include <lib3ds/io.h>
#include <lib3ds/mesh.h>
#include <lib3ds/material.h>
#include <sstream>
#include <Kernel/Parsers/Parser.h>
#include <Kernel/Singleton.h>
#include <MAO/MAORenderable3DModel.h>


class Parser3ds: public Singleton<Parser3ds>, public Parser {
	/* Functions in order to read from a Resources, instead of a file */
	static Lib3dsBool _IoErrorFunc(void *self);
	static long _IoSeekFunc(void *self, long offset, Lib3dsIoSeek origin);
	static long _IoTellFunc(void *self);
	static size_t _IoReadFunc(void *self, void *buffer, size_t size);
	static size_t _IoWriteFunc(void *self, const void *buffer, size_t size); // Unused ;)

	Lib3dsFile* _load3dsFile(const boost::filesystem::path& file);

public:
	Parser3ds();
	virtual ~Parser3ds();

	void loadModel(const boost::filesystem::path& file, MAORenderable3DModel& model);
};

#endif /* PARSER3DS_H_ */
