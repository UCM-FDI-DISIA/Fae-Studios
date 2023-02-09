#include "MovingObject.h"
#include "../gameflow/GameState.h"

#pragma once
class Entity : public MovingObject
{
protected:
	uint life, maxLife;
	GameState* game;

public:
	Entity(Vector2D pos, Texture* texture, Vector2D dir, uint maxLife, GameState* game, Scale scale = Scale(1.0f, 1.0f)) :
		MovingObject(pos, texture, dir, scale), maxLife(maxLife), life(maxLife), game(game) {};
	virtual ~Entity() {};

	virtual void render() const {};
	virtual void update() {};
	bool collides();
	void stop();
	void start();
};