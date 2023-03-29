#include "../../../utils/checkML.h"
#include "MusicOptionsMenuState.h"
#include "../../GameStateMachine.h"
#include "../../../sdlutils/SDLUtils.h"
#include "../../../game/Constructors.h"
#include "../../../components/FadeTransitionComponent.h"
#include "../../../sdlutils/SoundEffect.h"

MusicOptionsMenuState::MusicOptionsMenuState() : MenuState() {
	Vector2D pos;
	constructors::background(mngr_, &sdlutils().images().at("playbackground"));

	fade = mngr_->addEntity(ecs::_grp_FADEOUT);
	fade->addComponent<FadeTransitionComponent>(true);
		
	pos = Vector2D(sdlutils().getWindowDimensions().getX() / 4, 2 * sdlutils().getWindowDimensions().getY() / 9);
	constructors::slider(mngr_, pos, "Volumen general", 0.0f, 100.0f, 100.0f, [this](int v) {
		generalVolume(v);
	});

	pos = Vector2D(sdlutils().getWindowDimensions().getX() / 4, 4 * sdlutils().getWindowDimensions().getY() / 9);
	constructors::slider(mngr_, pos, "Música", 0.0f, 100.0f, 100.0f, [this](int v) {
		musicVolume(v);
	});

	pos = Vector2D(sdlutils().getWindowDimensions().getX() / 4, 6 * sdlutils().getWindowDimensions().getY() / 9);
	constructors::slider(mngr_, pos, "Sonido general", 0.0f, 100.0f, 100.0f, [this](int v) {
		soundsVolume(v);
	});

	pos = Vector2D(3 * sdlutils().getWindowDimensions().getX() / 4, 2 * sdlutils().getWindowDimensions().getY() / 9);
	constructors::slider(mngr_, pos, "Interfaz", 0.0f, 100.0f, SoundEffect::getChannelVolume(ecs::_channel_UI), [this](int v) {
		uiVolume(v);
	});

	pos = Vector2D(sdlutils().getWindowDimensions().getX() / 2, 6 * sdlutils().getWindowDimensions().getY() / 7);
	constructors::button(mngr_, pos, "Volver", sdlutils().fonts().at("vcr_osd48"), [this]() {
		sdlutils().soundEffects().at("button_back").play(0, ecs::_channel_UI);
		fade->getComponent<FadeTransitionComponent>()->setFunction([]() { GameStateMachine::instance()->popState(); });
		fade->getComponent<FadeTransitionComponent>()->revert();
	});

	fade->getComponent<FadeTransitionComponent>()->activateWithoutExecute();
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
void MusicOptionsMenuState::uiVolume(int value) {
	SoundEffect::setChannelVolume(value, ecs::_channel_UI);
}