#include "../../../checkML.h"
#include "OptionsMenuState.h"
#include "../../../SDLApplication.h"
#include "../../../ui/Button.h"
#include "MusicOptionsMenuState.h"
#include <iostream>


OptionsMenuState::OptionsMenuState(SDLApplication* app) : MenuState(2, app->getTexture("mainmenubackground", 2), app) {
	//Graphics
	gameObjects.push_back(new Button(ButtonParams(
		Vector2D(WINDOW_WIDTH / 4 - (app->getTexture("button", this->getStateID())->getW() / 3) / 2, 2 * WINDOW_HEIGHT / 7 - (app->getTexture("button", this->getStateID())->getH() / 2)), 
		"Gráficos", 
		app->getTexture("button", this->getStateID()), 
		app, 
		graphicOptions, 
		Scale(0.33f, 1.0f),
		Scale(1.7f, 1.7f))));
	//Music
	gameObjects.push_back(new Button(ButtonParams(
		Vector2D(3 *WINDOW_WIDTH / 4 - (app->getTexture("button", this->getStateID())->getW() / 3) / 2, 2 * WINDOW_HEIGHT / 7 - (app->getTexture("button", this->getStateID())->getH() / 2)),
		"Música", 
		app->getTexture("button", this->getStateID()), 
		app, 
		musicOptions, 
		Scale(0.33f, 1.0f))));
	//Return
	gameObjects.push_back(new Button(ButtonParams(
		Vector2D( WINDOW_WIDTH / 2 - (app->getTexture("button", this->getStateID())->getW() / 3) / 2, 6 * WINDOW_HEIGHT / 7 - (app->getTexture("button", this->getStateID())->getH() / 2)), 
		"Volver", 
		app->getTexture("button", this->getStateID()), 
		app, 
		back, 
		Scale(0.33f, 1.0f))));

	title = new Text("Opciones", *(app->getFont("vcr_osd")), Vector2D(WINDOW_WIDTH / 2, 20), app->getRenderer(), { 255,255,255 }, Scale(3.0f, 3.0f));
	title->movePosition(Vector2D(WINDOW_WIDTH / 2 - 3 * title->getTexture()->getW() / 2, 20));
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

void OptionsMenuState::render() const {
	MenuState::render();
	title->render();
}

OptionsMenuState::~OptionsMenuState() {
	delete title;
}