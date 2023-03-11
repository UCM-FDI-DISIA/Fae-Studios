#include "FramedImage.h"
#pragma once
#pragma region OTT
FramedImageOtt::FramedImageOtt()
{

}

void FramedImageOtt::initComponent()
{
	// está muy feo coger las texturas así, hay que cambiar esto de alguna forma
	tex_ = mngr_->getTexture(0);
	tr_ = ent_->getComponent<Transform>();
	shieldTex_ = mngr_->getTexture(4);
}

void FramedImageOtt::render()
{
	SDL_Rect dest; dest.x = tr_->getPos().getX(); dest.y = tr_->getPos().getY();
	dest.w = tr_->getW(); dest.h = tr_->getH();
	dest.x -= mngr_->getCamera()->getComponent<CameraComponent>()->camera.x;
	dest.y -= mngr_->getCamera()->getComponent<CameraComponent>()->camera.y;
	//if (pAnim_->isInvincible() && SDL_GetTicks() % 2 == 0) return;
	
	SDL_RendererFlip flip = SDL_FLIP_NONE;
	bool lookRight = ent_->getComponent<PhysicsComponent>()->getLookDirection();
	if (!lookRight) flip = SDL_FLIP_HORIZONTAL;

	//int state = pAnim_->getState();

	tex_->renderFrame(dest, row, col, 0, flip);

	if (isShielded) { // esto habría que cambiarlo de alguna forma, me parece feo que se ponga aquí
		int elemNum = ent_->getComponent<Health>()->getElement();
		shieldTex_ = mngr_->getTexture(elemNum+4);
		SDL_Rect shieldRect;
		shieldRect.x = tr_->getPos().getX() - mngr_->getCamera()->getComponent<CameraComponent>()->camera.x;
		shieldRect.y = tr_->getPos().getY() - mngr_->getCamera()->getComponent<CameraComponent>()->camera.y + 40;
		shieldRect.w = 50; shieldRect.h = 50;
		if (lookRight) shieldRect.x += 50;
		shieldTex_->render(shieldRect);
	}
}

void FramedImageOtt::changeElement(ecs::elements newElem)
{
	tex_ = mngr_->getTexture((int)newElem);
}

FramedImageOtt::~FramedImageOtt()
{

}
#pragma endregion

#pragma region ENEMY

FramedImageEnemy::FramedImageEnemy(Texture* text, anims::Entities e) {
	tex_ = text;
	this->e = e;
}

void FramedImageEnemy::initComponent() {
	tr_ = ent_->getComponent<Transform>();
	physics_ = ent_->getComponent<PhysicsComponent>();
}

void FramedImageEnemy::update() {
	lookingRight = physics_->getLookDirection();
}

void FramedImageEnemy::render(){
	SDL_Rect dest; dest.x = tr_->getPos().getX(); dest.y = tr_->getPos().getY();
	dest.w = tr_->getW(); dest.h = tr_->getH();
	dest.x -= mngr_->getCamera()->getComponent<CameraComponent>()->camera.x;
	dest.y -= mngr_->getCamera()->getComponent<CameraComponent>()->camera.y;
	SDL_RendererFlip flip;
	if (lookingRight&& e != anims::MELEE_ANIM || !lookingRight && e == anims::MELEE_ANIM) flip = SDL_FLIP_NONE;
	else flip = SDL_FLIP_HORIZONTAL;
	tex_->renderFrame(dest, row, col, 0, flip);
}

#pragma endregion
