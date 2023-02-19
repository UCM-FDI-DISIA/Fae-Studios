#include "../../checkML.h"
#include "PauseMenuState.h"
#include "../../SDLApplication.h"
#include "../../ui/Button.h"
#include "MainMenuState.h"
#include "options/OptionsMenuState.h"
#include "../../utils/InputHandler.h"

PauseMenuState::PauseMenuState(SDLApplication* app) : MenuState(PAUSE_MENU, app->getTexture("playbackground", PAUSE_MENU), app) {
	//Resume
	gameObjects.push_back(new Button(ButtonParams(
		Vector2D(WINDOW_WIDTH / 2 - (app->getTexture("button", this->getStateID())->getW() / 3) / 2, 3 * WINDOW_HEIGHT / 7 - (app->getTexture("button", this->getStateID())->getH() / 2)),
		"Continuar",
		app->getTexture("button", this->getStateID()),
		app,
		resume,
		Scale(1.0f, 1.0f),
		Scale(1.7f,1.7f))));
	//Main menu
	gameObjects.push_back(new Button(ButtonParams(
		Vector2D(WINDOW_WIDTH / 2 - (app->getTexture("button", this->getStateID())->getW() / 3) / 2, 4 * WINDOW_HEIGHT / 7 - (app->getTexture("button", this->getStateID())->getH() / 2)),
		"Menú principal",
		app->getTexture("button", this->getStateID()),
		app,
		mainMenu,
		Scale(1.0f, 1.0f),
		Scale(1.0f, 1.0f))));
	//Options
	gameObjects.push_back(new Button(ButtonParams(
		Vector2D(WINDOW_WIDTH / 2 - (app->getTexture("button", this->getStateID())->getW() / 3) / 2, 5 * WINDOW_HEIGHT / 7 - (app->getTexture("button", this->getStateID())->getH() / 2)),
		"Opciones",
		app->getTexture("button", this->getStateID()),
		app,
		settings,
		Scale(1.0f, 1.0f),
		Scale(1.7f, 1.7f))));
	//Quit
	gameObjects.push_back(new Button(ButtonParams(
		Vector2D(WINDOW_WIDTH / 2 - (app->getTexture("quitbutton", this->getStateID())->getW() / 3) / 2, 6 * WINDOW_HEIGHT / 7 - (app->getTexture("quitbutton", this->getStateID())->getH() / 2)),
		"X",
		app->getTexture("quitbutton", this->getStateID()),
		app,
		exit)));
}

void PauseMenuState::resume(SDLApplication* app) {
	app->getStateMachine()->popState();
}

void PauseMenuState::mainMenu(SDLApplication* app) {
	app->nextState = new MainMenuState(app);
	app->change = true;
}

void PauseMenuState::settings(SDLApplication* app) {
	app->getStateMachine()->pushState(new OptionsMenuState(app));
}

void PauseMenuState::exit(SDLApplication* app) {
	app->quitGame();
}

void PauseMenuState::handleEvents() {
	MenuState::handleEvents();
	/*if (InputHandler::instance()->isKeyJustDown(SDLK_ESCAPE)) {
		InputHandler::instance()->clearState();
		app->getStateMachine()->popState();
	}*/
}