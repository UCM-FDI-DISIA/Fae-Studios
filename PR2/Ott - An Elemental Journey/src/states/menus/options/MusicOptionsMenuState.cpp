#include "../../../utils/checkML.h"
#include "MusicOptionsMenuState.h"
#include "../../GameStateMachine.h"
#include "../../../sdlutils/SDLUtils.h"
#include "../../../game/Constructors.h"

MusicOptionsMenuState::MusicOptionsMenuState() : MenuState() {
	Vector2D pos;
	constructors::background(mngr_, &sdlutils().images().at("playbackground"));
		
	pos = Vector2D(sdlutils().width() / 2, 2 * sdlutils().height() / 9);
	constructors::slider(mngr_, pos, "Volumen general", 0.0f, 100.0f, 100.0f, [this](int v) {
		generalVolume(v);
	});

	pos = Vector2D(sdlutils().width() / 2, 4 * sdlutils().height() / 9);
	constructors::slider(mngr_, pos, "Música", 0.0f, 100.0f, 100.0f, [this](int v) {
		musicVolume(v);
	});

	pos = Vector2D(sdlutils().width() / 2, 6 * sdlutils().height() / 9);
	constructors::slider(mngr_, pos, "Sonido", 0.0f, 100.0f, 100.0f, [this](int v) {
		soundsVolume(v);
	});

	pos = Vector2D(sdlutils().width() / 2, 6 * sdlutils().height() / 7);
	constructors::button(mngr_, pos, "Volver", sdlutils().fonts().at("vcr_osd48"), []() {
		GameStateMachine::instance()->popState();
	});

}


void MusicOptionsMenuState::generalVolume(int value) {
	//app->changeVolume(0, value);
}
void MusicOptionsMenuState::musicVolume(int value) {
	//app->changeVolume(1, value);
}
void MusicOptionsMenuState::soundsVolume(int value) {
	//app->changeVolume(2, value);
}