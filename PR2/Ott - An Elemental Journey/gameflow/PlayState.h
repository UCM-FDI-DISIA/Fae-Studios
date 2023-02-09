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
		enemy = new Enemy(Vector2D(400, 400), app->getTexture("enemy", stateID), 20, elementsInfo::Earth);
		gameObjects.push_back(enemy);
	}

	virtual void update() {
		GameState::update();
		if (!enemy->isDead()) {
			std::cout << elementsInfo::matrix[0][0] << endl;
			std::cout << "Lives = " + to_string(enemy->GetLives())<< endl;
			enemy->Damage(elementsInfo::elements(i));
			std::cout << "ActualLives = " + to_string(enemy->GetLives()) << endl;
			i = (i + 1) % elementsInfo::numElems;
		}
	}
};

