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
		cam_->setPos(newPlayerPos); // settear la nueva posición de la cámara
		tr_->setPosition(Vector2D(cam_->camera.x, cam_->camera.y));
		map_->activateObjectsInRoom(map_->getCurrentRoom(), false); // desactivar los objetos de la sala actual
		map_->setCurrentRoom(newMapRoom); // settear la nueva sala
		cam_->setBounds(map_->getCamBounds()); // cambiar los bounds de la cámara
		mngr_->getPlayer()->getComponent<Transform>()->setPosition(newPlayerPos); // settear la posición del jugador
		mngr_->getPlayer()->getComponent<Transform>()->setScale(map_->getCurrentRoomScale()); // settear su escala
		mngr_->getPlayer()->getComponent<Health>()->setDead(false); // decirle al jugador que no está muerto
		map_->activateObjectsInRoom(map_->getCurrentRoom(), true); // activar los objetos de la nueva sala
	}
	else {
		static_cast<PlayState*>(stateMachine().currentState())->endRest();
	}
	playerPs_->Resume(resumeSpeed);
	fadeOut = false;
	fadeIn = true;
	col = MAX_COL;
}