#include "MapState.h"
#include "PlayState.h"

/// Constructora del estado de juego
MapState::MapState(PlayState* ps) : GameState(ecs::_state_MAP) {
	auto map = ps->getMap();
	int i = 0;
	Vector2D window = sdlutils().getWindowDimensions();
	auto ent = mngr_->addEntity(ecs::_grp_GENERAL);
	ent->addComponent<Transform>(0, 0, window.getX(), window.getY());
	ent->addComponent<Image>(&(sdlutils().images().at("mapBG")));
	std::string key = map->getMapKey(i);
	while (key != " ") {
		if (ps->isVisited(i)) {
			auto ent = mngr_->addEntity(ecs::_grp_GENERAL);
			ent->addComponent<Transform>(0, 0, window.getX(), window.getY());
			ent->addComponent<Image>(&(sdlutils().images().at(key)));
		}
		++i;
		key = map->getMapKey(i);
	}
}

/// Destructora del estado de juego
MapState::~MapState() {

}

void MapState::update() {
	GameState::update();

	if (InputHandler::instance()->isKeyDown(SDLK_ESCAPE)) {
		exit = true;
	}
	else if (InputHandler::instance()->isKeyUp(SDLK_ESCAPE) && exit) {
		GameStateMachine::instance()->popState();
	}
}