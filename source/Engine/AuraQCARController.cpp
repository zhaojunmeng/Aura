#include "AuraQCARController.h"

namespace Aura {

AuraQCARController::AuraQCARController() :
		mScreenWidth(0), mScreenHeight(0), mPortraitOrientation(false) {
}

AuraQCARController::~AuraQCARController() {
}

void AuraQCARController::configureVideoBackground() {
	// Get the default video mode:
	QCAR::CameraDevice& cameraDevice = QCAR::CameraDevice::getInstance();
	QCAR::VideoMode videoMode = cameraDevice.getVideoMode(
			QCAR::CameraDevice::MODE_DEFAULT);

	// Configure the video background
	QCAR::VideoBackgroundConfig config;
	config.mEnabled = false;
	config.mSynchronous = true;
	config.mPosition.data[0] = 0.0f;
	config.mPosition.data[1] = 0.0f;

	if (mPortraitOrientation) {
		config.mSize.data[0] = videoMode.mHeight
				* (mScreenHeight / (float) videoMode.mWidth);
		config.mSize.data[1] = mScreenHeight;

		if (config.mSize.data[0] < mScreenWidth) {
			config.mSize.data[0] = mScreenWidth;
			config.mSize.data[1] = mScreenWidth
					* (videoMode.mWidth / (float) videoMode.mHeight);
		}

	} else {
		config.mSize.data[0] = mScreenWidth;
		config.mSize.data[1] = videoMode.mHeight
				* (mScreenWidth / (float) videoMode.mWidth);

		if (config.mSize.data[1] < mScreenHeight) {
			config.mSize.data[0] = mScreenHeight
					* (videoMode.mWidth / (float) videoMode.mHeight);
			config.mSize.data[1] = mScreenHeight;
		}
	}

	// Set the config:
	QCAR::Renderer::getInstance().setVideoBackgroundConfig(config);
}

QCAR::Frame AuraQCARController::getFrame() {
	QCAR::State QCARState = QCAR::Renderer::getInstance().begin();
	QCAR::Renderer::getInstance().drawVideoBackground();
	QCAR::Frame frame = QCARState.getFrame();
	QCAR::Renderer::getInstance().end();
	return frame;
}

void AuraQCARController::stopCamera() {
	QCAR::CameraDevice::getInstance().stop();
	QCAR::CameraDevice::getInstance().deinit();
}

void AuraQCARController::setProjectionMatrix() {
	// Cache the projection matrix:
	const QCAR::CameraCalibration& cameraCalibration =
			QCAR::CameraDevice::getInstance().getCameraCalibration();
	projectionMatrix = QCAR::Tool::getProjectionGL(cameraCalibration, 2.0f,
			2500.0f);
}

}

extern "C" {
JNIEXPORT void JNICALL
Java_com_cesardev_aura_Aura_startCamera(JNIEnv *, jobject, int screenWidth,
		int screenHeight) {

	Aura::AuraQCARController::getInstance()->setScreenWidth(screenWidth);
	Aura::AuraQCARController::getInstance()->setScreenHeight(screenHeight);

	// Select the camera to open, set this to QCAR::CameraDevice::CAMERA_FRONT
	// to activate the front camera instead.
	QCAR::CameraDevice::CAMERA camera = QCAR::CameraDevice::CAMERA_DEFAULT;

	// Initialize the camera:
	if (!QCAR::CameraDevice::getInstance().init(camera)) {
		LOGI("Cant init camera!");
		return;
	}

	// Configure the video background
	Aura::AuraQCARController::getInstance()->configureVideoBackground();

	// Select the default mode:
	if (!QCAR::CameraDevice::getInstance().selectVideoMode(
			QCAR::CameraDevice::MODE_DEFAULT)) {
		LOGI("Cant set video mode!");
		return;
	}

	// Set image format
	if (!QCAR::setFrameFormat(QCAR::RGB888, true)) {
		LOGI("ERROR setting camera format");
		return;
	}

	// Start the camera:
	if (!QCAR::CameraDevice::getInstance().start()) {
		LOGI("Cant start camera");
		return;
	}

	Aura::AuraQCARController::getInstance()->setProjectionMatrix();
}

JNIEXPORT int JNICALL
Java_com_cesardev_aura_Aura_getOpenGlVersion(JNIEnv*, jobject) {

#ifdef USE_OPENGL_ES_1_1
	return 1;
#else 
#ifdef USE_OPENGL_ES_2_0
	return 2;
#else
#error "Error choosing the OpenGL Version, constant not well defined?"
#endif
#endif
}

} // extern "C"
