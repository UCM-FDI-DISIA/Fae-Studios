#include "EnemyAnimationController.h"
#include "../Src/Entity.h"

void EnemyAnimationComponent::update() {
	if (currentAnimation == ATTACK_ENEMY || currentAnimation == DIE_ENEMY) return;
	Vector2D vel = ent_->getComponent<PhysicsComponent>()->getVelocity();
	if (vel.getX() != 0) currentAnimation = WALK_ENEMY;
	else currentAnimation = IDLE_ENEMY;
	if (invincible && SDL_GetTicks() - damageTimer >= invencibilityTime * 1000) invincible = false;
}