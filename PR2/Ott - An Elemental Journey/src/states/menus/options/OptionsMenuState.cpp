#include "../../../utils/checkML.h"
#include "OptionsMenuState.h"
#include "../../GameStateMachine.h"
#include "MusicOptionsMenuState.h"
#include "ControlMenuState.h"
#include <iostream>
#include "../../../sdlutils/SDLUtils.h"
#include "../../../game/Constructors.h"

OptionsMenuState::OptionsMenuState() : MenuState() {
	Vector2D pos;
	const SDL_Color yellow{ 255,217,102 };
	
	constructors::background(mngr_, &sdlutils().images().at("playbackground"));
	
	pos = Vector2D((sdlutils().width()) / 2, 100);
	constructors::boldText(mngr_, "Opciones", pos, sdlutils().fonts().at("press_start48"), 5, yellow);

	pos = Vector2D(sdlutils().width() / 2, 3 * sdlutils().height() / 7);
	constructors::button(mngr_, pos, "Gráficos", sdlutils().fonts().at("vcr_osd24"), []() {
			std::cout << "opciones graficas" << std::endl;
	});

	pos = Vector2D(sdlutils().width() / 2, 4 * sdlutils().height() / 7);
	constructors::button(mngr_, pos, "Música y sonidos", sdlutils().fonts().at("vcr_osd16"), []() {
			GameStateMachine::instance()->pushState(new MusicOptionsMenuState());
	});

	pos = Vector2D(sdlutils().width() / 2, 5 * sdlutils().height() / 7);
	constructors::button(mngr_, pos, "Controles", sdlutils().fonts().at("vcr_osd24"), []() {
		GameStateMachine::instance()->pushState(new ControlMenuState());
	});

	pos = Vector2D(sdlutils().width() / 2, 6 * sdlutils().height() / 7);
	constructors::button(mngr_, pos, "Volver", sdlutils().fonts().at("vcr_osd48"), []() {
		GameStateMachine::instance()->popState();
	});
}