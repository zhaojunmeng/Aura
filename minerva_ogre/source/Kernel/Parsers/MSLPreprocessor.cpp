/*
 * MSLPreprocessor.cpp
 *
 *  Created on: 09/02/2013
 *      Author: cesar
 */

#include <Kernel/Parsers/MSLPreprocessor.h>

using namespace std;

MSLPreprocessor::MSLPreprocessor() {
}

void MSLPreprocessor::start(const std::string& file, stringstream& finalFile) {
	ifstream fileStream;
	fileStream.open(file.c_str());

	Logger::getInstance()->out("Preprocessing file: " + file);

	if (!fileStream.is_open()) {
		Logger::getInstance()->error("Application file not found!: " + file);
		throw "File not found exception: " + file;
	}

	while (!fileStream.eof()) {
		string line;
		getline(fileStream, line);
		stringstream streamLine;
		streamLine << line;

		// Checking for import sentences
		string firstWord;
		streamLine >> firstWord;

		if (string(firstWord) == "include") {
			string path;
			streamLine >> path;
			path = path.substr(1, path.length() - 2); // Removing quotes
			start(path, finalFile);
		} else if (firstWord.size() > 1 && firstWord.at(0) == '/'
				&& firstWord.at(1) == '/') { // Checking for one line comments //
			// Ignore that line :)
		} else {
			finalFile << line << endl;
		}
	}

	fileStream.close();
}

MSLPreprocessor::~MSLPreprocessor() {
}

