#include "../../utils/checkML.h"
#include "PauseMenuState.h"
#include "../GameStateMachine.h"
//#include "../../ui/Button.h"
#include "MainMenuState.h"
#include "options/OptionsMenuState.h"
#include "../../sdlutils/InputHandler.h"
#include "../../sdlutils/SDLUtils.h"

PauseMenuState::PauseMenuState() : MenuState() {
	/*
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
		*/
}

void PauseMenuState::resume() {
	GameStateMachine::instance()->popState();
}

void PauseMenuState::mainMenu() {
	/*app->nextState = new MainMenuState();
	app->change = true;*/
}

void PauseMenuState::settings() {
	GameStateMachine::instance()->pushState(new OptionsMenuState());
}

void PauseMenuState::exit() {
	sdlutils().close();
}

void PauseMenuState::handleInput() {
	MenuState::handleInput();
	/*if (InputHandler::instance()->isKeyJustDown(SDLK_ESCAPE)) {
		InputHandler::instance()->clearState();
		app->getStateMachine()->popState();
	}*/
}