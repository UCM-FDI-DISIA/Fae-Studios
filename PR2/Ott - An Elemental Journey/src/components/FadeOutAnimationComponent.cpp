#include "FadeOutAnimationComponent.h"
#include "MapComponent.h"
#include "Health.h"
#include "../states/GameStateMachine.h"
#include "../states/PlayState.h"

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
	if (roomChange) {
		auto enemies_ = static_cast<PlayState*>(stateMachine().currentState())->getEnemies();
		for (auto it : enemies_[map_->getCurrentRoom()]) {
			it->setActive(false);
		}
		auto waterObjects = map_->getWater();
		for (auto water : waterObjects[map_->getCurrentRoom()]) {
			water->setActive(false);
		}
		for (auto water : waterObjects[newMapRoom]) {
			water->setActive(true);
		}

		auto interact = map_->getInteract();
		for (int i = 0; i < interact.size(); ++i) {
			for (auto ot : interact[i]) {
				if (i != newMapRoom) ot->setActive(false);
				else ot->setActive(true);
			}
		}
		map_->setCurrentRoom(newMapRoom);
		cam_->setBounds(map_->getCamBounds());
		mngr_->getPlayer()->getComponent<Transform>()->setPosition(newPlayerPos);
		mngr_->getPlayer()->getComponent<Transform>()->setScale(map_->getCurrentRoomScale());
		cam_->setPos(newPlayerPos);
		for (auto it : enemies_[newMapRoom]) {
			it->setActive(true);
		}
		mngr_->getPlayer()->getComponent<Health>()->setDead(false);
	}
	else {
		static_cast<PlayState*>(stateMachine().currentState())->endRest();
	}
	playerPs_->Resume(resumeSpeed);
	fadeOut = false;
	fadeIn = true;
	col = MAX_COL;
}