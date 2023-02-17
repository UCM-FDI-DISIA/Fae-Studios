#pragma once
#include "../gameflow/GameState.h"
#include "../gameobjects/MeleeEnemy.h"
#include "../gameobjects/Bullet.h"
#include "../SDLApplication.h"
#include "../gameobjects/staticEnemy.h"
#include "../gameobjects/SlimeEnemy.h"
#include "../gameobjects/Physics/Ground.h"
#include <iostream>

class PlayState : public GameState
{
private:
	Enemy* enemy;
	staticEnemy* enemy2;
	int i = 0;
	double gravity = 0.08f;

	list<CollisionObject*> groundObjects;
	list<Enemy*> physicObjects;
	list<CollisionObject*> wallObjects;


public:
	PlayState(int stateID, SDLApplication* app) : GameState(stateID,app) {
		/*enemy2 = static_cast<staticEnemy*> (addObject(new staticEnemy(Vector2D(300, 400), app->getTexture("enemy", stateID), enemy, 2000, 5, elementsInfo::Earth, 10 * app->getTexture("enemy", stateID)->getH(), app->getTexture("enemy", stateID)->getH(), Scale(0.5f, 0.5f), this)));*/
		Ground* ground;
		enemy = static_cast<SlimeEnemy*> (addObject(new SlimeEnemy(3, Vector2D(370, 400), app->getTexture("enemy", stateID), 5, elementsInfo::Earth, nullptr, false, Vector2D(1, 0), Scale(0.5, 0.5), 110, this)));
		physicObjects.push_back(enemy);
		enemy = static_cast<MeleeEnemy*> (addObject(new MeleeEnemy(Vector2D(300, 400), app->getTexture("enemy", stateID), 5, elementsInfo::Earth, enemy, true, Vector2D(1, 0), Scale(0.5, 0.5), 110, this)));
		physicObjects.push_back(enemy);
		//enemy = static_cast<MeleeEnemy*> (addObject(new MeleeEnemy(Vector2D(300, 100), app->getTexture("enemy", stateID), 5, elementsInfo::Earth, enemy, true, Vector2D(1, 0), Scale(0.5, 0.5), 110, this)));
		//physicObjects.push_back(enemy);
		ground = static_cast<Ground*> (addObject(new Ground(Vector2D(0, 500), app->getTexture("whiteBox", stateID), Scale(0.4, 1))));
		groundObjects.push_back(ground);
		wallObjects.push_back(static_cast<CollisionObject*> (ground));
		ground = static_cast<Ground*> (addObject(new Ground(Vector2D(0, 550), app->getTexture("whiteBox", stateID), Scale(0.5, 1))));
		groundObjects.push_back(ground);
		Wall* wall;
		wall = static_cast<Wall*> (addObject(new Wall(Vector2D(0, 400), app->getTexture("whiteBox", stateID), Scale(0.1, 1))));
		wallObjects.push_back(wall);
	}

	virtual ~PlayState() = default;

	virtual void update() {
		GameState::update();
	}

	void addBullet(Vector2D pos, Vector2D dir, elementsInfo::elements elem, GameObject* g) {
		addObject(new Bullet(pos, app->getTexture("enemy", stateID), elem, g, dir, Scale(0.1f, 0.1f), this));
	}

	void enemyCollidesGround(const SDL_Rect& enemy, SDL_Rect& result, bool& grounded) {
		grounded = false;
		for (auto it = groundObjects.begin(); it != groundObjects.end() && !grounded; ++it) {
			grounded = (*it)->collide(enemy, result);
		}
	}

	void enemyCollidesWall(const SDL_Rect& enemy, SDL_Rect& result, bool& collided) {
		for (auto it = wallObjects.begin(); it != wallObjects.end() && !collided; ++it) {
			collided = (*it)->collide(enemy, result);
		}
	}

	inline double Gravity() { return gravity; };

	void addEnemy(GameObject* g) {
		enemy = static_cast<Enemy*> (addObject(g));
		physicObjects.push_back(enemy);
	}

};

