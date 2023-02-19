#include "MovingObject.h"
#include "../utils/Elements.h"


class PlayState;

#pragma once
class Entity : public MovingObject
{
protected:
	uint life, maxLife;
	PlayState* game;
	elementsInfo::elements currentElement;
	virtual void die();
	Vector2D speed;
	bool ground = false;
	bool dead = false;

public:
	list<Entity*>::iterator* physicsIterator = nullptr;
	Entity(Vector2D pos, Texture* texture, Vector2D dir, uint maxLife, PlayState* game, Scale scale = Scale(1.0f, 1.0f), elementsInfo::elements elem = elementsInfo::Light) :
		MovingObject(pos, texture, dir, scale), maxLife(maxLife), life(maxLife), game(game), currentElement(elem) {};
	virtual ~Entity() {};

	void useGravity();

	virtual void update() {};
	bool isGrounded();
	bool collides();
	void stop();
	void start();
	PlayState* getState() { return game; }
	virtual bool recieveDamage(elementsInfo::elements elem);
	inline void resetLives() { life = maxLife; }
	inline void addLive() { ++maxLife; }
	inline void subLive() { if (life == maxLife) --life; maxLife--; }
	inline int getCurrentElement() { return currentElement; }
	virtual void deleteMyself();
};