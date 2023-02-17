#pragma once
#include "Enemy.h"

class SlimeEnemy : public Enemy
{
	enum size { big=3, medium=2, small=1 };
protected:
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
		bool moving, Vector2D dir = Vector2D(0, 0), const Scale& scale = Scale(1.0f, 1.0f), float wTrigger = 110.0f, float hTrigger = 100, GameState* state = nullptr) :
		Enemy(position, texture, lives, elem, p, moving, dir, scale, wTrigger, hTrigger, state) 
	{
		slimeScale = scale.widthScale;
		actualSize = size;
		damageZone.y = position.getY(); damageZone.x = position.getX(); damageZone.w = width; damageZone.h = height / actualSize;
	};
	
	virtual void Move();
	virtual void DetectAttackTrigger(); // probably va a ser un render frame con el bicho cayendose cuando este en Attack_Time
	virtual bool Damage(/*const SDL_Rect& playerAttack, */elementsInfo::elements e);
	virtual void Die();
	virtual void render() const;

};

