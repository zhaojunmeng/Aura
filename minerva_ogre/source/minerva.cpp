/*
 * main.cpp
 *
 *  Created on: 19/02/2011
 *      Author: cesar
 */
#include <Kernel/Logger.h>
#include <Kernel/Parsers/MSLParser.h>
#include <Kernel/Parsers/MSLPreprocessor.h>
#include <string>
#include <unistd.h>
#include <sstream>
#include <MPY/MPYWrapper.h>
#include <boost/filesystem.hpp>

using namespace std;

void showCurrentDirectory() {
	char c[255];
#ifdef WIN32
	GetCurrentDirectory(255,c);
#else
	getcwd(c, 255);
#endif
	cout << "Current directory: " << c << endl;
}

string getCurrentDirectory() {
	char buf[255];
#ifdef WIN32
	GetCurrentDirectory(255,buf);
#else
	getcwd(buf, 255);
#endif
	return string(buf);
}

string getFileName(char* path) {
	string strpath(path);

#ifdef WIN32
	int p = strpath.rfind('\\');
#else
	int p = strpath.rfind('/');
#endif

	return strpath.substr(p + 1);
}

string getDirPath(char* path) {
	string strpath(path);
#ifdef WIN32
	int p = strpath.rfind('\\');
#else
	int p = strpath.rfind('/');
#endif

	return strpath.substr(0, p);
}

void setDirectory(string path) {

#ifdef WIN32
	SetCurrentDirectory(path.c_str());
#else
	chdir(path.c_str());
#endif

}

int main(int argc, char* argv[]) {
	cout << "~~~-------~~~" << endl;
	cout << "~~ Minerva! ~" << endl;
	cout << "~~~-------~~~" << endl;

	if (argc == 2) {
		try {
			/* Setting application directory */
			string workingDir = getCurrentDirectory();
			string minervaBinaryDir = getDirPath(argv[0]);

			string sourceCodeName = getFileName(argv[1]);
			string sourceCodeDir = getDirPath(argv[1]);

			setDirectory(workingDir);
			setDirectory(sourceCodeDir);

			// Init to parse the resources :)
			MPYWrapper::getInstance()->initPython();
			World::getInstance()->initWorld(640, 480);
			//VideoFactory::getInstance()->addVideoSource("cam", 0);
			//TrackingMethodFactory::getInstance(); /* Init tracking */

			// Parses the code looking for resources, and pack them!
			/* Preprocessing! */
			MSLPreprocessor preprocessor;
			stringstream finalFile;
			preprocessor.start(sourceCodeName, finalFile);

			// Redirect cin
			streambuf* cinold = cin.rdbuf();
			cin.rdbuf(finalFile.rdbuf());

			/* Parsing! */
			Logger::getInstance()->out("Starts the source file parsing...");
			MSLParser parser;
			parser.yyparse();

			/* Packing */
			//ResourcesManager::getInstance()->pack(finalFile);
			//ResourcesManager::getInstance()->destroy();

			// Restoring cin
			cin.rdbuf(cinold);

			// Copies the binary
			Logger::getInstance()->out("Creating executable...");
			string sourceDir = workingDir + "/" + minervaBinaryDir + "/player";
			string destDir = workingDir + "/" + sourceCodeDir;
			boost::filesystem::copy_file(sourceDir, "./app",
					boost::filesystem::copy_option::overwrite_if_exists);

		} catch (string e) {
			cout << "Exception: " << e << endl;
			EndController::getInstance()->end();
		} catch (const char* e) {
			cout << "Exception: " << e << endl;
			EndController::getInstance()->end();
		}
	} else {
		cout << "ARGUMENTS ERROR!" << endl;
		cout << "\tUsage:" << endl;
		cout << "\tGenerate: minerva <source_file>" << endl << endl;
		cout << "Building Augmented Reality Apps has never been so easy!"
				<< endl;
		return -1;
	}

	World::getInstance()->destroy();
	MAOFactory::getInstance()->destroy();
	MLBFactory::getInstance()->destroy();
	PhysicsController::getInstance()->destroy();

	Logger::getInstance()->out("Done! Enjoy your app created with Minerva!");

	return 0;
}
