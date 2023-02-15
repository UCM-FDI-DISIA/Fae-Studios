#include "CollisionObject.h"
#include "../gameflow/play/PlayState.h"
#pragma once

class InteractuableObject : public CollisionObject
{
protected:
	PlayState* game;
public:
	InteractuableObject(Vector2D position, Texture* texture, PlayState* game, Scale scale = Scale(1.0f, 1.0f)) : CollisionObject(position, texture, scale), game(game) {};
	virtual void interact() = 0;
	virtual bool collide(const SDL_Rect& obj, SDL_Rect& result);
};

class TP_Lamp : public InteractuableObject {
private:
	TP_Lamp* pairedLamp;
public:
	TP_Lamp(Vector2D position, Texture* texture, PlayState* game, Scale scale = Scale(1.0f, 1.0f)) : InteractuableObject(position, texture, game, scale) {};
	void SetLamp(TP_Lamp* pair) { pairedLamp = pair; };
	virtual void interact();
};

class Enredaderas: public CollisionObject{
private:
	
public:
	Enredaderas(Vector2D position, Texture* texture, PlayState* game, Scale scale = Scale(1.0f, 1.0f)) : CollisionObject(position, texture, scale){}
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

public:
	Grass(Vector2D position, Texture* texture, PlayState* game, Scale scale, float eH) : InteractuableObject(position, texture, game, scale){};
	virtual void interact() {
		if (!withEnredadera) {
			game->addEnredadera(position);
			withEnredadera = true;
		}
	}
};