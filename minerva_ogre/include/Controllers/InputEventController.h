/*
 * InputEventController.h
 *
 *  Created on: 20/02/2011
 *      Author: cesar
 */

#ifndef INPUTEVENTCONTROLLER_H_
#define INPUTEVENTCONTROLLER_H_

#include <Kernel/Singleton.h>
#include <SDL.h>

#include <Kernel/Logger.h>
#include <Kernel/EndController.h>
#include <MLB/Sensor/MLBSensorKeyboard.h>

class InputEventController: public Singleton<InputEventController> {
public:
	InputEventController();
	virtual ~InputEventController();

	void pollEvents();
	void addMLBSensorKeyboard(MLBSensorKeyboard& sensor);

private:
	std::vector<MLBSensorKeyboard*> _vectorMLBSensorKeyboard;
};

#endif /* INPUTEVENTCONTROLLER_H_ */
