#include "EarthBossAnimationController.h"
#include "FramedImage.h"
#include "EarthBossManager.h"

void EarthBossAnimationController::setState(anims::Entities newState, Entity* e) {
	state = newState;
	image = e->getComponent<FramedImage>();
}

void EarthBossAnimationController::initComponent() {
	image = nullptr;
}

void EarthBossAnimationController::update() {
	if (image != nullptr) {
		timer_++;
		int col = image->getCurrentCol();

		if (col != getNFrames(state) + getColNum(state) - 1) col = (timer_ / getTPerFrame(state)) % getNFrames(state) + getColNum(state);

		image->setCol(col);

		if (timer_ > (getTPerFrame(state) * getNFrames(state)) + 1)
		{
			endAnim();
		}
	}
}

void EarthBossAnimationController::endAnim() {
	if (state == anims::EARTHBOSSPRESENT) {
		std::cout << "Termine la presentaci�n, ahora paso al de pausa" << std::endl;
		//emngr_->setState(PAUSE);
	}
	else if (state == anims::PAUSE_ANIM) {
		std::cout << "Termine la pausa" << std::endl;
	}
	/*if (currentAnimation == PRESENTATION) {
		setState(STOP);
	}
	else if(currentAnimation == WARNING)*/
	//if (currentAnimation == PREPARE_ATTACK_ENEMY)
	//{
	//	setState(ATTACK_ENEMY);
	//	eAttack_->Attack();
	//	// el enemigo ataca, aqu� deber�a llamarse a una funci�n de ataque
	//}
	////else if (currentAnimation == ATTACK_ENEMY && ent_->hasComponent<Generations>()) setState(AFTER_ATTACK_ENEMY);
	//else if (currentAnimation != DIE_ENEMY && eMovement_ != nullptr && eMovement_->isMoving()) { setState(WALK_ENEMY); }
	//else if (currentAnimation != DIE_ENEMY || currentAnimation == ATTACK) setState(IDLE_ENEMY);
	//else ent_->setAlive(false);
	timer_ = 0;
}
