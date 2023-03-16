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
			std::cout << "Animacion de Presentación" << std::endl;
		}
		else if (state == anims::PAUSE_ANIM) {
			std::cout << "Animacion de Pause" << std::endl;
		}
		else if (state == anims::EARTHBOSSATTACK) {
			std::cout << "Animacion de Ataque vertical" << std::endl;
		}
		else if (state == anims::WARNINGEARTH) {
			std::cout << "Animacion de Warning" << std::endl;
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
	emngr_->setState(states[actualState]);
	if (actualState < states.size()-1) { ++actualState; }
	else { actualState = 0; }
	timer_ = 0;
}
