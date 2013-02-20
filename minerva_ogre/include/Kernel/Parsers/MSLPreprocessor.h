/*
 * MSLPreprocessor.h
 *
 *  Created on: 09/02/2013
 *      Author: cesar
 */

#ifndef MSLPREPROCESSOR_H_
#define MSLPREPROCESSOR_H_

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <Kernel/Logger.h>

class MSLPreprocessor {
public:
	MSLPreprocessor();
	virtual ~MSLPreprocessor();

	void start(const std::string& file, std::stringstream& finalFile);
};

#endif /* MSLPREPROCESSOR_H_ */
