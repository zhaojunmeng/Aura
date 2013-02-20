/*
 * ResourcesManager.cpp
 *
 *  Created on: 11/02/2013
 *      Author: cesar
 */

#include <Kernel/Resources/ResourcesManager.h>

const std::string ResourcesManager::dataFileName = "data.dat";
const std::string ResourcesManager::sourceCodeFile = "code.mrv";

using namespace std;

ResourcesManager::ResourcesManager() :
		_dataFile(NULL), _dataFileExists(true) {
}

void ResourcesManager::addResource(const boost::filesystem::path& uri) {
	_filesToPack.push_back(uri);
}

void ResourcesManager::addResource(const std::string& uri) {
	_filesToPack.push_back(boost::filesystem::path(uri));
}


Resource& ResourcesManager::getResource(const std::string& uri) {
	return getResource(boost::filesystem::path(uri));
}

Resource& ResourcesManager::getResource(const boost::filesystem::path& uri) {
	int err = 0;

	Resource* r = _resources[uri];

	cout<<"Looking for resource: "<<uri.generic_string()<<endl;

	/* Try to return the zip resource */
	if (_dataFileExists && r == NULL) {
		/* Check if the data file is opened */
		if (_dataFile == NULL)
			_dataFile = zip_open(dataFileName.c_str(), 0, &err);
		if (err) {
			Logger::getInstance()->warning(
					"[ResourcesManager] File data.dat is not present.");
			_dataFileExists = false;
		} else {
			r = new ResourceZip(_dataFile, uri);
		}
	}

	/* Else, try to load the actual file */
	if (!r || !r->isOpened()) {
		if (r)	delete r;
		r = new ResourceFile(uri);
	}

	/* Else, we can't find it.. aborting! */
	if (!r || !r->isOpened()) {
		if (r)
			delete r;
		Logger::getInstance()->error("[ResourcesManager] Could not find the resource " + uri.generic_string());
		exit(-1);
	}

	return *r;
}

/* Creates a zip file with the resources */
void ResourcesManager::pack(const stringstream& finalFile) {
	int err = 0;

	/* Stores the resources */
	if (_dataFile != NULL)
		zip_close(_dataFile);

	_dataFile = zip_open(dataFileName.c_str(), ZIP_CREATE | ZIP_EXCL, &err);
	if (err) { // It already exists, empty content
		// Data.dat already exists. Delete it and create it again!
		boost::filesystem::remove(dataFileName);

		/* It takes a while to remove it completely */
		//while(boost::filesystem::exists(dataFileName)) sleep(1);

		_dataFile = zip_open(dataFileName.c_str(), ZIP_CREATE , &err);

	}
	zip_source* s = NULL;

	//map<string, Resource*>::iterator it;
	list<boost::filesystem::path>::iterator it;
	for (it = _filesToPack.begin(); it != _filesToPack.end(); ++it) {
		boost::filesystem::path entry = *it;
		Logger::getInstance()->out("[ResourcesManager] Packing :" + entry.generic_string() + "...");

		s = zip_source_file(_dataFile, entry.c_str(), 0, -1);
		if(s == NULL){
			Logger::getInstance()->error(
							"[ResourcesManager] ERROR Locating the file "+entry.generic_string());
			Logger::getInstance()->out(zip_strerror(_dataFile));
			exit(-1);
		}

		if(zip_add(_dataFile, entry.c_str(), s) == -1) {
			Logger::getInstance()->error(
							"[ResourcesManager] ERROR adding the file "+entry.generic_string());
			Logger::getInstance()->out(zip_strerror(_dataFile));
			zip_source_free(s);
			exit(-1);
		}
	}

	/* Stores the source code */
	string code = finalFile.str();

	//Remove invalid characters
	code.erase(std::remove(code.begin(), code.end(), '\0'), code.end());

	Logger::getInstance()->out(
			"[ResourcesManager] Packing :" + string(sourceCodeFile) + "...");
	if ((s = zip_source_buffer(_dataFile, code.c_str(), code.length(), 0))
			== NULL || zip_add(_dataFile, sourceCodeFile.c_str(), s) == -1) {
		zip_error_get(_dataFile, &err, NULL);
		Logger::getInstance()->out(zip_strerror(_dataFile));
		exit(-1);

	}

	Logger::getInstance()->out("Finishing packing.");
	if (zip_close(_dataFile) == -1) {
		Logger::getInstance()->error(
				"[ResourcesManager] ERROR closing the zip file data.dat");
		cout << zip_strerror(_dataFile) << endl;
	}

}

ResourcesManager::~ResourcesManager() {
//if (_dataFile != NULL)
//	zip_close(_dataFile);

	map<boost::filesystem::path, Resource*>::iterator it;
	for (it = _resources.begin(); it != _resources.end(); ++it) {
		pair<boost::filesystem::path, Resource*> entry = (*it);
		if (entry.second != NULL)
			entry.second->free();
	}
}

