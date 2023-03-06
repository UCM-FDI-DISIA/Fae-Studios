#include "../../../utils/checkML.h"
#include "OptionsMenuState.h"
#include "../../GameStateMachine.h"
//#include "../../../ui/Button.h"
#include "MusicOptionsMenuState.h"
#include "ControlMenuState.h"
#include <iostream>
#include "../../../sdlutils/SDLUtils.h"


OptionsMenuState::OptionsMenuState() : MenuState() {
	/*
	//Opciones gráficas
	gameObjects.push_back(new Button(ButtonParams(
		Vector2D(WINDOW_WIDTH / 2 - (app->getTexture("button", this->getStateID())->getW() / 3) / 2, 3 * WINDOW_HEIGHT / 7 - (app->getTexture("button", this->getStateID())->getH() / 2)),
		"Gráficos",
		app->getTexture("button", this->getStateID()),
		app,
		graphicOptions,
		Scale(1.0f, 1.0f),
		Scale(1.7f, 1.7f))));
	//Música y sonido
	gameObjects.push_back(new Button(ButtonParams(
		Vector2D(WINDOW_WIDTH / 2 - (app->getTexture("button", this->getStateID())->getW() / 3) / 2, 4 * WINDOW_HEIGHT / 7 - (app->getTexture("button", this->getStateID())->getH() / 2)),
		"Música",
		app->getTexture("button", this->getStateID()),
		app,
		musicOptions)));
	//Controles
	gameObjects.push_back(new Button(ButtonParams(
		Vector2D(WINDOW_WIDTH / 2 - (app->getTexture("button", this->getStateID())->getW() / 3) / 2, 5 * WINDOW_HEIGHT / 7 - (app->getTexture("button", this->getStateID())->getH() / 2)),
		"Controles",
		app->getTexture("button", this->getStateID()),
		app,
		controls,
		Scale(1.0f, 1.0f),
		Scale(1.5f,1.5f))));
	//Volver
	gameObjects.push_back(new Button(ButtonParams(
		Vector2D( WINDOW_WIDTH / 2 - (app->getTexture("button", this->getStateID())->getW() / 3) / 2, 6 * WINDOW_HEIGHT / 7 - (app->getTexture("button", this->getStateID())->getH() / 2)), 
		"Volver", 
		app->getTexture("button", this->getStateID()), 
		app, 
		back)));

	titleBack = new UIText("Opciones", *(app->getFont("press_start")), Vector2D(WINDOW_WIDTH / 2, 20), app->getRenderer(), { 194,147,42 }, Scale(4.0f, 4.0f));
	titleBack->movePosition(Vector2D(WINDOW_WIDTH / 2 - 4 * titleBack->getTexture()->getW() / 2 - 5, 100));
    titleFront = new UIText("Opciones", *(app->getFont("press_start")), Vector2D(WINDOW_WIDTH / 2, 20), app->getRenderer(), { 255,217,102 }, Scale(4.0f, 4.0f));
    titleFront->movePosition(Vector2D(WINDOW_WIDTH / 2 - 4 * titleFront->getTexture()->getW() / 2, 100));
	*/
}

void OptionsMenuState::graphicOptions() {
	std::cout << "opciones graficas" << std::endl;
}

void OptionsMenuState::musicOptions() {
	GameStateMachine::instance()->pushState(new MusicOptionsMenuState());
}

void OptionsMenuState::back() {
	GameStateMachine::instance()->popState();
}

void OptionsMenuState::controls() {
	GameStateMachine::instance()->pushState(new ControlMenuState());
}

void OptionsMenuState::render() const {
	MenuState::render();
	/*titleBack->render();
    titleFront->render();*/
}

/*OptionsMenuState::~OptionsMenuState() {
	delete titleBack;
    delete titleFront;
}*/