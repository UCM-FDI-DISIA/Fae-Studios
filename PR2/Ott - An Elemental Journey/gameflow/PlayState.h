#pragma once
#include "../gameflow/GameState.h"
#include "../gameobjects/Enemy.h"
#include "../SDLApplication.h"
#include <iostream>

class PlayState : public GameState
{
private:
	Enemy* enemy;
	int i = 0;
public:
	PlayState(int stateID, SDLApplication* app) : GameState(stateID,app) {
		enemy = new Enemy(Vector2D(600, 400), app->getTexture("enemy", stateID), 5, elementsInfo::Earth, nullptr, false, Vector2D(1, 0), Scale(0.5, 0.5));
		gameObjects.push_back(enemy);
		enemy = new Enemy(Vector2D(300, 400), app->getTexture("enemy", stateID), 20, elementsInfo::Earth, enemy, true, Vector2D(1,0), Scale(0.5,0.5));
		gameObjects.push_back(enemy);

	}

	virtual void update() {
		GameState::update();
	}
};

