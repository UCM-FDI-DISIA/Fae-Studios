#include "../../checkML.h"
#include "MainMenuState.h"
#include "../../SDLApplication.h"
#include "../../ui/Button.h"
#include "options/OptionsMenuState.h"
#include <iostream>

MainMenuState::MainMenuState(SDLApplication* app) : MenuState(1, app->getTexture("mainmenubackground", 1), app) {
	//Play button
	gameObjects.push_back(new Button(ButtonParams(
		Vector2D(WINDOW_WIDTH / 2 - (app->getTexture("button", this->getStateID())->getW() / 3) / 2, 3 * WINDOW_HEIGHT / 7 - (app->getTexture("button", this->getStateID())->getH() / 2)),
		"Jugar",
		app->getTexture("button", this->getStateID()), 
		app, 
		play, 
		Scale(0.33f, 1.0f))));
    //Load
    gameObjects.push_back(new Button(ButtonParams(
            Vector2D(WINDOW_WIDTH / 2 - (app->getTexture("button", this->getStateID())->getW() / 3) / 2, 4 * WINDOW_HEIGHT / 7 - (app->getTexture("button", this->getStateID())->getH() / 2)),
            "Cargar",
            app->getTexture("button", this->getStateID()),
            app,
            options,
            Scale(0.33f, 1.0f),
            Scale(1.7f, 1.7f))));
	//Options
	gameObjects.push_back(new Button(ButtonParams(
		Vector2D(WINDOW_WIDTH / 2 - (app->getTexture("button", this->getStateID())->getW() / 3) / 2, 5 * WINDOW_HEIGHT / 7 - (app->getTexture("button", this->getStateID())->getH() / 2)),
		"Opciones", 
		app->getTexture("button", this->getStateID()), 
		app, 
		options, 
		Scale(0.33f, 1.0f), 
		Scale(1.7f, 1.7f))));
	//Quit
	gameObjects.push_back(new Button(ButtonParams(
		Vector2D( WINDOW_WIDTH / 2 - (app->getTexture("quitbutton", this->getStateID())->getW() / 3) / 2, 6 * WINDOW_HEIGHT / 7 - (app->getTexture("quitbutton", this->getStateID())->getH() / 2)),
		"X", 
		app->getTexture("quitbutton", this->getStateID()), 
		app, 
		quit, 
		Scale(0.33f, 1.0f))));

    titleBack = new Text("Ott: an Elemental Journey", *(app->getFont("press_start")), Vector2D(WINDOW_WIDTH / 2, 20), app->getRenderer(), { 194,147,42 }, Scale(3.0f, 3.0f));
    titleBack->movePosition(Vector2D(WINDOW_WIDTH / 2 - 3* titleBack->getTexture()->getW() / 2 - 5, 100));
    titleFront = new Text("Ott: an Elemental Journey", *(app->getFont("press_start")), Vector2D(WINDOW_WIDTH / 2, 20), app->getRenderer(), { 255,217,102 }, Scale(3.0f, 3.0f));
    titleFront->movePosition(Vector2D(WINDOW_WIDTH / 2 - 3 * titleFront->getTexture()->getW() / 2, 100));

}

void MainMenuState::play(SDLApplication* app) {
	std::cout << "play" << std::endl;
}

void MainMenuState::options(SDLApplication* app) {
	app->getStateMachine()->pushState(new OptionsMenuState(app));
}

void MainMenuState::quit(SDLApplication* app) {
	app->quitGame();
}

void MainMenuState::render() const {
    MenuState::render();
    titleBack->render();
    titleFront->render();
}

MainMenuState::~MainMenuState() {
    delete titleBack;
    delete titleFront;
}