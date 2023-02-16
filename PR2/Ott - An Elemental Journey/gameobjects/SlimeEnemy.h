#pragma once
#include "Enemy.h"

class SlimeEnemy : public Enemy
{
	enum size { big=3, medium=2, small=1 };
protected:
	int actualSize = big;
	SDL_Rect damageZone = {0,0,0,0};

	void Divide();
public:
	SlimeEnemy(int size, const Vector2D& position, Texture* texture, int lives, elementsInfo::elements elem, GameObject* p,
		bool moving, Vector2D dir = Vector2D(0, 0), const Scale& scale = Scale(1.0f, 1.0f), float wTrigger = 110.0f, float hTrigger = 100, GameState* state = nullptr) :
		Enemy(position, texture, lives, elem, p, moving, dir, scale, wTrigger, hTrigger, state) 
	{
		actualSize = size;
		damageZone.y = position.getY(); damageZone.x = position.getX(); damageZone.w = width; damageZone.h = height / actualSize;
	};
	
	virtual void Move();
	virtual void Attack(); // probably va a ser un render frame con el bicho cayendose cuando este en Attack_Time
	virtual bool Damage(const SDL_Rect& playerAttack, elementsInfo::elements e);
	virtual void Die();

};

