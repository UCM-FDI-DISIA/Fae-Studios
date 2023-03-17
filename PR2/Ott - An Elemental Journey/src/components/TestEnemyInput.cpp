#include "TestEnemyInput.h"
#include "../ecs/Entity.h"

void TestEnemyInput::initComponent() {
	anim_ = ent_->getComponent<EnemyAnimationComponent>();
	input_ = InputHandler::instance();
}

void TestEnemyInput::update() {
	if (input_->isKeyJustDown(SDLK_i)) {
		anim_->setState(IDLE_ENEMY);
	}
	if (input_->isKeyJustDown(SDLK_k)) {
		anim_->setState(PREPARE_ATTACK_ENEMY);
	}
	if (input_->isKeyJustDown(SDLK_j)) {
		anim_->setState(ATTACK_ENEMY);
	}
	if (input_->isKeyJustDown(SDLK_l)) {
		anim_->setState(DIE_ENEMY);
	}
	if (input_->isKeyJustDown(SDLK_h)) {
		anim_->damage();
	}
}