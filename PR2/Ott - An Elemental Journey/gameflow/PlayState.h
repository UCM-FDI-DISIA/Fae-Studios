#pragma once
#include "../gameflow/GameState.h"
#include "../gameobjects/MeleeEnemy.h"
#include "../gameobjects/Bullet.h"
#include "../SDLApplication.h"
#include "../gameobjects/staticEnemy.h"
#include <iostream>

class PlayState : public GameState
{
private:
	Enemy* enemy;
	staticEnemy* enemy2;
	int i = 0;
public:
	PlayState(int stateID, SDLApplication* app) : GameState(stateID,app) {
		enemy = static_cast<MeleeEnemy*> (addObject(new MeleeEnemy(Vector2D(600, 400), app->getTexture("enemy", stateID), 5, elementsInfo::Earth, nullptr, false, Vector2D(1, 0), Scale(0.5, 0.5), 110, this)));
		enemy = static_cast<MeleeEnemy*> (addObject(new MeleeEnemy(Vector2D(100, 400), app->getTexture("enemy", stateID), 5, elementsInfo::Earth, enemy, true, Vector2D(1, 0), Scale(0.5, 0.5), 110, this)));
		enemy2 = static_cast<staticEnemy*> (addObject(new staticEnemy(Vector2D(300, 400), app->getTexture("enemy", stateID), enemy, 2000, 5, elementsInfo::Earth, 10 * app->getTexture("enemy", stateID)->getH(), app->getTexture("enemy", stateID)->getH(), Scale(0.5f, 0.5f), this)));
	}

	virtual ~PlayState() = default;

	virtual void update() {
		GameState::update();
	}

	void addBullet(Vector2D pos, Vector2D dir, elementsInfo::elements elem, GameObject* g) {
		addObject(new Bullet(pos, app->getTexture("enemy", stateID), elem, g, dir, Scale(0.1f, 0.1f), this));
	}
};

