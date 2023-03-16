#include "EarthBossAnimationController.h"
#include "FramedImage.h"
#include "EarthBossManager.h"

void EarthBossAnimationController::setState(anims::Entities newState, Entity* e1, Entity* e2) {
	state = newState;
	image1 = e1->getComponent<FramedImage>();
	if(e2 != nullptr)
		image2 = e2->getComponent<FramedImage>();
}

void EarthBossAnimationController::initComponent() {
	image1 = nullptr;
	image2 = nullptr;
}

void EarthBossAnimationController::update() {
	if (image1 != nullptr) {
		if (state == anims::EARTHBOSSPRESENT) {
			std::cout << "Animación de Presentación" << std::endl;
		}
		else if (state == anims::PAUSE_ANIM) {
			std::cout << "Animación de Pause" << std::endl;
		}
		timer_++;
		int col = image1->getCurrentCol();

		if (col != getNFrames(state) + getColNum(state) - 1) col = (timer_ / getTPerFrame(state)) % getNFrames(state) + getColNum(state);

		image1->setCol(col);

		if (timer_ > (getTPerFrame(state) * getNFrames(state)) + 1)
		{
			endAnim();
		}
		if (image2 != nullptr) {
			int col2 = image2->getCurrentCol();

			if (col2 != getNFrames(state) + getColNum(state) - 1) col2 = (timer_ / getTPerFrame(state)) % getNFrames(state) + getColNum(state);

			image2->setCol(col2);

			if (timer_ > (getTPerFrame(state) * getNFrames(state)) + 1)
			{
				endAnim();
			}
		}
	}
}

void EarthBossAnimationController::endAnim() {
	if (state == anims::EARTHBOSSPRESENT) {
		std::cout << "Termine la presentación, ahora paso al de pausa" << std::endl;
		emngr_->setState(PAUSE);
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
	//	// el enemigo ataca, aquí debería llamarse a una función de ataque
	//}
	////else if (currentAnimation == ATTACK_ENEMY && ent_->hasComponent<Generations>()) setState(AFTER_ATTACK_ENEMY);
	//else if (currentAnimation != DIE_ENEMY && eMovement_ != nullptr && eMovement_->isMoving()) { setState(WALK_ENEMY); }
	//else if (currentAnimation != DIE_ENEMY || currentAnimation == ATTACK) setState(IDLE_ENEMY);
	//else ent_->setAlive(false);
	timer_ = 0;
}
