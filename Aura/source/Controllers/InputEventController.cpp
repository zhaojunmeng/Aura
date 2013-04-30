/*
 * InputEventController.cpp
 *
 *  Created on: 20/02/2011
 *      Author: cesar
 */

#include <Controllers/InputEventController.h>

using namespace std;

InputEventController::InputEventController() {
	OIS::ParamList param;
	size_t windowHandle = 0;
	std::ostringstream wHandleStr;

	Ogre::RenderWindow* win = World::getInstance()->getRenderWindow();
	win->getCustomAttribute("WINDOW", &windowHandle);
	wHandleStr << windowHandle;
	param.insert(std::make_pair(std::string("WINDOW"), wHandleStr.str()));

	//Do not kidnap my keyboard and mouse!
#if defined OIS_WIN32_PLATFORM
	param.insert(std::make_pair(std::string("w32_mouse"), std::string("DISCL_FOREGROUND" )));
	param.insert(std::make_pair(std::string("w32_mouse"), std::string("DISCL_NONEXCLUSIVE")));
	param.insert(std::make_pair(std::string("w32_keyboard"), std::string("DISCL_FOREGROUND")));
	param.insert(std::make_pair(std::string("w32_keyboard"), std::string("DISCL_NONEXCLUSIVE")));
#elif defined OIS_LINUX_PLATFORM
	param.insert(std::make_pair(std::string("x11_mouse_grab"), std::string("false")));
	param.insert(std::make_pair(std::string("x11_mouse_hide"), std::string("false")));
	param.insert(std::make_pair(std::string("x11_keyboard_grab"), std::string("false")));
	param.insert(std::make_pair(std::string("XAutoRepeatOn"), std::string("true")));
#endif

	_inputManager = OIS::InputManager::createInputSystem(param);
	_keyboard = static_cast<OIS::Keyboard*>(_inputManager->createInputObject(
			OIS::OISKeyboard, true));
	_mouse = static_cast<OIS::Mouse*>(_inputManager->createInputObject(
			OIS::OISMouse, true));

	//Setting up mouse state
	const OIS::MouseState &ms = _mouse->getMouseState();
	ms.width = 640;
	ms.height = 480;

	_keyboard->setEventCallback(this);
	_mouse->setEventCallback(this);

}

void InputEventController::pollEvents() {
	_keyboard->capture();
	_mouse->capture();
}

bool InputEventController::keyPressed(const OIS::KeyEvent &arg) {
	std::list<MLBSensorKeyboard*>::iterator sensorPtr;
	for (sensorPtr = _listMLBSensorKeyboard.begin();
			sensorPtr != _listMLBSensorKeyboard.end(); sensorPtr++) {
		if ((*sensorPtr)->getKey() == OIS2StringKey(arg.key) && (*sensorPtr)->getType() == "KEYDOWN") {
			(*sensorPtr)->setKeyDown(true);
		}

	}
	return true;
}

bool InputEventController::keyReleased(const OIS::KeyEvent &arg) {
	std::list<MLBSensorKeyboard*>::iterator sensorPtr;
	for (sensorPtr = _listMLBSensorKeyboard.begin();
			sensorPtr != _listMLBSensorKeyboard.end(); sensorPtr++) {
		if ((*sensorPtr)->getKey() == OIS2StringKey(arg.key)) {
			(*sensorPtr)->setKeyDown(false);
			if((*sensorPtr)->getType() == "KEYDOWN") (*sensorPtr)->trigger(); //Just one time!
		}
	}
	return true;
}

bool InputEventController::mouseMoved(const OIS::MouseEvent &arg) {
	return true;
}
bool InputEventController::mousePressed(const OIS::MouseEvent &arg,
		OIS::MouseButtonID id) {
	return true;
}
bool InputEventController::mouseReleased(const OIS::MouseEvent &arg,
		OIS::MouseButtonID id) {
	return true;
}

void InputEventController::addMLBSensorKeyboard(MLBSensorKeyboard& sensor) {
	_listMLBSensorKeyboard.push_back(&sensor);
}

