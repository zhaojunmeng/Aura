/*
 * InputEventController.cpp
 *
 *  Created on: 20/02/2011
 *      Author: cesar
 */

#include <Controllers/InputEventController.h>

InputEventController::InputEventController() {

}

void InputEventController::pollEvents() {
	SDL_Event event;

	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		//Mouse events
		case SDL_MOUSEMOTION:
			break;
		case SDL_MOUSEBUTTONDOWN:
			break;
		case SDL_MOUSEBUTTONUP:
			break;
			//Keyboard events
		case SDL_KEYDOWN:
			for (unsigned int i = 0; i < _vectorMLBSensorKeyboard.size(); i++) {
				MLBSensorKeyboard* s = _vectorMLBSensorKeyboard.at(i);
				if (s->getType() == SDL_KEYDOWN && s->getKey()
						== event.key.keysym.sym)
					s->setKeyDown(true);
			}

			break;

		case SDL_KEYUP:
		  for (unsigned int i = 0; i < _vectorMLBSensorKeyboard.size(); i++) {
		    MLBSensorKeyboard* s = _vectorMLBSensorKeyboard.at(i);
		    if (s->getKey() == event.key.keysym.sym) {
		      s->setKeyDown(false);
		      if (s->getType() == SDL_KEYUP){
			s->trigger(); //Just one time!
		      }
		    }
		  }
			break;
			//Quit event
		case SDL_QUIT:
			EndController::getInstance()->end();
			break;
		}
	}
}

void InputEventController::addMLBSensorKeyboard(MLBSensorKeyboard& sensor) {
	_vectorMLBSensorKeyboard.push_back(&sensor);
}

InputEventController::~InputEventController() {
}
