#include "FadeOutAnimationComponent.h"
#include "MapComponent.h"

void FadeOutAnimationComponent::initComponent() {
	playerPs_ = mngr_->getPlayer()->getComponent<PhysicsComponent>();
	image_ = ent_->getComponent<FramedImage>();
	tr_ = ent_->getComponent<Transform>();
	cam_ = mngr_->getCamera()->getComponent<CameraComponent>();
}

void FadeOutAnimationComponent::update() {
	tr_->setPosition(Vector2D(cam_->camera.x, cam_->camera.y));
	//tr_->setWidth(sdlutils().width());
	//tr_->setHeight(sdlutils().height());   ESTO NO VA
	if (fadeOut || fadeIn) {
		timer_++;
		if (timer_ > timeBetweenFrames) {
			if (fadeOut && col < MAX_COL) col++;
			else if (col >= MAX_COL) { startFadeIn(); }
			
			if (fadeIn && col > 0) col--;
			else if (fadeIn && col <= 0) { fadeIn = false;  }

			image_->setCol(col);
			timer_ = 0;
		}
		onAnimPlaying = true;
	}
	else {
		timer_ = 0;
		col = 0;
		image_->setCol(col);
		onAnimPlaying = false;
	}
}

void FadeOutAnimationComponent::startFadeIn() {
	mngr_->getPlayer()->getComponent<Transform>()->setPosition(newPlayerPos);
	map_->setCurrentRoom(newMapRoom);
	mngr_->getPlayer()->getComponent<Transform>()->setScale(map_->getCurrentRoomScale());
	cam_->setBounds(map_->getCamBounds());
	playerPs_->Resume();
	fadeOut = false;
	fadeIn = true;
	col = MAX_COL;
}