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
	if (thereIsAnimation) {
		if (image1 != nullptr) {
			timer_++;
			int col = image1->getCurrentCol();

			if (col != getNFrames(state) + getColNum(state) - 1) col = (timer_ / getTPerFrame(state)) % getNFrames(state) + getColNum(state);

			image1->setCol(col);

			if (image2 != nullptr) {
 				int col2 = image2->getCurrentCol();

				if (col2 != getNFrames(state) + getColNum(state) - 1) col2 = (timer_ / getTPerFrame(state)) % getNFrames(state) + getColNum(state);

				image2->setCol(col2);

			}
			if (timer_ > (getTPerFrame(state) * getNFrames(state)) + 1)
			{
				endAnim();
			}
		}
	}
}

void EarthBossAnimationController::endAnim() {
	if (animPresentacion < 3 && state == anims::EARTHBOSSPRESENT) {
		std::cout << "Animacion de presentacion acabada, pasar al de pausa" << std::endl;
		++animPresentacion;
		image1->setCol(0);
	}
	else{
		if(state == anims::PAUSE_ANIM) {
			std::cout << "Animacion de pausa acabada, pasar a la siguiente" << std::endl;
		}
		else if (state == anims::MINIPAUSE_ANIM) {
			std::cout << "Animacion de mini pausa acabada, pasar a la siguiente" << std::endl;
		}
		else if (state == anims::WARNINGEARTH) {
			std::cout << "Animacion de warning acabada, pasar a la siguiente" << std::endl;
			thereIsAnimation = false;
			image1->setCol(0);
			image2->setCol(0);
		}
	}
	emngr_->setChangeState(true);
	timer_ = 0;
}
