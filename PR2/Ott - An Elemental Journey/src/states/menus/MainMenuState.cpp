#include "../../utils/checkML.h"
#include "MainMenuState.h"
#include "../GameStateMachine.h"
#include "../../components/Button.h"
#include "options/OptionsMenuState.h"
#include "../../components/Image.h"
#include "../../game/Constructors.h"
#include "../../game/Game.h"

MainMenuState::MainMenuState() : MenuState() {    
    SDL_Color yellow{ 255,217,102 };
	Vector2D pos;
    
    constructors::background(mngr_, &sdlutils().images().at("mainmenubackground"));

    fade = mngr_->addEntity(ecs::_grp_FADEOUT);
    fade->addComponent<FadeTransitionComponent>(true);

    pos = Vector2D(sdlutils().getWindowDimensions().getX() / 2, 100);
    constructors::boldText(mngr_, "Ott: an Elemental Journey", pos, sdlutils().fonts().at("press_start48"), 5, yellow);

    pos = Vector2D(sdlutils().getWindowDimensions().getX() / 9, sdlutils().getWindowDimensions().getY() - 30);
    constructors::boldText(mngr_, "Fae Studios - 2023", pos, sdlutils().fonts().at("press_start16"), 1, yellow);

    pos = Vector2D(8.2 * sdlutils().getWindowDimensions().getX() / 9, sdlutils().getWindowDimensions().getY() - 30);
    constructors::boldText(mngr_, "Hito 2 - DEMO", pos, sdlutils().fonts().at("press_start16"), 1, yellow);
    
    littleOtt = mngr_->addEntity(ecs::_grp_UI);
    littleOtt->addComponent<Transform>(Vector2D(2*sdlutils().getWindowDimensions().getX()/10, 5.1*sdlutils().getWindowDimensions().getY()/10), 100, 100);
    littleOtt->addComponent<FramedImage>(&sdlutils().images().at("ott_luz"), 9, 8);

    pos = Vector2D(sdlutils().getWindowDimensions().getX() / 2, 3 * sdlutils().getWindowDimensions().getY() / 7);
    buttons.push_back(constructors::button(mngr_, pos, "Jugar", sdlutils().fonts().at("vcr_osd48"), [this]() {
#ifdef __APPLE__
        sdlutils().soundEffects().at("play_button").play(0, ecs::_channel_UI);
        fade->getComponent<FadeTransitionComponent>()->setFunction([this]() { GameStateMachine::instance()->changeState(new PlayState()); playStateInit = true; sdlutils().musics().at("main_menu_music").fadeOutMusic(100); });
        fade->getComponent<FadeTransitionComponent>()->revert();
#endif
#ifdef __WINDOWS__
        sdlutils().soundEffects().at("play_button").play(0, ecs::_channel_UI);
        fade->getComponent<FadeTransitionComponent>()->setFunction([]() { GameStateMachine::instance()->changeState(new PlayState()); sdlutils().musics().at("main_menu_music").fadeOutMusic(100);});
        fade->getComponent<FadeTransitionComponent>()->revert();
        playStateInit = true;
#endif
    }));

    pos = Vector2D(sdlutils().getWindowDimensions().getX() / 2, 4 * sdlutils().getWindowDimensions().getY() / 7);
    buttons.push_back(constructors::button(mngr_, pos, "Cargar", sdlutils().fonts().at("vcr_osd48"), [this]() {
        sdlutils().soundEffects().at("button").play(0, ecs::_channel_UI);
        fade->getComponent<FadeTransitionComponent>()->setFunction([]() { GameStateMachine::instance()->changeState(new PlayState("../resources/saves/temporalUniqueSave.sv")); sdlutils().musics().at("main_menu_music").fadeOutMusic(100); });
        fade->getComponent<FadeTransitionComponent>()->revert();
    }));

    pos = Vector2D(sdlutils().getWindowDimensions().getX() / 2, 5 * sdlutils().getWindowDimensions().getY() / 7);
    buttons.push_back(constructors::button(mngr_, pos, "Opciones", sdlutils().fonts().at("vcr_osd24"), [this]() {
        sdlutils().soundEffects().at("button").play(0, ecs::_channel_UI);
        fade->getComponent<FadeTransitionComponent>()->setFunction([](){ GameStateMachine::instance()->pushState(new OptionsMenuState());});
        fade->getComponent<FadeTransitionComponent>()->revert();
    }));

    pos = Vector2D(sdlutils().getWindowDimensions().getX() / 2, 6 * sdlutils().getWindowDimensions().getY() / 7);
    buttons.push_back(constructors::exitButton(mngr_, pos, []() {
        sdlutils().soundEffects().at("button").play(0, ecs::_channel_UI);
        sdlutils().musics().at("main_menu_music").haltMusic();
        game().exitGame();
    }));

    fade->getComponent<FadeTransitionComponent>()->activateWithoutExecute();
    playStateInit = false;

    sdlutils().musics().at("main_menu_music").play();

    buttonIndex = 0;
    formerIndex = 0;
    detectJoystickActivity = false;
}

void MainMenuState::update() {
    MenuState::update();
	if (SDL_GetTicks() >= animTime) {
		animFrame = (animFrame + 1) % 2;
        if(!playStateInit) littleOtt->getComponent<FramedImage>()->setCol(animFrame);
		animTime = SDL_GetTicks() + MAIN_MENU_OTT_ANIM_TIME;
	}
}

