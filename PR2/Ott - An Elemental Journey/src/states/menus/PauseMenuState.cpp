#include "../../utils/checkML.h"
#include "PauseMenuState.h"
#include "../GameStateMachine.h"
#include "../../components/Button.h"
#include "MainMenuState.h"
#include "options/OptionsMenuState.h"
#include "../../sdlutils/InputHandler.h"
#include "../../sdlutils/SDLUtils.h"
#include "../../game/Constructors.h"
#include "../../game/Game.h"

PauseMenuState::PauseMenuState() : MenuState() {
	SDL_Color yellow{ 255,217,102 };
	Vector2D pos;

	constructors::background(mngr_, &sdlutils().images().at("playbackground"));

	fade = mngr_->addEntity(ecs::_grp_FADEOUT);
	fade->addComponent<FadeTransitionComponent>(true);
	fade->getComponent<FadeTransitionComponent>()->activateWithoutExecute();

	pos = Vector2D(sdlutils().getWindowDimensions().getX() / 2, 100);
	constructors::boldText(mngr_, "Pausa", pos, sdlutils().fonts().at("press_start48"), 5, yellow);

	pos = Vector2D(sdlutils().getWindowDimensions().getX() / 2, 3 * sdlutils().getWindowDimensions().getY() / 7);
	buttons.push_back(constructors::button(mngr_, pos, "Continuar", sdlutils().fonts().at("vcr_osd24"), [this]() {
		sdlutils().soundEffects().at("button").play(0, ecs::_channel_UI);
		fade->getComponent<FadeTransitionComponent>()->setFunction([]() { GameStateMachine::instance()->popState(); });
		fade->getComponent<FadeTransitionComponent>()->revert();
	}));

	pos = Vector2D(sdlutils().getWindowDimensions().getX() / 2, 4 * sdlutils().getWindowDimensions().getY() / 7);
	buttons.push_back(constructors::button(mngr_, pos, "Menú principal", sdlutils().fonts().at("vcr_osd16"), [this]() {
		sdlutils().soundEffects().at("button").play(0, ecs::_channel_UI);
		fade->getComponent<FadeTransitionComponent>()->setFunction([]() { GameStateMachine::instance()->resetStack(); });
		fade->getComponent<FadeTransitionComponent>()->revert();
	}));

	pos = Vector2D(sdlutils().getWindowDimensions().getX() / 2, 5 * sdlutils().getWindowDimensions().getY() / 7);
	buttons.push_back(constructors::button(mngr_, pos, "Opciones", sdlutils().fonts().at("vcr_osd24"), [this]() {
		sdlutils().soundEffects().at("button").play(0, ecs::_channel_UI);
		fade->getComponent<FadeTransitionComponent>()->setFunction([]() { GameStateMachine::instance()->pushState(new OptionsMenuState()); });
		fade->getComponent<FadeTransitionComponent>()->revert();
	}));

	pos = Vector2D(sdlutils().getWindowDimensions().getX() / 2, 6 * sdlutils().getWindowDimensions().getY() / 7);
	buttons.push_back(constructors::exitButton(mngr_, pos, []() {
		sdlutils().soundEffects().at("button").play(0, ecs::_channel_UI);
		game().exitGame();
	}));

	buttonIndex = 0;
	formerIndex = 0;
	detectJoystickActivity = false;
}

void PauseMenuState::handleInput() {
	MenuState::handleInput();
	
	//Bloqueamos la entrada de teclado hasta que se dejen de pulsar todas las teclas
	if (doNotDetectKeyboardInput && InputHandler::instance()->allKeysUp()) doNotDetectKeyboardInput = false;

	//Si presionamos el espacio, volvemos al juego
	if (!doNotDetectKeyboardInput) {
		if (InputHandler::instance()->isKeyJustDown(SDLK_ESCAPE)) {
			dynamic_cast<PlayState*>(GameStateMachine::instance()->getPlayState())->blockKeyboardInputAfterUnfreeze();
			fade->getComponent<FadeTransitionComponent>()->setFunction([]() { GameStateMachine::instance()->popState(); });
			fade->getComponent<FadeTransitionComponent>()->revert();
			doNotDetectKeyboardInput = true;
		}
	}

	if (game().getIsJoystick()) {
		SDL_GameControllerUpdate();
		if (SDL_GameControllerGetAxis(game().getJoystick(), SDL_CONTROLLER_AXIS_LEFTY) <= 29000 && SDL_GameControllerGetAxis(game().getJoystick(), SDL_CONTROLLER_AXIS_LEFTY) >= -29000 && !SDL_GameControllerGetButton(game().getJoystick(), SDL_CONTROLLER_BUTTON_A)) detectJoystickActivity = true;

		if ((SDL_GameControllerGetAxis(game().getJoystick(), SDL_CONTROLLER_AXIS_LEFTY) > 29000 && detectJoystickActivity)) {
			formerIndex = buttonIndex;
			buttonIndex++;
			buttonIndex %= buttons.size();
			detectJoystickActivity = false;
		}
		if (SDL_GameControllerGetAxis(game().getJoystick(), SDL_CONTROLLER_AXIS_LEFTY) < -29000 && detectJoystickActivity) {
			formerIndex = buttonIndex;
			buttonIndex--;
			buttonIndex %= buttons.size();
			detectJoystickActivity = false;
		}
		if (SDL_GameControllerGetButton(game().getJoystick(), SDL_CONTROLLER_BUTTON_A) && detectJoystickActivity) {
			buttons[buttonIndex]->getComponent<Button>()->onClick();
		}

		buttons[formerIndex]->getComponent<Button>()->unselect();
		buttons[buttonIndex]->getComponent<Button>()->select();
	}
}