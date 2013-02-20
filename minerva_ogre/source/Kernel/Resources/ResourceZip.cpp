/*
 * ResourceZip.cpp
 *
 *  Created on: 12/02/2013
 *      Author: cesar
 */

#include <Kernel/Resources/ResourceZip.h>

using namespace std;

ResourceZip::ResourceZip(zip* dataFile, const boost::filesystem::path& uri) :
		Resource(uri) {
	_dataFile = dataFile;
	load();
}

void ResourceZip::load() {
	if (isOpened()) {
		Logger::getInstance()->warning(
				"[ResourceZip] The resource " + _uri.generic_string()
						+ " is already opened.");
		return;
	}

	zip_file* file;
	struct zip_stat st;

	Logger::getInstance()->out(
			"[ResourceZip] Unpacking resource " + _uri.generic_string());

	zip_stat_init(&st);

	if (zip_stat(_dataFile, _uri.generic_string().c_str(), 0, &st) == -1) {
		//Logger::getInstance()->error(
		//"[ResourceZip] Error locating the zip file " + _uri);
		_opened = false;
		return;
	}

	_size = st.size;

	file = zip_fopen(_dataFile, _uri.generic_string().c_str(), 0);

	if (file == NULL) {
		Logger::getInstance()->error(
				"[ResourceZip] Error opening the zip file "
						+ _uri.generic_string());
		_opened = false;
		return;
	}

	_data = new char[_size];





	if (zip_fread(file, _data, _size) == -1) {
		Logger::getInstance()->error(
				"[ResourceZip] Error reading the zip file "
						+ _uri.generic_string());
		_opened = false;
		return;
	}

	_opened = true;

	if (file != NULL)
		zip_fclose(file);
}

ResourceZip::~ResourceZip() {
}

