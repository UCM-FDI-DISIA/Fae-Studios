#include "FadeOutAnimationComponent.h"
#include "MapComponent.h"
#include "Health.h"
#include "../states/GameStateMachine.h"
#include "../states/PlayState.h"

void FadeOutMapComponent::initComponent() {
	playerPs_ = mngr_->getPlayer()->getComponent<PhysicsComponent>();
	image_ = ent_->getComponent<FramedImage>();
	tr_ = ent_->getComponent<Transform>();
	cam_ = mngr_->getCamera()->getComponent<CameraComponent>();
}

void FadeOutMapComponent::update() {
	tr_->setPosition(Vector2D(cam_->camera.x, cam_->camera.y));
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

void FadeOutMapComponent::startFadeIn() {
	if (roomChange) {
		map_->setPlayerInRoom(newPlayerPos, newMapRoom);
		tr_->setPosition(Vector2D(cam_->camera.x, cam_->camera.y));
		roomChange = false;
	}
	else if (mapChange) {
		map_->changeMap(newMapEnum, newMapKey, newMapPlayerPos);
		tr_->setPosition(Vector2D(cam_->camera.x, cam_->camera.y));
		mapChange = false;
	}
	else {
		static_cast<PlayState*>(stateMachine().currentState())->endRest();
	}
	playerPs_->Resume(resumeSpeed);
	fadeOut = false;
	fadeIn = true;
	col = MAX_COL;
}