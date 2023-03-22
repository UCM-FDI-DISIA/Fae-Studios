#include "../../utils/checkML.h"
#include "MainMenuState.h"
#include "../GameStateMachine.h"
#include "../../sdlutils/SDLUtils.h"
#include "../../components/Button.h"
#include "options/OptionsMenuState.h"
#include "../PlayState.h"
#include "../../components/Image.h"
#include "../../game/Constructors.h"
#include "../../game/Game.h"
#include "../../components/FadeTransitionComponent.h"
#include <mutex>
#include <condition_variable>
#include <thread>

MainMenuState::MainMenuState() : MenuState() {    
    SDL_Color yellow{ 255,217,102 };
	Vector2D pos;
    
    constructors::background(mngr_, &sdlutils().images().at("mainmenubackground"));

    fade = mngr_->addEntity(ecs::_grp_FADEOUT);
    fade->addComponent<FadeTransitionComponent>(true);

    pos = Vector2D(sdlutils().width() / 2, 100);
    constructors::boldText(mngr_, "Ott: an Elemental Journey", pos, sdlutils().fonts().at("press_start48"), 5, yellow);

    pos = Vector2D(sdlutils().width() / 9, sdlutils().height() - 30);
    constructors::boldText(mngr_, "Fae Studios - 2023", pos, sdlutils().fonts().at("press_start16"), 1, yellow);

    pos = Vector2D(8 * sdlutils().width() / 9, sdlutils().height() - 30);
    constructors::boldText(mngr_, "InDev 0.02", pos, sdlutils().fonts().at("press_start16"), 1, yellow);
    
    littleOtt = mngr_->addEntity(ecs::_grp_UI);
    littleOtt->addComponent<Transform>(Vector2D(320, 415), 100, 100);
    littleOtt->addComponent<FramedImage>(&sdlutils().images().at("ott_luz"), 9, 8);

    pos = Vector2D(sdlutils().width() / 2, 3 * sdlutils().height() / 7);
    constructors::button(mngr_, pos, "Jugar", sdlutils().fonts().at("vcr_osd48"), [this]() {
        sdlutils().soundEffects().at("play_button").play(0, ecs::_channel_UI);
        fade->getComponent<FadeTransitionComponent>()->setFunction([this]() { GameStateMachine::instance()->changeState(new PlayState());  playStateInit = true; });
        fade->getComponent<FadeTransitionComponent>()->revert();
    });

    pos = Vector2D(sdlutils().width() / 2, 4 * sdlutils().height() / 7);
    constructors::button(mngr_, pos, "Cargar", sdlutils().fonts().at("vcr_osd48"), [this]() {
        sdlutils().soundEffects().at("button").play(0, ecs::_channel_UI);
        fade->getComponent<FadeTransitionComponent>()->setFunction([]() { GameStateMachine::instance()->pushState(new OptionsMenuState()); });
        fade->getComponent<FadeTransitionComponent>()->revert();
    });

    pos = Vector2D(sdlutils().width() / 2, 5 * sdlutils().height() / 7);
    constructors::button(mngr_, pos, "Opciones", sdlutils().fonts().at("vcr_osd24"), [this]() {
        sdlutils().soundEffects().at("button").play(0, ecs::_channel_UI);
        fade->getComponent<FadeTransitionComponent>()->setFunction([](){ GameStateMachine::instance()->pushState(new OptionsMenuState()); });
        fade->getComponent<FadeTransitionComponent>()->revert();
    });

    pos = Vector2D(sdlutils().width() / 2, 6 * sdlutils().height() / 7);
    constructors::exitButton(mngr_, pos, []() {
        sdlutils().soundEffects().at("button").play(0, ecs::_channel_UI);
        game().exitGame();
    });

    fade->getComponent<FadeTransitionComponent>()->activateWithoutExecute();
    playStateInit = false;
}

void MainMenuState::update() {
    GameState::update();
	if (SDL_GetTicks() >= animTime) { //Se cambia la animaci�n de ca�da
		animFrame = (animFrame + 1) % 2;
        if(!playStateInit) littleOtt->getComponent<FramedImage>()->setCol(animFrame);
		animTime = SDL_GetTicks() + MAIN_MENU_OTT_ANIM_TIME;
	}
}