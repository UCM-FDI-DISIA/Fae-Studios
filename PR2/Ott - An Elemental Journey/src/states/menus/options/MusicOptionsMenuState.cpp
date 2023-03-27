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
	constructors::slider(mngr_, pos, "Volumen general de sonidos", 0.0f, 100.0f, SoundEffect::getMasterVolume() , [this](int v) {
		masterVolume(v);
	});
	
	pos = Vector2D(sdlutils().getWindowDimensions().getX() / 4, 4 * sdlutils().getWindowDimensions().getY() / 9);
	constructors::slider(mngr_, pos, "Música", 0.0f, 100.0f, Music::getMusicVolume(), [this](int v) {
		musicVolume(v);
	});

	pos = Vector2D(sdlutils().getWindowDimensions().getX() / 4, 6 * sdlutils().getWindowDimensions().getY() / 9);
	constructors::slider(mngr_, pos, "Interfaz", 0.0f, 100.0f, SoundEffect::getChannelVolume(ecs::_channel_UI), [this](int v) {
		uiVolume(v);
	});

	pos = Vector2D(3 * sdlutils().getWindowDimensions().getX() / 4, 2 * sdlutils().getWindowDimensions().getY() / 9);
	constructors::slider(mngr_, pos, "Jugador", 0.0f, 100.0f, SoundEffect::getChannelVolume(ecs::_channel_PLAYER), [this](int v) {
		playerVolume(v);
	});

	pos = Vector2D(3 * sdlutils().getWindowDimensions().getX() / 4, 4 * sdlutils().getWindowDimensions().getY() / 9);
	constructors::slider(mngr_, pos, "Enemigos", 0.0f, 100.0f, SoundEffect::getChannelVolume(ecs::_channel_ENEMY_SLIME), [this](int v) {
		enemiesVolume(v);
	});

	pos = Vector2D(3 * sdlutils().getWindowDimensions().getX() / 4, 6 * sdlutils().getWindowDimensions().getY() / 9);
	constructors::slider(mngr_, pos, "Misceláneo", 0.0f, 100.0f, SoundEffect::getChannelVolume(ecs::_channel_AMBIENTAL), [this](int v) {
		miscVolume(v);
	});

	pos = Vector2D(sdlutils().getWindowDimensions().getX() / 2, 6 * sdlutils().getWindowDimensions().getY() / 7);
	constructors::button(mngr_, pos, "Volver", sdlutils().fonts().at("vcr_osd48"), [this]() {
		sdlutils().soundEffects().at("button_back").play(0, ecs::_channel_UI);
		fade->getComponent<FadeTransitionComponent>()->setFunction([]() { GameStateMachine::instance()->popState(); });
		fade->getComponent<FadeTransitionComponent>()->revert();
	});

	fade->getComponent<FadeTransitionComponent>()->activateWithoutExecute();
}

void MusicOptionsMenuState::musicVolume(int value) {
	Music::setMusicVolume(value);
}
void MusicOptionsMenuState::uiVolume(int value) {
	SoundEffect::setChannelVolume(value, ecs::_channel_UI);
}
void MusicOptionsMenuState::playerVolume(int value) {
	SoundEffect::setChannelVolume(value, ecs::_channel_PLAYER);
}
void MusicOptionsMenuState::enemiesVolume(int value) {
	SoundEffect::setChannelVolume(value, ecs::_channel_ENEMY_SLIME);
	SoundEffect::setChannelVolume(value, ecs::_channel_ENEMY_RANGE);
	SoundEffect::setChannelVolume(value, ecs::_channel_ENEMY_MELEE);
	SoundEffect::setChannelVolume(value, ecs::_channel_EARTH_BOSS);
	SoundEffect::setChannelVolume(value, ecs::_channel_WATER_BOSS);
	SoundEffect::setChannelVolume(value, ecs::_channel_FIRE_BOSS);
}
void MusicOptionsMenuState::miscVolume(int value) {
	SoundEffect::setChannelVolume(value, ecs::_channel_AMBIENTAL);
	SoundEffect::setChannelVolume(value, ecs::_channel_ALERTS);
}
void MusicOptionsMenuState::masterVolume(int value) {
	SoundEffect::setMasterVolume(value);
}