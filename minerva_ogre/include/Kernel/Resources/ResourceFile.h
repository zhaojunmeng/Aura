/*
 * ResourceFile.h
 *
 *  Created on: 12/02/2013
 *      Author: cesar
 */

#ifndef RESOURCEFILE_H_
#define RESOURCEFILE_H_

#include <Kernel/Resources/Resource.h>
#include <fstream>

class ResourceFile: public Resource {

	void load();
public:
	ResourceFile(const boost::filesystem::path& uri);
	virtual ~ResourceFile();

};

#endif /* RESOURCEFILE_H_ */
