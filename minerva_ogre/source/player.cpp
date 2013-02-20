/*
 * main.cpp
 *
 *  Created on: 19/02/2011
 *      Author: cesar
 */
#include <Controllers/InputEventController.h>
#include <Controllers/GameLogicController.h>
#include <Controllers/PhysicsController.h>
#include <Factories/VideoFactory.h>
#include <Factories/TrackingMethodFactory.h>
#include <Kernel/VideoSource.h>
#include <Kernel/EndController.h>
#include <Kernel/World.h>
#include <Kernel/Logger.h>
#include <Kernel/Parsers/MSLParser.h>
#include <Kernel/Parsers/MSLPreprocessor.h>
#include <MPY/MPYWrapper.h>
#include <string>
#include <unistd.h>
#include <sstream>

using namespace std;

string getDirPath(char* path){
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

	/* Set app directory */
	string appDir = getDirPath(argv[0]);
	setDirectory(appDir);


	try {

		/* Initializations */
		MPYWrapper::getInstance()->initPython();
		World::getInstance()->initWorld(640, 480);
		VideoFactory::getInstance()->addVideoSource("cam", 0);
		TrackingMethodFactory::getInstance(); /* Init tracking */

		// Redirect cin
		streambuf* cinold = cin.rdbuf();
		Resource& sourceCode = ResourcesManager::getInstance()->getResource(
				ResourcesManager::sourceCodeFile);

		stringstream finalFile;
		finalFile << string(sourceCode.getData());
		cin.rdbuf(finalFile.rdbuf());

		/* Parsing! */
		Logger::getInstance()->out("Starts the source file parsing...");
		MSLParser parser;
		parser.yyparse();

		// Restoring cin
		cin.rdbuf(cinold);

	} catch (string e) {
		cout << "Exception: " << e << endl;
		EndController::getInstance()->end();
	} catch (const char* e) {
		cout << "Exception: " << e << endl;
		EndController::getInstance()->end();
	}

	//Main loop
	while (EndController::getInstance()->isRunning()) {
		//Grab a frame from the camera!
		VideoFactory::getInstance()->getMainCamera().grabFrame();

		//Tracking method!
		TrackingMethodFactory::getInstance()->pollMethods();

		//Physics
		PhysicsController::getInstance()->pollPhysics();

		//Poll Events
		InputEventController::getInstance()->pollEvents();

		//Game Logic
		GameLogicController::getInstance()->pollLogic();

		//Draw
		World::getInstance()->drawWorld();
	}

	//Freeing resources
	World::getInstance()->destroy();
	MAOFactory::getInstance()->destroy();
	MLBFactory::getInstance()->destroy();
	GameLogicController::getInstance()->destroy();
	TrackingMethodFactory::getInstance()->destroy();
	PhysicsController::getInstance()->destroy();
	InputEventController::getInstance()->destroy();
	VideoFactory::getInstance()->destroy();
	ResourcesManager::getInstance()->destroy();

	return 0;
}
