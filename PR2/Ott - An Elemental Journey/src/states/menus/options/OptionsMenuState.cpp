#include "../../../utils/checkML.h"
#include "OptionsMenuState.h"
#include "../../GameStateMachine.h"
#include "MusicOptionsMenuState.h"
#include "ControlMenuState.h"
#include <iostream>
#include "../../../sdlutils/SDLUtils.h"
#include "../../../game/Constructors.h"
#include "../../../components/FadeTransitionComponent.h"

OptionsMenuState::OptionsMenuState() : MenuState() {
	Vector2D pos;
	const SDL_Color yellow{ 255,217,102 };
	
	constructors::background(mngr_, &sdlutils().images().at("playbackground"));

	fade = mngr_->addEntity(ecs::_grp_FADEOUT);
	fade->addComponent<FadeTransitionComponent>(true);
	
	pos = Vector2D((sdlutils().width()) / 2, 100);
	constructors::boldText(mngr_, "Opciones", pos, sdlutils().fonts().at("press_start48"), 5, yellow);

	pos = Vector2D(sdlutils().width() / 2, 3 * sdlutils().height() / 7);
	constructors::button(mngr_, pos, "Gráficos", sdlutils().fonts().at("vcr_osd24"), []() {
		sdlutils().soundEffects().at("button").play(0, ecs::_channel_UI);
		std::cout << "opciones graficas" << std::endl;
	});

	pos = Vector2D(sdlutils().width() / 2, 4 * sdlutils().height() / 7);
	constructors::button(mngr_, pos, "Música y sonidos", sdlutils().fonts().at("vcr_osd16"), [this]() {
		sdlutils().soundEffects().at("button").play(0, ecs::_channel_UI);
		fade->getComponent<FadeTransitionComponent>()->setFunction([]() { GameStateMachine::instance()->pushState(new MusicOptionsMenuState()); });
		fade->getComponent<FadeTransitionComponent>()->revert();
	});

	pos = Vector2D(sdlutils().width() / 2, 5 * sdlutils().height() / 7);
	constructors::button(mngr_, pos, "Controles", sdlutils().fonts().at("vcr_osd24"), [this]() {
		sdlutils().soundEffects().at("button").play(0, ecs::_channel_UI);
		fade->getComponent<FadeTransitionComponent>()->setFunction([]() { GameStateMachine::instance()->pushState(new ControlMenuState()); });
		fade->getComponent<FadeTransitionComponent>()->revert();
	});

	pos = Vector2D(sdlutils().width() / 2, 6 * sdlutils().height() / 7);
	constructors::button(mngr_, pos, "Volver", sdlutils().fonts().at("vcr_osd48"), [this]() {
		sdlutils().soundEffects().at("button_back").play(0, ecs::_channel_UI);
		fade->getComponent<FadeTransitionComponent>()->setFunction([]() { GameStateMachine::instance()->popState(); });
		fade->getComponent<FadeTransitionComponent>()->revert();
	});

	fade->getComponent<FadeTransitionComponent>()->activateWithoutExecute();
}