void MainMenuState::handleInput() {
    MenuState::handleInput();
    if (game().getIsJoystick()) {
        SDL_JoystickUpdate();
        if (SDL_JoystickGetAxis(game().getJoystick(), 1) <= 29000 && SDL_JoystickGetAxis(game().getJoystick(), 1) >= -29000 && !SDL_JoystickGetButton(game().getJoystick(), SDL_CONTROLLER_BUTTON_A)) detectJoystickActivity = true;
              
        if ((SDL_JoystickGetAxis(game().getJoystick(), 1) > 29000 && detectJoystickActivity)) {
            formerIndex = buttonIndex;
            buttonIndex++;
            buttonIndex %= buttons.size();
            detectJoystickActivity = false;
        }
        if (SDL_JoystickGetAxis(game().getJoystick(), 1) < -29000 && detectJoystickActivity) {
            formerIndex = buttonIndex;
            buttonIndex--;
            buttonIndex %= buttons.size();
            detectJoystickActivity = false;
        }
        if (SDL_JoystickGetButton(game().getJoystick(), SDL_CONTROLLER_BUTTON_A) && detectJoystickActivity) {
            buttons[buttonIndex]->getComponent<Button>()->onClick();
        }
             
        buttons[formerIndex]->getComponent<Button>()->unselect();
        buttons[buttonIndex]->getComponent<Button>()->select();
    }
}

void MainMenuState::changeResolution() {
    for(int i = 0; i < ecs::maxGroupId; ++i) {
        auto ents = mngr_->getEntities(i);
        for(auto e : ents) e->setAlive(false);
    }

    SDL_Color yellow{ 255,217,102 };
    Vector2D pos;

    constructors::background(mngr_, &sdlutils().images().at("mainmenubackground"));

    fade = mngr_->addEntity(ecs::_grp_FADEOUT);
    fade->addComponent<FadeTransitionComponent>(true);

    pos = Vector2D(sdlutils().getWindowDimensions().getX() / 2, 100);
    constructors::boldText(mngr_, "Ott: an Elemental Journey", pos, sdlutils().fonts().at("press_start48"), 5, yellow);

    pos = Vector2D(sdlutils().getWindowDimensions().getX() / 9, sdlutils().getWindowDimensions().getY() - 30);
    constructors::boldText(mngr_, "Fae Studios - 2023", pos, sdlutils().fonts().at("press_start16"), 1, yellow);

    pos = Vector2D(8.2 * sdlutils().getWindowDimensions().getX() / 9, sdlutils().getWindowDimensions().getY() - 30);
    constructors::boldText(mngr_, "Hito 2 - DEMO", pos, sdlutils().fonts().at("press_start16"), 1, yellow);

    littleOtt = mngr_->addEntity(ecs::_grp_UI);
    littleOtt->addComponent<Transform>(Vector2D(2*sdlutils().getWindowDimensions().getX()/10, 5.1*sdlutils().getWindowDimensions().getY()/10), 100, 100);
    littleOtt->addComponent<FramedImage>(&sdlutils().images().at("ott_luz"), 9, 8);

    pos = Vector2D(sdlutils().getWindowDimensions().getX() / 2, 3 * sdlutils().getWindowDimensions().getY() / 7);
    constructors::button(mngr_, pos, "Jugar", sdlutils().fonts().at("vcr_osd48"), [this]() {
#ifdef __APPLE__
        sdlutils().soundEffects().at("play_button").play(0, ecs::_channel_UI);
        fade->getComponent<FadeTransitionComponent>()->setFunction([this]() { GameStateMachine::instance()->changeState(new PlayState()); playStateInit = true; sdlutils().musics().at("main_menu_music").fadeOutMusic(100); });
        fade->getComponent<FadeTransitionComponent>()->revert();
#endif
#ifdef __WINDOWS__
        sdlutils().soundEffects().at("play_button").play(0, ecs::_channel_UI);
        fade->getComponent<FadeTransitionComponent>()->setFunction([]() { GameStateMachine::instance()->changeState(new PlayState()); sdlutils().musics().at("main_menu_music").fadeOutMusic(100);});
        fade->getComponent<FadeTransitionComponent>()->revert();
        playStateInit = true;
#endif
    });

    pos = Vector2D(sdlutils().getWindowDimensions().getX() / 2, 4 * sdlutils().getWindowDimensions().getY() / 7);
    constructors::button(mngr_, pos, "Cargar", sdlutils().fonts().at("vcr_osd48"), [this]() {
        sdlutils().soundEffects().at("button").play(0, ecs::_channel_UI);
        fade->getComponent<FadeTransitionComponent>()->setFunction([]() { GameStateMachine::instance()->changeState(new PlayState("../resources/saves/temporalUniqueSave.sv")); sdlutils().musics().at("main_menu_music").fadeOutMusic(100); });
        fade->getComponent<FadeTransitionComponent>()->revert();
    });

    pos = Vector2D(sdlutils().getWindowDimensions().getX() / 2, 5 * sdlutils().getWindowDimensions().getY() / 7);
    constructors::button(mngr_, pos, "Opciones", sdlutils().fonts().at("vcr_osd24"), [this]() {
        sdlutils().soundEffects().at("button").play(0, ecs::_channel_UI);
        fade->getComponent<FadeTransitionComponent>()->setFunction([](){ GameStateMachine::instance()->pushState(new OptionsMenuState());});
        fade->getComponent<FadeTransitionComponent>()->revert();
    });

    pos = Vector2D(sdlutils().getWindowDimensions().getX() / 2, 6 * sdlutils().getWindowDimensions().getY() / 7);
    constructors::exitButton(mngr_, pos, []() {
        sdlutils().soundEffects().at("button").play(0, ecs::_channel_UI);
        sdlutils().musics().at("main_menu_music").haltMusic();
        game().exitGame();
    });

    fade->getComponent<FadeTransitionComponent>()->activateWithoutExecute();
    playStateInit = false;

    stateMachine().resNotChangedAnymore();
}