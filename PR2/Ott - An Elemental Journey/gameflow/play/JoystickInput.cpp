#include "../play/JoystickInput.h"
#include "../../SDLApplication.h"
#include <iostream>
InputObject::InputObject(const Vector2D& position, Texture* texture, const Scale& scale) : GameObject(position, texture, scale) {
	
}

PlayState::PlayState(SDLApplication* app) : GameState(2, app) {
	InputObject* input = new InputObject(Vector2D(400 - 296/2, 300 - 214/2), app->getTexture("arrow", 2));
	gameObjects.push_back(input);
}

void InputObject::handleEvents(const SDL_Event& event) {
	if (event.type == SDL_JOYAXISMOTION) {
		if (event.jaxis.which == 0) { // SABER QUÉ JOYSTICK SE HA MOVIDO
			// X axis motion
			if (event.jaxis.axis == 0) { // SABER QUÉ EJE SE HA MOVIDO
				if (event.jaxis.value < -JOYSTICK_DEAD_ZONE) xDir = -1; // Left to dead zone
				else if (event.jaxis.value > JOYSTICK_DEAD_ZONE) xDir = 1; // Right to dead zone
				else xDir = 0;
			}
			// Y axis motion
			else if (event.jaxis.axis == 1) {
				if (event.jaxis.value < -JOYSTICK_DEAD_ZONE) yDir = -1; // Below to dead zone
				else if (event.jaxis.value > JOYSTICK_DEAD_ZONE) yDir = 1; // Above dead zone
				else yDir = 0;
			}
		}
	}

	if (event.type == SDL_JOYBUTTONDOWN) {
		cout << (int)event.jbutton.button << endl;
	}
}

void InputObject::update() {
	// Cálculo de ángulo para mostar dirección en la que apunta el Joystick
	arrowAngle = atan2((double)yDir, (double)xDir) * (180 / M_PI);
	if (xDir == 0 && yDir == 0) arrowAngle = 0;
}

void InputObject::render() const {
	texture->renderFrame(getRect(), 0, 0, arrowAngle);
}