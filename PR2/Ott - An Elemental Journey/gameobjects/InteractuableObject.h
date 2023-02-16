#include "CollisionObject.h"
#include "../gameflow/play/PlayState.h"
#pragma once

class InteractuableObject : public CollisionObject
{
protected:
	PlayState* game;
public:
	InteractuableObject(Vector2D position, Texture* texture, PlayState* game, Scale scale = Scale(1.0f, 1.0f), GO_TYPE type = DEFAULT) : CollisionObject(position, texture, scale, type), game(game) {};
	virtual void interact() = 0;
	virtual bool collide(const SDL_Rect& obj, SDL_Rect& result);
};

class TP_Lamp : public InteractuableObject {
private:
	TP_Lamp* pairedLamp;
	bool canTP = false;
	const uint MAX_TIME = 300;
	uint timer = MAX_TIME;
public:
	TP_Lamp(Vector2D position, Texture* texture, PlayState* game, Scale scale = Scale(1.0f, 1.0f), GO_TYPE type = DEFAULT) : InteractuableObject(position, texture, game, scale, type) {};
	virtual bool collide(const SDL_Rect& obj, SDL_Rect& result);
	void SetLamp(TP_Lamp* pair) { pairedLamp = pair; };
	virtual void interact();
	virtual void update();
};

class Enredaderas: public CollisionObject{
private:
	
public:
	Enredaderas(Vector2D position, Texture* texture, PlayState* game, Scale scale = Scale(1.0f, 1.5f)) : CollisionObject(position, texture, scale){}
	bool collide(const SDL_Rect& obj, SDL_Rect& result) {
		const SDL_Rect rect = getRect();
		SDL_Rect aux = obj;
		aux.y += aux.h;
		return SDL_IntersectRect(&obj, &rect, &result);

	}
};

class Grass : public InteractuableObject {
private :
	bool withEnredadera = false;
	Vector2D position;

public:
	Grass(Vector2D position, Texture* texture, PlayState* game, Scale scale = Scale(1.0f, 1.0f)) : InteractuableObject(position, texture, game, scale), position(position) {};
	virtual void interact() {
		if (!withEnredadera) {
			game->addEnredadera(position);
			withEnredadera = true;
		}
	}
};