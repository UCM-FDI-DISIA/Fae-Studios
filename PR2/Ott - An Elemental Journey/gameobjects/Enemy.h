#pragma once
#include "Entity.h"
#include "../utils/Elements.h"
#include "../SDLApplication.h" //cosa para texturas desde enemy(?)
#include <iostream>
#include <cmath>

// MOVER ARCHIVOS Y COLOCAR BIEN
// CLASE TEMPORAL PARA PROBAR COSAS

class Enemy : public Entity{
protected:
	enum triggerState {normal, preparing, attacking, afterAttack, laying};

	int maxLives;
	int actualLives;
	elementsInfo::elements element;

	uint PREPARING_TIME = 1000;
	uint ATTACKING_TIME = 1000;
	uint DAMAGED_TIME = 1000;
	uint LAYING_TIME = 2000;

	uint NEW_DIR = 1000;
	int startAttackingTime = 0;
	int startMovingTime = 0;
	int startDamagedTime = 0;
	int turningError = 1;
	double turningOffset = 0.75; // entre 0 y 1
	SDL_Rect attackTrigger;
	triggerState attackState;
	SDL_Rect detectingTrigger;
	bool detectPlayer;
	bool movee = true;;  // TEMPORAL PARA PRUEBAS, BORRAR TODO LO RELACIONADO CON ESTO
	bool lookingRight = true;
	int nearDistance = 10;
	bool grounded = false;

	float horizontalSpeed = 1, verticalSpeed = 1;

	GameObject* player;
	SDL_Rect collider;
	SDL_Rect groundCollider;

	Vector2D colliderOffset;
	Vector2D colliderWH; // width height

	const int time_per_frame = 140;
	SDL_RendererFlip flip[2] = { SDL_FLIP_NONE, SDL_FLIP_HORIZONTAL };
	int col = 0;
	int timer = 0;
	int fil = 0;

	Texture* colliderRender;
public:
	Enemy(const Vector2D& position, Texture* texture, int lives, elementsInfo::elements elem, GameObject* p, bool moving, PlayState* game, Vector2D dir = Vector2D(0,0), const Scale& scale = Scale(1.0f, 1.0f), float wTrigger = 110, float hTrigger = 100, Texture* colliderDEBUG = nullptr);
	virtual ~Enemy() = default;

	virtual void die();

	void DetectPlayer();

	virtual void FollowPlayer();

	virtual void update();

	virtual void Move();

	int GetLives();

	bool isDead();

	virtual void Attack();

	virtual void DetectAttackTrigger();

	virtual bool recieveDamage(elementsInfo::elements elem);

	void playerCollide();

	void useGravity();

	virtual void MoveTriggers();

	virtual void ChangeDir(const SDL_Rect& result); // Bordes de plataformas, no paredes

	SDL_Rect getCollider() const{ 
		SDL_Rect collider = { (position.getX() + colliderOffset.getX()), (position.getY() + colliderOffset.getY()),
								colliderWH.getX(), colliderWH.getY() };
		return collider;
	}

	virtual void render(const SDL_Rect& Camera = { 0,0,0,0 }) const;
};


