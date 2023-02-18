#pragma once
#include "Enemy.h"

class MeleeEnemy : public Enemy {
private:
	const int time_per_frame = 140;
	SDL_RendererFlip flip[2] = { SDL_FLIP_NONE, SDL_FLIP_HORIZONTAL };
	bool attacked = false;
	int col = 0;
	int attackStart = 0;
	int timer = 0;
public:
	MeleeEnemy(const Vector2D& position, Texture* texture, int lives, elementsInfo::elements elem, GameObject* p,
		bool moving, Vector2D dir = Vector2D(0, 0), const Scale& scale = Scale(1.0f, 1.0f), float wTrigger = 110.0f, float hTrigger = 100, GameState* state = nullptr, Texture* te = nullptr) :
				Enemy(position, texture, lives, elem, p, moving, dir, scale, wTrigger, hTrigger, state) {
		


		colliderOffset = {21 * scale.widthScale, 4 * scale.heightScale};
		colliderWH = { (double)(width * 0.45), height * 0.875};

		nearDistance = colliderWH.getX();
		attackTrigger = { 0,0, (int)width / 2, (int)height };
	};

	virtual void Move();

	virtual void render() const;

	virtual void Attack();

	void update();

	virtual void MoveTriggers();

	void Die();

};