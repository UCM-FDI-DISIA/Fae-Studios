#include "MapState.h"
#include "PlayState.h"
#include "../components/PlayerAnimationComponent.h"

/// Constructora del estado de juego
MapState::MapState(PlayState* ps) : GameState(ecs::_state_MAP) {
	auto map = ps->getMap();
	int i = 0;
	Vector2D window = sdlutils().getWindowDimensions();
	auto ent = mngr_->addEntity(ecs::_grp_GENERAL);
	ent->addComponent<Transform>(0, 0, window.getX(), window.getY());
	ent->addComponent<Image>(&(sdlutils().images().at("mapBG")));
	if (ps->getCurrentMap() != ecs::WATER_BOSS_MAP && ps->getCurrentMap() != ecs::FINAL_BOSS_MAP) {
		std::string key = map->getMapKey(ps->getCurrentMap(), i);
		while (key != " " && key != "") {
			if (ps->isVisited(ps->getCurrentMap(), i)) {
				auto ent = mngr_->addEntity(ecs::_grp_GENERAL);
				ent->addComponent<Transform>(window.getX() / 8.5, window.getY() / 8, window.getX() - window.getX() / 8.5 * 2, window.getY() - window.getY() / 7 * 2);
				ent->addComponent<Image>(&(sdlutils().images().at(key)));
			}
			++i;
			key = map->getMapKey(ps->getCurrentMap(), i);
		}
	}
}

/// Destructora del estado de juego
MapState::~MapState() {

}

void MapState::update() {
	GameState::update();

	if (InputHandler::instance()->isKeyDown(SDLK_ESCAPE) || InputHandler::instance()->isKeyDown(SDLK_TAB)) {
		exit = true;
	}
	else if (exit && (InputHandler::instance()->isKeyUp(SDLK_ESCAPE) || InputHandler::instance()->isKeyUp(SDLK_TAB))) {
		GameStateMachine::instance()->popState();
		static_cast<PlayState*>(GameStateMachine::instance()->getPlayState())->getPlayer()->getComponent<PlayerAnimationComponent>()->setState(CLOSE_MAP);
		sdlutils().soundEffects().at("map").play(0, ecs::_channel_PLAYER);
	}
}