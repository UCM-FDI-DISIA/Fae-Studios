#include "MovingObject.h"
#include "../gameflow/GameState.h"

#pragma once
class Entity : public MovingObject
{
protected:
	uint life, maxLife;
	GameState* game;
	enum Elements{Luz,Agua,Tierra,Fuego,Oscuridad};
	int elementsInfo [5][5] = {
		{ 1, 1, 1, 1, 1 },
		{ 1, 1, 2, 0, -1 },
		{ 1, 0, 1, 2, -1 },
		{ 1, 2, 0, 1, -1 },
		{ 1, 2, 2, 2, 1 }
	};
	int currentElement = Luz;
	virtual void die();

public:
	Entity(Vector2D pos, Texture* texture, Vector2D dir, uint maxLife, GameState* game, Scale scale = Scale(1.0f, 1.0f)) :
		MovingObject(pos, texture, dir, scale), maxLife(maxLife), life(maxLife), game(game) {};
	virtual ~Entity() {};

	virtual void render() const {};
	virtual void update() {};
	bool collides();
	void stop();
	void start();
	virtual void recieveDamage(int elem);
	inline void resetLives() { life = maxLife; }
	inline void addLive() { ++maxLife; }
	inline void subLive() { if (life == maxLife) --life; maxLife--; }
	inline int getCurrentElement() { return currentElement; }
};