#include <jni.h>
#include <android_native_app_glue.h>
#include <AuraApp.h>

AuraApp* auraApp = NULL;

static void android_handle_cmd(struct android_app* app, int cmd) {
	switch (cmd) {
	case APP_CMD_INIT_WINDOW:
		auraApp->initWindow();
		break;
	case APP_CMD_DESTROY:
		auraApp->destroy();
		break;
	case APP_CMD_TERM_WINDOW:
		auraApp->termWindow();
		break;
	case APP_CMD_RESUME:
		auraApp->resume();
		break;
	case APP_CMD_PAUSE:
		auraApp->pause();
		break;
	}
}

void android_main(struct android_app* state) {
	auraApp = new AuraApp();

	app_dummy();

	state->onAppCmd = android_handle_cmd;
	bool running = true;

	while (running) {
		int events;
		struct android_poll_source* pSource = NULL;

		auraApp->step();

		if (ALooper_pollAll(0, 0, &events, (void**) &pSource) >= 0) {
			if (pSource) {
				pSource->process(state, pSource);
			}
			if (state->destroyRequested) {
				running = false;
			}
		}

	}
}

