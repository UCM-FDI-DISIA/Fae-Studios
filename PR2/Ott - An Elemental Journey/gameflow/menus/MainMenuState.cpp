#include "../../checkML.h"
#include "MainMenuState.h"
#include "../../SDLApplication.h"
#include "../../ui/Button.h"
#include "options/OptionsMenuState.h"
#include <iostream>
#include "../play/PlayState.h"

MainMenuState::MainMenuState(SDLApplication* app) : MenuState(MAIN_MENU, app->getTexture("mainmenubackground", MAIN_MENU), app) {
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

    titleBack = new UIText("Ott: an Elemental Journey", *(app->getFont("press_start")), Vector2D(WINDOW_WIDTH / 2, 20), app->getRenderer(), { 194,147,42 }, Scale(3.0f, 3.0f));
    titleBack->movePosition(Vector2D(WINDOW_WIDTH / 2 - 3 * titleBack->getTexture()->getW() / 2 - 5, 100));
    titleFront = new UIText("Ott: an Elemental Journey", *(app->getFont("press_start")), Vector2D(WINDOW_WIDTH / 2, 20), app->getRenderer(), { 255,217,102 }, Scale(3.0f, 3.0f));
    titleFront->movePosition(Vector2D(WINDOW_WIDTH / 2 - 3 * titleFront->getTexture()->getW() / 2, 100));
	faeStudiosBack = new UIText("Fae Studios - 2023", *(app->getFont("press_start")), Vector2D(WINDOW_WIDTH / 2, 20), app->getRenderer(), { 194,147,42 }, Scale(1.0f, 1.0f));
	faeStudiosBack->movePosition(Vector2D(WINDOW_WIDTH / 2 - 5 * faeStudiosBack->getTexture()->getW() / 2 - 1, WINDOW_HEIGHT - 30));
	faeStudiosFront = new UIText("Fae Studios - 2023", *(app->getFont("press_start")), Vector2D(WINDOW_WIDTH / 2, 20), app->getRenderer(), { 255,217,102 }, Scale(1.0f, 1.0f));
	faeStudiosFront->movePosition(Vector2D(WINDOW_WIDTH / 2 - 5 * faeStudiosFront->getTexture()->getW() / 2, WINDOW_HEIGHT - 30));
	versionBack = new UIText("InDev 0.0.1", *(app->getFont("press_start")), Vector2D(WINDOW_WIDTH / 2, 20), app->getRenderer(), { 194,147,42 }, Scale(1.0f, 1.0f));
	versionBack->movePosition(Vector2D(WINDOW_WIDTH / 2 + 5 * versionBack->getTexture()->getW() / 2 - 1, WINDOW_HEIGHT - 30));
	versionFront = new UIText("InDev 0.0.1", *(app->getFont("press_start")), Vector2D(WINDOW_WIDTH / 2, 20), app->getRenderer(), { 255,217,102 }, Scale(1.0f, 1.0f));
	versionFront->movePosition(Vector2D(WINDOW_WIDTH / 2 + 5 * versionFront->getTexture()->getW() / 2, WINDOW_HEIGHT - 30));
	
	littleOtt = app->getTexture("ott_luz", MAIN_MENU);
	littleOttPos = Vector2D(400, 528);
	littleOttRect.x = littleOttPos.getX(); littleOttRect.y = littleOttPos.getY();
	littleOttRect.h = littleOtt->getH() * 0.5f; littleOttRect.w = littleOtt->getW() * 0.5f;
}

void MainMenuState::play(SDLApplication* app) {
	app->getStateMachine()->changeState(new PlayState(app));
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
	faeStudiosBack->render();
	faeStudiosFront->render();
	versionBack->render();
	versionFront->render();
	littleOtt->renderFrame(littleOttRect, 0, animFrame);
}

MainMenuState::~MainMenuState() {
    delete titleBack;
    delete titleFront;
	delete faeStudiosBack;
	delete faeStudiosFront;
	delete versionBack;
	delete versionFront;
}

void MainMenuState::update() {
	if (SDL_GetTicks() >= animTime) { //Se cambia la animaci�n de ca�da
		animFrame = (animFrame + 1) % 2;
		animTime = SDL_GetTicks() + MAIN_MENU_OTT_ANIM_TIME;
	}
}