#include "EnemyAnimationController.h"
#include "../ecs/Entity.h"
#include "FramedImage.h"
#include "PlayerAnimationComponent.h"
#include "../utils/checkML.h"
#include "Health.h"
#include "Generations.h"
#include "FramedImage.h"
#include "../states/GameStateMachine.h"
#include "../states/PlayState.h"
// LIMPIO

void EnemyAnimationComponent::setState(int newState) {
	if (!health_->isDead() && currentAnimation != DIE_ENEMY) {
		currentAnimation = newState;
		timer_ = 0;
		image->setCol(getColNum(currentAnimation));
	}
}

EnemyAnimationComponent::~EnemyAnimationComponent() {
	if(!ent_->isAlive())static_cast<PlayState*>(stateMachine().currentState())->eraseEnemy(posInList, roomNum);
}

void EnemyAnimationComponent::initComponent() {
	image = ent_->getComponent<FramedImage>();
	health_ = ent_->getComponent<Health>();
	eMovement_ = ent_->getComponent<EnemyMovement>();
	eAttack_ = ent_->getComponent<EnemyAttack>();
	setState(IDLE_ENEMY);
}

void EnemyAnimationComponent::update() {
	if (currentAnimation == IDLE_ENEMY && eMovement_ != nullptr && eMovement_->isMoving()) setState(WALK_ENEMY);
	else if (currentAnimation == WALK_ENEMY && !eMovement_->isMoving()) setState(IDLE_ENEMY);


	int state = currentAnimation;
	timer_++;

	if (damaged) {
		image->setRow(1);
		damageTimer_ = SDL_GetTicks() - damageStartTime_;
		if (damageTimer_ >= maxDamagedTimer_) {
			damaged = false;
		}
	}
	else { damageStartTime_ = SDL_GetTicks(); image->setRow(0); }

	int col = image->getCurrentCol();

	if (col != getNFrames(state) + getColNum(state) - 1) col = (timer_ / getTPerFrame(state)) % getNFrames(state) + getColNum(state);

	image->setCol(col);

	if (timer_ > (getTPerFrame(state) * getNFrames(state)) + 1)
	{
		endAnim();
	}

	/*
	if (currentAnimation == ATTACK_ENEMY || currentAnimation == DIE_ENEMY) return;
	Vector2D vel = ent_->getComponent<PhysicsComponent>()->getVelocity();
	if (vel.getX() != 0) currentAnimation = WALK_ENEMY;
	else currentAnimation = IDLE_ENEMY;*/
	switch (this->eAnims) {
	case anims::SLIME_ANIM:
		if (currentAnimation == WALK_ENEMY) sdlutils().soundEffects().at("slime_movement").play(0, ecs::_channel_ENEMY_SLIME);
		else if(currentAnimation == ATTACK_ENEMY) sdlutils().soundEffects().at("slime_attack").play(0, ecs::_channel_ENEMY_SLIME);
		break;
	case anims::MELEE_ANIM:
		if (currentAnimation == WALK_ENEMY) sdlutils().soundEffects().at("menemy_step").play(0, ecs::_channel_ENEMY_MELEE);
		break;
	case anims::RANGE_ANIM:
		if(currentAnimation == ATTACK_ENEMY) sdlutils().soundEffects().at("fireball").play(0, ecs::_channel_ENEMY_RANGE);
		break;
	}

}

void EnemyAnimationComponent::endAnim() {
	if (currentAnimation == PREPARE_ATTACK_ENEMY)
	{
		setState(ATTACK_ENEMY);
		eAttack_->Attack();
		// el enemigo ataca, aqu� deber�a llamarse a una funci�n de ataque
	}
	else if (currentAnimation == ATTACK_ENEMY && ent_->hasComponent<Generations>()) setState(AFTER_ATTACK_ENEMY);
	else if (currentAnimation != DIE_ENEMY && eMovement_ != nullptr && eMovement_->isMoving()) { setState(WALK_ENEMY); }
	else if (currentAnimation != DIE_ENEMY || currentAnimation == ATTACK) setState(IDLE_ENEMY);
	else ent_->setAlive(false);
	timer_ = 0;
}