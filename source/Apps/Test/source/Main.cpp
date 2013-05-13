#include "TestApp.h"


int main() {

	TestApp app("OgreKitStartup.cfg");

	if (!app.initialize()) return -1;
	if (!app.getEngine()->initializeStepLoop()) return -1;

	bool running = true;
	while (running) {
	  app.getEngine()->stepOneFrame();
	}

	app.getEngine()->finalizeStepLoop();

	return 0;
}


