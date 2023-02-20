#pragma once
#include "Enemy.h"

class SlimeEnemy : public Enemy
{
	enum size { big=3, medium=2, small=1 };
protected:
	int col;
	float slimeScale = 0;
	int actualSize = big;
	SDL_Rect damageZone = {0,0,0,0};

	bool layDown = false;
	bool getUp = true;

	void Divide();
	void layDownAdjust();
	void getUpAdjust();
public:
	SlimeEnemy(int size, const Vector2D& position, Texture* texture, int lives, elementsInfo::elements elem, GameObject* p,
		bool moving, Vector2D dir = Vector2D(0, 0), const Scale& scale = Scale(1.0f, 1.0f), float wTrigger = 110.0f, float hTrigger = 100, PlayState* state = nullptr, Texture* colliderDEBUG = nullptr) :
		Enemy(position, texture, lives, elem, p, moving, state, dir, scale, wTrigger, hTrigger, colliderDEBUG) 
	{
		slimeScale = scale.widthScale;
		actualSize = size;

		colliderOffset = { (double)(width * 0.44), (double)(height * 0.1) };
		colliderWH = { (double)(width * 0.16), (double)(height * 0.9) };
		damageZone.y = position.getY(); damageZone.x = position.getX(); damageZone.w = width; damageZone.h = height / actualSize;

		SDL_Rect collider = getCollider();

		attackTrigger.x = collider.x + collider.h; attackTrigger.y = collider.y;
		attackTrigger.w = collider.h; attackTrigger.h = collider.h;
		attackState = normal;
		uint NEW_DIR = 5000;

		nearDistance = colliderWH.getY();
	};
	
	virtual void update();
	virtual void Move();
	virtual void DetectAttackTrigger(); // probably va a ser un render frame con el bicho cayendose cuando este en Attack_Time
	virtual bool recieveDamage(/*const SDL_Rect& playerAttack, */elementsInfo::elements e);
	virtual void die();
	virtual void render(const SDL_Rect& Camera = { 0,0,0,0 }) const;

};

