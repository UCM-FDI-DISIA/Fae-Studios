#include "MapState.h"
#include "PlayState.h"

/// Constructora del estado de juego
MapState::MapState(PlayState* ps) : GameState(ecs::_state_MAP) {
	auto map = ps->getMap();
	int i = 0;
	Vector2D window = sdlutils().getWindowDimensions();
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
		GameStateMachine::instance()->popState();
	}
}