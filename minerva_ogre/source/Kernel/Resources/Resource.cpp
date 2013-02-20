/*
 * Resource.cpp
 *
 *  Created on: 12/02/2013
 *      Author: cesar
 */

#include <Kernel/Resources/Resource.h>

Resource::Resource(const boost::filesystem::path& uri) :
		_uri(uri), _opened(false), _data(NULL), _eof(false), _offset(0) {
}

size_t Resource::getSize() {
	return _size;
}

bool Resource::isEOF() {
	return _eof;
}

const char* Resource::getData() {
	return _data;
}

ssize_t Resource::read(void* ptr, size_t size, size_t nmemb) {
	if (_eof)
		return 0;

	size_t bytesReq = size * nmemb;
	size_t bytesLeft = _size - _offset;

	if (bytesReq >= bytesLeft) {
		_eof = true;
		bytesReq = bytesLeft;
	}

	for (unsigned int i = 0; i < bytesReq; i++) {
		static_cast<char*>(ptr)[i] = _data[_offset++];
	}

	return bytesReq;
}

bool Resource::seek(unsigned long offset) {
	if (offset > _size)
		return false;
	else if (offset == _size)
		_eof = true;
	else
		_eof = false;

	_offset = offset;

	return true;
}

long Resource::tell() {
	return _offset;
}

void Resource::rewind() {
	_offset = 0;
	_eof = false;
}

bool Resource::isOpened() {
	return _opened;
}

void Resource::free() {
	_opened = false;
	if (_data != NULL)
		delete[] _data;
}

Resource::~Resource() {
}

