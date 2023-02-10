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
	controlsRect.w = 3 * WINDOW_WIDTH / 5;
	controlsRect.h = 4 * WINDOW_HEIGHT / 7;
	controlsRect.x = WINDOW_WIDTH / 2 - controlsRect.w / 2;
	controlsRect.y = 3 * WINDOW_HEIGHT / 7 - controlsRect.h / 2;
}

void ControlMenuState::back(SDLApplication* app) {
	app->getStateMachine()->popState();
}

void ControlMenuState::render() const {
	MenuState::render();
	controles->render(controlsRect);
}

