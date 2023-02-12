#include "../../../checkML.h"
#include "OptionsMenuState.h"
#include "../../../SDLApplication.h"
#include "../../../ui/Button.h"
#include "MusicOptionsMenuState.h"
#include "ControlMenuState.h"
#include <iostream>


OptionsMenuState::OptionsMenuState(SDLApplication* app) : MenuState(OPTIONS, app->getTexture("mainmenubackground", OPTIONS), app) {
	//Opciones gráficas
	gameObjects.push_back(new Button(ButtonParams(
		Vector2D(WINDOW_WIDTH / 2 - (app->getTexture("button", this->getStateID())->getW() / 3) / 2, 3 * WINDOW_HEIGHT / 7 - (app->getTexture("button", this->getStateID())->getH() / 2)),
		"Gráficos",
		app->getTexture("button", this->getStateID()),
		app,
		graphicOptions,
		Scale(0.33f, 1.0f),
		Scale(1.7f, 1.7f))));
	//Música y sonido
	gameObjects.push_back(new Button(ButtonParams(
		Vector2D(WINDOW_WIDTH / 2 - (app->getTexture("button", this->getStateID())->getW() / 3) / 2, 4 * WINDOW_HEIGHT / 7 - (app->getTexture("button", this->getStateID())->getH() / 2)),
		"Música",
		app->getTexture("button", this->getStateID()),
		app,
		musicOptions,
		Scale(0.33f, 1.0f))));
	//Controles
	gameObjects.push_back(new Button(ButtonParams(
		Vector2D(WINDOW_WIDTH / 2 - (app->getTexture("button", this->getStateID())->getW() / 3) / 2, 5 * WINDOW_HEIGHT / 7 - (app->getTexture("button", this->getStateID())->getH() / 2)),
		"Controles",
		app->getTexture("button", this->getStateID()),
		app,
		controls,
		Scale(0.33f, 1.0f),
		Scale(1.5f,1.5f))));
	//Volver
	gameObjects.push_back(new Button(ButtonParams(
		Vector2D( WINDOW_WIDTH / 2 - (app->getTexture("button", this->getStateID())->getW() / 3) / 2, 6 * WINDOW_HEIGHT / 7 - (app->getTexture("button", this->getStateID())->getH() / 2)), 
		"Volver", 
		app->getTexture("button", this->getStateID()), 
		app, 
		back, 
		Scale(0.33f, 1.0f))));

	titleBack = new Text("Opciones", *(app->getFont("press_start")), Vector2D(WINDOW_WIDTH / 2, 20), app->getRenderer(), { 194,147,42 }, Scale(4.0f, 4.0f));
	titleBack->movePosition(Vector2D(WINDOW_WIDTH / 2 - 4 * titleBack->getTexture()->getW() / 2 - 5, 100));
    titleFront = new Text("Opciones", *(app->getFont("press_start")), Vector2D(WINDOW_WIDTH / 2, 20), app->getRenderer(), { 255,217,102 }, Scale(4.0f, 4.0f));
    titleFront->movePosition(Vector2D(WINDOW_WIDTH / 2 - 4 * titleFront->getTexture()->getW() / 2, 100));
}

void OptionsMenuState::graphicOptions(SDLApplication* app) {
	std::cout << "opciones graficas" << std::endl;
}

void OptionsMenuState::musicOptions(SDLApplication* app) {
	app->getStateMachine()->pushState(new MusicOptionsMenuState(app));
}

void OptionsMenuState::back(SDLApplication* app) {
    app->getStateMachine()->popState();
}

void OptionsMenuState::controls(SDLApplication* app) {
	app->getStateMachine()->pushState(new ControlMenuState(app));
}

void OptionsMenuState::render() const {
	MenuState::render();
	titleBack->render();
    titleFront->render();
}

OptionsMenuState::~OptionsMenuState() {
	delete titleBack;
    delete titleFront;
}