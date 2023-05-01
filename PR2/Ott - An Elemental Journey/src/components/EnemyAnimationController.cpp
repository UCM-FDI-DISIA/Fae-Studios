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
	if(!ent_->isAlive()) static_cast<PlayState*>(stateMachine().currentState())->eraseEnemy(posInList, roomNum);
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

	if (damaged && currentAnimation != DIE_ENEMY) {
		image->setRow(1);
		damageTimer_ = SDL_GetTicks() - damageStartTime_;
		if (damageTimer_ < maxDamagedTimer_ / 5) {
			sdlutils().soundEffects().at("hitTaken").setVolume(100);
			sdlutils().soundEffects().at("hitTaken").play(0, ecs::_channel_ENEMY_MELEE);
		}
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

	switch (this->eAnims) {
	case anims::SLIME_ANIM:
		if (currentAnimation == WALK_ENEMY) {
			sdlutils().soundEffects().at("slime_movement").setVolume(30);
			sdlutils().soundEffects().at("slime_movement").play(0, ecs::_channel_ENEMY_SLIME);
		}
		else if (currentAnimation == ATTACK_ENEMY) sdlutils().soundEffects().at("slime_attack").play(0, ecs::_channel_ENEMY_SLIME);
		break;
	case anims::MELEE_ANIM:
		if (currentAnimation == WALK_ENEMY) {
			sdlutils().soundEffects().at("menemy_step").setVolume(30);
			sdlutils().soundEffects().at("menemy_step").play(0, ecs::_channel_ENEMY_MELEE);
		}
		else if (currentAnimation == DIE_ENEMY) {
			sdlutils().soundEffects().at("menemy_dead").setVolume(50);
			sdlutils().soundEffects().at("menemy_dead").play(0, ecs::_channel_ENEMY_MELEE);
		}
		else if (currentAnimation == ATTACK_ENEMY) {
			sdlutils().soundEffects().at("menemy_attack").setVolume(50);
			sdlutils().soundEffects().at("menemy_attack").play(0, ecs::_channel_ENEMY_MELEE);
		}
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
		// el enemigo ataca, aquí debería llamarse a una función de ataque
	}
	else if (currentAnimation == ATTACK_ENEMY && ent_->hasComponent<Generations>()) setState(AFTER_ATTACK_ENEMY);
	else if (currentAnimation != DIE_ENEMY && eMovement_ != nullptr && eMovement_->isMoving()) { setState(WALK_ENEMY); }
	else if (currentAnimation != DIE_ENEMY || currentAnimation == ATTACK) setState(IDLE_ENEMY);
	else ent_->setAlive(false);
	timer_ = 0;
}