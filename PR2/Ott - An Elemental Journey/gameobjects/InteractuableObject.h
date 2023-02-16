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

class Enredaderas : public InteractuableObject {
private:
	
public:
	Enredaderas(Vector2D position, Texture* texture, PlayState* game, Scale scale = Scale(1.0f, 1.0f)): InteractuableObject(position, texture, game, scale) {};
	virtual void interact() {
		game->climb();
	}
	//bool isActive() { return active; }
};

class Grass : public InteractuableObject {
private :
	bool withEnredadera = false;
	float heightEnredadera;
	float widthEnredadera = 0.05f;
public:
	Grass(Vector2D position, Texture* texture, PlayState* game, Scale scale, float eH) : InteractuableObject(position, texture, game, scale), heightEnredadera(eH){};
	virtual void interact() {
		if (!withEnredadera) {
			game->addEnredadera(Vector2D(position.getX(), position.getY()-200),Scale(widthEnredadera,heightEnredadera));
			withEnredadera = true;
		}
	}
};