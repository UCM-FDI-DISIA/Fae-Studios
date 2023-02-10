#include "ControlMenuState.h"
#include "../../../checkML.h"
#include "../../../SDLApplication.h"
#include "../../../ui/Button.h"

ControlMenuState::ControlMenuState(SDLApplication* app) : MenuState(5, app->getTexture("mainmenubackground", 5), app) {
	//Volver
	gameObjects.push_back(new Button(ButtonParams(
		Vector2D(WINDOW_WIDTH / 2 - (app->getTexture("button", this->getStateID())->getW() / 3) / 2, 6 * WINDOW_HEIGHT / 7 - (app->getTexture("button", this->getStateID())->getH() / 2)),
		"Volver",
		app->getTexture("button", this->getStateID()),
		app,
		back,
		Scale(0.33f, 1.0f))));

	controles = app->getTexture("playbackground", 5);
}

void ControlMenuState::back(SDLApplication* app) {
	app->getStateMachine()->popState();
}