std::string InputEventController::OIS2StringKey(OIS::KeyCode key) {
	if (key == OIS::KC_A) {
		return "A";
	} else if (key == OIS::KC_B) {
		return "B";
	} else if (key == OIS::KC_C) {
		return "C";
	} else if (key == OIS::KC_D) {
		return "D";
	} else if (key == OIS::KC_E) {
		return "E";
	} else if (key == OIS::KC_F) {
		return "F";
	} else if (key == OIS::KC_G) {
		return "G";
	} else if (key == OIS::KC_H) {
		return "H";
	} else if (key == OIS::KC_I) {
		return "I";
	} else if (key == OIS::KC_J) {
		return "J";
	} else if (key == OIS::KC_K) {
		return "K";
	} else if (key == OIS::KC_L) {
		return "L";
	} else if (key == OIS::KC_M) {
		return "M";
	} else if (key == OIS::KC_N) {
		return "N";
	} else if (key == OIS::KC_O) {
		return "O";
	} else if (key == OIS::KC_P) {
		return "P";
	} else if (key == OIS::KC_Q) {
		return "Q";
	} else if (key == OIS::KC_R) {
		return "R";
	} else if (key == OIS::KC_S) {
		return "S";
	} else if (key == OIS::KC_T) {
		return "T";
	} else if (key == OIS::KC_U) {
		return "U";
	} else if (key == OIS::KC_V) {
		return "V";
	} else if (key == OIS::KC_W) {
		return "W";
	} else if (key == OIS::KC_X) {
		return "X";
	} else if (key == OIS::KC_Y) {
		return "Y";
	} else if (key == OIS::KC_Z) {
		return "Z";
	} else if (key == OIS::KC_UP) {
		return "UP";
	} else if (key == OIS::KC_DOWN) {
		return "DOWN";
	} else if (key == OIS::KC_LEFT) {
		return "LEFT";
	} else if (key == OIS::KC_RIGHT) {
		return "RIGHT";
	} else if (key == OIS::KC_SPACE) {
		return "SPACE";
	} else if (key == OIS::KC_0) {
		return "0";
	} else if (key == OIS::KC_1) {
		return "1";
	} else if (key == OIS::KC_2) {
		return "2";
	} else if (key == OIS::KC_3) {
		return "3";
	} else if (key == OIS::KC_4) {
		return "4";
	} else if (key == OIS::KC_5) {
		return "5";
	} else if (key == OIS::KC_6) {
		return "6";
	} else if (key == OIS::KC_7) {
		return "7";
	} else if (key == OIS::KC_8) {
		return "8";
	} else if (key == OIS::KC_9) {
		return "9";
	} else if (key == OIS::KC_TAB) {
		return "TAB";
	} else if (key == OIS::KC_RETURN) {
		return "RETURN";
	} else if (key == OIS::KC_ESCAPE) {
		return "ESC";
	} else if (key == OIS::KC_F1) {
		return "F1";
	} else if (key == OIS::KC_F2) {
		return "F2";
	} else if (key == OIS::KC_F3) {
		return "F3";
	} else if (key == OIS::KC_F4) {
		return "F4";
	} else if (key == OIS::KC_F5) {
		return "F5";
	} else if (key == OIS::KC_F6) {
		return "F6";
	} else if (key == OIS::KC_F7) {
		return "F7";
	} else if (key == OIS::KC_F8) {
		return "F8";
	} else if (key == OIS::KC_F9) {
		return "F9";
	} else if (key == OIS::KC_F10) {
		return "F10";
	} else if (key == OIS::KC_F11) {
		return "F11";
	} else if (key == OIS::KC_F12) {
		return "F12";
	} else if (key == OIS::KC_RCONTROL) {
		return "RCTRL";
	} else if (key == OIS::KC_LCONTROL) {
		return "LCTRL";
	} else if (key == OIS::KC_RSHIFT) {
		return "RSHIFT";
	} else if (key == OIS::KC_LSHIFT) {
		return "LSHIFT";
	} else if (key == OIS::KC_BACK) {
		return "BACK";
	}
	Logger::getInstance()->error("Key type not found!: " + key);
	return "";

}

InputEventController::~InputEventController() {
}
