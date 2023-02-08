#pragma once
#include "gameflow/GameState.h"
#include "Enemy.h"
#include "SDLApplication.h"
#include <iostream>


class PlayState : public GameState
{
private:
	Enemy* enemy;
public:
	PlayState(int stateID, SDLApplication* app) : GameState(stateID,app) {
		
		gameObjects.push_back(new Enemy(Vector2D(400, 400), app->getTexture("enemy", stateID), 10, elementsInfo::Earth));
	}

	virtual void update() {
		GameState::update();
		for (int i = 0; i < elementsInfo::numElems; ++i) {
			std::cout << "ActualLives = " + enemy->GetLives();
		}
	}
};

