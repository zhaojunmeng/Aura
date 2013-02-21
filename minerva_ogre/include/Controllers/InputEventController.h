/*
 * InputEventController.h
 *
 *  Created on: 20/02/2011
 *      Author: cesar
 */

#ifndef INPUTEVENTCONTROLLER_H_
#define INPUTEVENTCONTROLLER_H_

#include <OIS.h>
#include <Kernel/Logger.h>
#include <Kernel/Singleton.h>
#include <Kernel/World.h>
#include <Kernel/EndController.h>
#include <MLB/Sensor/MLBSensorKeyboard.h>

class InputEventController: public Singleton<InputEventController>,
		public OIS::MouseListener,
		public OIS::KeyListener {

	OIS::InputManager* _inputManager;
	OIS::Keyboard* _keyboard;
	OIS::Mouse* _mouse;
	std::list<MLBSensorKeyboard*> _listMLBSensorKeyboard;

	std::string OIS2StringKey(OIS::KeyCode key);

public:
	InputEventController();
	virtual ~InputEventController();

	void pollEvents();
	void addMLBSensorKeyboard(MLBSensorKeyboard& sensor);

	//Keyboard events
	bool keyPressed(const OIS::KeyEvent &arg);
	bool keyReleased(const OIS::KeyEvent &arg);

	//Mouse events
	bool mouseMoved(const OIS::MouseEvent &arg);
	bool mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id);
	bool mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id);

};

#endif /* INPUTEVENTCONTROLLER_H_ */
