#include "../../utils/checkML.h"
#include "MainMenuState.h"
#include "../GameStateMachine.h"
#include "../../sdlutils/SDLUtils.h"
#include "../../components/Button.h"
#include "options/OptionsMenuState.h"
#include <iostream>
#include "../PlayState.h"
#include "../../components/Image.h"

MainMenuState::MainMenuState() : MenuState() {
	//Play button
	/*gameObjects.push_back(new Button(ButtonParams(
		Vector2D(WINDOW_WIDTH / 2 - (app->getTexture("button", this->getStateID())->getW() / 3) / 2, 3 * WINDOW_HEIGHT / 7 - (app->getTexture("button", this->getStateID())->getH() / 2)),
		"Jugar",
		app->getTexture("button", this->getStateID()), 
		app, 
		play)));
    //Load
    gameObjects.push_back(new Button(ButtonParams(
            Vector2D(WINDOW_WIDTH / 2 - (app->getTexture("button", this->getStateID())->getW() / 3) / 2, 4 * WINDOW_HEIGHT / 7 - (app->getTexture("button", this->getStateID())->getH() / 2)),
            "Cargar",
            app->getTexture("button", this->getStateID()),
            app,
            options,
            Scale(1.0f, 1.0f),
            Scale(1.7f, 1.7f))));
	//Options
	gameObjects.push_back(new Button(ButtonParams(
		Vector2D(WINDOW_WIDTH / 2 - (app->getTexture("button", this->getStateID())->getW() / 3) / 2, 5 * WINDOW_HEIGHT / 7 - (app->getTexture("button", this->getStateID())->getH() / 2)),
		"Opciones", 
		app->getTexture("button", this->getStateID()), 
		app, 
		options, 
		Scale(1.0f, 1.0f), 
		Scale(1.7f, 1.7f))));
	//Quit
	gameObjects.push_back(new Button(ButtonParams(
		Vector2D( WINDOW_WIDTH / 2 - (app->getTexture("quitbutton", this->getStateID())->getW() / 3) / 2, 6 * WINDOW_HEIGHT / 7 - (app->getTexture("quitbutton", this->getStateID())->getH() / 2)),
		"X", 
		app->getTexture("quitbutton", this->getStateID()), 
		app, 
		quit)));
	
	littleOtt = app->getTexture("ott_luz", MAIN_MENU);
	littleOttPos = Vector2D(320, 415);
	littleOttRect.x = littleOttPos.getX(); littleOttRect.y = littleOttPos.getY();
	littleOttRect.h = littleOtt->getH() * 0.5f; littleOttRect.w = littleOtt->getW() * 0.5f;
	*/

	SDL_Color transparente{ 255,255,255,1 };
	SDL_Color darkYellow{ 194,147,42 };
	SDL_Color yellow{ 255,217,102 };

	Vector2D textPos;
	auto background = mngr_->addEntity(ecs::_grp_UI);
	background->addComponent<Transform>(Vector2D(0,0), Vector2D(0,0), sdlutils().width(), sdlutils().height());
	background->addComponent<Image>(&sdlutils().images().at("mainmenubackground"));

	auto titleBack = mngr_->addEntity(ecs::_grp_UI);
	titleBack->addComponent<Text>("Ott: an Elemental Journey", sdlutils().fonts().at("press_start48"), darkYellow, transparente);
	textPos = Vector2D((sdlutils().width() - titleBack->getComponent<Text>()->getWidth()) / 2 - 5, 100);
	titleBack->getComponent<Text>()->setPosition(textPos);
	auto titleFront = mngr_->addEntity(ecs::_grp_UI);
	titleFront->addComponent<Text>("Ott: an Elemental Journey", sdlutils().fonts().at("press_start48"), yellow, transparente);
	textPos = Vector2D((sdlutils().width() - titleBack->getComponent<Text>()->getWidth()) / 2, 100);
	titleFront->getComponent<Text>()->setPosition(textPos);
	auto faeStudiosBack = mngr_->addEntity(ecs::_grp_UI);
	faeStudiosBack->addComponent<Text>("Fae Studios - 2023", sdlutils().fonts().at("press_start16"), darkYellow, transparente);
	textPos = Vector2D((sdlutils().width() - 5 * faeStudiosBack->getComponent<Text>()->getWidth()) / 2 - 1, sdlutils().height() - 30);
	faeStudiosBack->getComponent<Text>()->setPosition(textPos);
	auto faeStudiosFront = mngr_->addEntity(ecs::_grp_UI);
	faeStudiosFront->addComponent<Text>("Fae Studios - 2023", sdlutils().fonts().at("press_start16"), yellow, transparente);
	textPos = Vector2D((sdlutils().width() - 5 * faeStudiosFront->getComponent<Text>()->getWidth()) / 2, sdlutils().height() - 30);
	faeStudiosFront->getComponent<Text>()->setPosition(textPos);
	auto versionBack = mngr_->addEntity(ecs::_grp_UI);
	versionBack->addComponent<Text>("InDev 0.0.2", sdlutils().fonts().at("press_start16"), darkYellow, transparente);
	textPos = Vector2D((sdlutils().width() + 5 * versionBack->getComponent<Text>()->getWidth()) / 2 - 1, sdlutils().height() - 30);
	versionBack->getComponent<Text>()->setPosition(textPos);
	auto versionFront = mngr_->addEntity(ecs::_grp_UI);
	versionFront->addComponent<Text>("InDev 0.0.2", sdlutils().fonts().at("press_start16"), yellow, transparente);
	textPos = Vector2D((sdlutils().width() + 5 * versionFront->getComponent<Text>()->getWidth()) / 2, sdlutils().height() - 30);
	versionFront->getComponent<Text>()->setPosition(textPos);

	auto littleOtt = mngr_->addEntity(ecs::_grp_UI);
	littleOtt->addComponent<Transform>(Vector2D(320, 415), Vector2D(0, 0), 100, 100);
	littleOtt->addComponent<FramedImage>(&sdlutils().images().at("ott_luz"), 9, 8);

	auto playButton = mngr_->addEntity(ecs::_grp_UI);
	playButton->addComponent<Transform>(Vector2D(sdlutils().width() / 2, sdlutils().height() / 7), Vector2D(0, 0), 50, 50);
	playButton->addComponent<FramedImage>(&sdlutils().images().at("button"), 1, 3);
	SDL_Color blanco{ 255,255,255 };
	playButton->addComponent<Text>("Jugar", sdlutils().fonts().at("vcr_osd48"), blanco, transparente);
	playButton->addComponent<Button>(play);
    playButton->getComponent<Transform>()->setWidth(playButton->getComponent<FramedImage>()->getFrameWidth());
    playButton->getComponent<Transform>()->setHeight(playButton->getComponent<FramedImage>()->getFrameHeight());

}

void MainMenuState::play() {
	GameStateMachine::instance()->changeState(new PlayState());
}

void MainMenuState::options() {
	GameStateMachine::instance()->pushState(new OptionsMenuState());
}

void MainMenuState::quit() {
	sdlutils().close();
}

void MainMenuState::render() const {
    MenuState::render();
    /*titleBack->render();
    titleFront->render();
	faeStudiosBack->render();
	faeStudiosFront->render();
	versionBack->render();
	versionFront->render();
	littleOtt->renderFrame(littleOttRect, 0, animFrame);*/
}

/*MainMenuState::~MainMenuState() {
    delete titleBack;
    delete titleFront;
	delete faeStudiosBack;
	delete faeStudiosFront;
	delete versionBack;
	delete versionFront;
}*/

void MainMenuState::update() {
	/*if (SDL_GetTicks() >= animTime) { //Se cambia la animaci�n de ca�da
		animFrame = (animFrame + 1) % 2;
		animTime = SDL_GetTicks() + MAIN_MENU_OTT_ANIM_TIME;
	}*/
}