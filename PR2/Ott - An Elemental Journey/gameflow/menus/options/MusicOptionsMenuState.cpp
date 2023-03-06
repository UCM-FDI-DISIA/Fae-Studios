#include "../../../checkML.h"
#include "MusicOptionsMenuState.h"
#include "../../../SDLApplication.h"
#include "../../../ui/Button.h"
#include "../../../ui/Slider.h"

MusicOptionsMenuState::MusicOptionsMenuState(SDLApplication* app) : MenuState(MUSIC_OPTIONS, app->getTexture("playbackground", MUSIC_OPTIONS), app) {
	//Return
	gameObjects.push_back(new Button(ButtonParams(
		Vector2D(WINDOW_WIDTH / 2 - (app->getTexture("button", this->getStateID())->getW() / 3) / 2, 8 * WINDOW_HEIGHT / 9 - (app->getTexture("button", this->getStateID())->getH() / 2)), 
		"Volver", 
		app->getTexture("button", this->getStateID()), 
		app, 
		back)));
	//General volume
	gameObjects.push_back(new Slider(Vector2D(WINDOW_WIDTH / 2 - app->getTexture("slider", this->getStateID())->getW() / 2, 2 * WINDOW_HEIGHT / 9 - (app->getTexture("slider", this->getStateID())->getH() / 3 / 2)), app->getTexture("slider", this->getStateID()), app->getTexture("needle", this->getStateID()), "Volumen general", app, generalVolume, app->getVolume(0), true, Scale(1.0f, 1.0f), Scale(0.5f, 0.5f)));
	//Music volume
	gameObjects.push_back(new Slider(Vector2D(WINDOW_WIDTH / 2 - app->getTexture("slider", this->getStateID())->getW() / 2, 4 * WINDOW_HEIGHT / 9 - (app->getTexture("slider", this->getStateID())->getH() / 3 / 2)), app->getTexture("slider", this->getStateID()), app->getTexture("needle", this->getStateID()), "Música", app, musicVolume, app->getVolume(1), true, Scale(1.0f, 1.0f), Scale(0.5f, 0.5f)));
	//Sound volume
	gameObjects.push_back(new Slider(Vector2D(WINDOW_WIDTH / 2 - app->getTexture("slider", this->getStateID())->getW() / 2, 6 * WINDOW_HEIGHT / 9 - (app->getTexture("slider", this->getStateID())->getH() / 3 / 2)), app->getTexture("slider", this->getStateID()), app->getTexture("needle", this->getStateID()), "Sonido", app, soundsVolume, app->getVolume(2), true, Scale(1.0f, 1.0f), Scale(0.5f, 0.5f)));
}

void MusicOptionsMenuState::back(SDLApplication* app) {
	app->getStateMachine()->popState();
}

void MusicOptionsMenuState::generalVolume(int value, SDLApplication* app) {
	app->changeVolume(0, value);
}
void MusicOptionsMenuState::musicVolume(int value, SDLApplication* app) {
	app->changeVolume(1, value);
}
void MusicOptionsMenuState::soundsVolume(int value, SDLApplication* app) {
	app->changeVolume(2, value);
}