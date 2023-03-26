#include "../../../utils/checkML.h"
#include "MusicOptionsMenuState.h"
#include "../../GameStateMachine.h"
#include "../../../sdlutils/SDLUtils.h"
#include "../../../game/Constructors.h"
#include "../../../components/FadeTransitionComponent.h"
#include "../../../sdlutils/SoundEffect.h"
#include "../../../sdlutils/Music.h"

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
	constructors::slider(mngr_, pos, "Música", 0.0f, 100.0f, Music::getMusicVolume(), [this](int v) {
		musicVolume(v);
	});

	pos = Vector2D(sdlutils().getWindowDimensions().getX() / 4, 6 * sdlutils().getWindowDimensions().getY() / 9);
	constructors::slider(mngr_, pos, "Sonido general", 0.0f, 100.0f, SoundEffect::getGeneralSoundsVolume(), [this](int v) {
		//soundsVolume(v);
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
	Music::setMusicVolume(value);
}
void MusicOptionsMenuState::soundsVolume(int value) {
	/*SoundEffect::setGeneralSoundsVolume(value);
	int vol = (int)((float)(SoundEffect::getChannelVolume(ecs::_channel_UI)) * (float)((float)(value) / 100));
	SoundEffect::setChannelVolume(vol, ecs::_channel_UI);
	SoundEffect::setChannelVolume((int)((float)(SoundEffect::getChannelVolume(ecs::_channel_PLAYER_ATTACK)) * (float)((float)(value) / 100)), ecs::_channel_PLAYER_ATTACK);
	SoundEffect::setChannelVolume((int)((float)(SoundEffect::getChannelVolume(ecs::_channel_PLAYER_MOVEMENT)) * (float)((float)(value) / 100)), ecs::_channel_PLAYER_MOVEMENT);
	SoundEffect::setChannelVolume((int)((float)(SoundEffect::getChannelVolume(ecs::_channel_AMBIENTAL)) * (float)((float)(value) / 100)), ecs::_channel_AMBIENTAL);
	SoundEffect::setChannelVolume((int)((float)(SoundEffect::getChannelVolume(ecs::_channel_ALERTS)) * (float)((float)(value) / 100)), ecs::_channel_ALERTS);
	SoundEffect::setChannelVolume((int)((float)(SoundEffect::getChannelVolume(ecs::_channel_ENEMY_ATTACK)) * (float)((float)(value) / 100)), ecs::_channel_ENEMY_ATTACK);
	SoundEffect::setChannelVolume((int)((float)(SoundEffect::getChannelVolume(ecs::_channel_ENEMY_MOVEMENT)) * (float)((float)(value) / 100)), ecs::_channel_ENEMY_MOVEMENT);*/
}
void MusicOptionsMenuState::uiVolume(int value) {
	SoundEffect::setChannelVolume(value, ecs::_channel_UI);
}