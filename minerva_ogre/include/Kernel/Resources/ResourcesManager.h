/*
 * ResourcesManager.h
 *
 *  Created on: 11/02/2013
 *      Author: cesar
 */

#ifndef RESOURCESMANAGER_H_
#define RESOURCESMANAGER_H_

#include <string>
#include <map>
#include <zip.h>
#include <sstream>
#include <algorithm>
#include <list>
#include <Kernel/Singleton.h>
#include <Kernel/Resources/ResourceFile.h>
#include <Kernel/Resources/ResourceZip.h>
#include <Kernel/Logger.h>
#include <boost/filesystem.hpp>

class ResourcesManager: public Singleton<ResourcesManager>{
	std::map<boost::filesystem::path, Resource*> _resources;
	std::list<boost::filesystem::path> _filesToPack;
	zip* _dataFile; /* For zip resources */
	bool _dataFileExists;

public:
	static const std::string dataFileName;
	static const std::string sourceCodeFile;

	ResourcesManager();
	virtual ~ResourcesManager();

	void addResource(const std::string& uri);
	void addResource(const boost::filesystem::path& uri);
	Resource& getResource(const std::string& uri);
	Resource& getResource(const boost::filesystem::path& uri);
	void pack(const std::stringstream& finalFile);

};

#endif /* RESOURCESMANAGER_H_ */
