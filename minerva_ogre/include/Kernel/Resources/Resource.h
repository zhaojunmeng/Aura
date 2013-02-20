/*
 * Resource.h
 *
 *  Created on: 12/02/2013
 *      Author: cesar
 */
/* Wrapper for a Zip resource */

#ifndef RESOURCE_H_
#define RESOURCE_H_

#include <zip.h>
#include <string>
#include <Kernel/Logger.h>
#include <iostream>
#include <sstream>
#include <boost/filesystem.hpp>

class Resource {
protected:
	boost::filesystem::path _uri;
	bool _opened;
	char* _data;
	bool _eof;
	long _offset;
	size_t _size;

	virtual void load() = 0;

public:
	Resource(const boost::filesystem::path& uri);

	/* Raw methods */
	size_t getSize();
	const char* getData();

	/* Sequential access methods */
	ssize_t read(void* ptr, size_t size, size_t nmemb);
	bool seek(unsigned long offset);
	long tell();
	void rewind();

	/* Checking methods */
	bool isEOF();
	bool isOpened();
	void free();
	virtual ~Resource();
};

#endif /* RESOURCE_H_ */
