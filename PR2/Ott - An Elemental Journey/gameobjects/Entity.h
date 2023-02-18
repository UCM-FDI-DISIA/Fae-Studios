#include "MovingObject.h"


class PlayState;

#pragma once
class Entity : public MovingObject
{
protected:
	uint life, maxLife;
	PlayState* game;
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
	Vector2D speed;
	bool ground = false;

public:
	Entity(Vector2D pos, Texture* texture, Vector2D dir, uint maxLife, PlayState* game, Scale scale = Scale(1.0f, 1.0f)) :
		MovingObject(pos, texture, dir, scale), maxLife(maxLife), life(maxLife), game(game) {};
	virtual ~Entity() {};

	void useGravity();

	virtual void render() const {};
	virtual void update() {};
	bool isGrounded();
	bool collides();
	void stop();
	void start();
	virtual void recieveDamage(int elem);
	inline void resetLives() { life = maxLife; }
	inline void addLive() { ++maxLife; }
	inline void subLive() { if (life == maxLife) --life; maxLife--; }
	inline int getCurrentElement() { return currentElement; }
};