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
	pAnim_ = ent_->getComponent<PlayerAnimationComponent>();
}

void FramedImageOtt::update() {
	int state = pAnim_->getState();
	if (col == (pAnim_->getNFrames(state) - 1 + pAnim_->getColNum(state)) &&
		((SDL_GetTicks() - pAnim_->getStartTicks()) / pAnim_->getTPerFrame(state)) % pAnim_->getNFrames(state) == 0)
	{
		pAnim_->endAnim();
	}

	if (state == ATTACK || state == DIE || state == VANISH) {
		col = ((SDL_GetTicks() - pAnim_->getStartTicks()) / pAnim_->getTPerFrame(state)) % pAnim_->getNFrames(state) + pAnim_->getColNum(state);
	}
	else if (state == PEAK) col = 4;
	else if (state == FALL) col = 5;
	else if (state == LAND) col = 6;
	else {
		col = (SDL_GetTicks() / pAnim_->getTPerFrame(state)) % pAnim_->getNFrames(state) + pAnim_->getColNum(state);
	}
}

void FramedImageOtt::render()
{
	SDL_Rect dest; dest.x = tr_->getPos().getX(); dest.y = tr_->getPos().getY();
	dest.w = tr_->getW(); dest.h = tr_->getH();
	dest.x -= mngr_->getCamera()->getComponent<CameraComponent>()->camera.x;
	dest.y -= mngr_->getCamera()->getComponent<CameraComponent>()->camera.y;
	if (pAnim_->isInvincible() && SDL_GetTicks() % 2 == 0) return;
	
	SDL_RendererFlip flip = SDL_FLIP_NONE;
	bool lookRight = ent_->getComponent<PhysicsComponent>()->getLookDirection();
	if (!lookRight) flip = SDL_FLIP_HORIZONTAL;

	int state = pAnim_->getState();

	tex_->renderFrame(dest, pAnim_->getRowNum(state), col, 0, flip);

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

void FramedImageOtt::elementChanged(int newElem)
{
	tex_ = mngr_->getTexture(newElem);
}

FramedImageOtt::~FramedImageOtt()
{

}
#pragma endregion

#pragma region ENEMY

FramedImageEnemy::FramedImageEnemy(Texture* text) {
	tex_ = text;
}

void FramedImageEnemy::initComponent() {
	tr_ = ent_->getComponent<Transform>();
	eAnim_ = ent_->getComponent<EnemyAnimationComponent>();
}

void FramedImageEnemy::update() {
	if (eAnim_->isDamaged()) row = 1; // hay que hacer las filas de daño para el slime
	else row = 0;

	int state = eAnim_->getState();
	if (col == (eAnim_->getNFrames(state) - 1 + eAnim_->getColNum(state)) &&
		((SDL_GetTicks() - eAnim_->getStartTicks()) / eAnim_->getTPerFrame(state)) % eAnim_->getNFrames(state) == 0)
	{
		eAnim_->endAnim();
	}

	if (state == ATTACK_ENEMY || state == DIE_ENEMY || state == PREPARE_ATTACK_ENEMY) {
		col = ((SDL_GetTicks() - eAnim_->getStartTicks()) / eAnim_->getTPerFrame(state)) % eAnim_->getNFrames(state) + eAnim_->getColNum(state);
	}
	else {
		col = (SDL_GetTicks() / eAnim_->getTPerFrame(state)) % eAnim_->getNFrames(state) + eAnim_->getColNum(state);
	}
}

void FramedImageEnemy::render(){
	SDL_Rect dest; dest.x = tr_->getPos().getX(); dest.y = tr_->getPos().getY();
	dest.w = tr_->getW(); dest.h = tr_->getH();
	dest.x -= mngr_->getCamera()->getComponent<CameraComponent>()->camera.x;
	dest.y -= mngr_->getCamera()->getComponent<CameraComponent>()->camera.y;
	SDL_RendererFlip flip;
	/*bool lookRight = ent_->getComponent<PhysicsComponent>()->getLookDirection();
	if (!lookRight) flip = SDL_FLIP_HORIZONTAL;
	else flip = SDL_FLIP_NONE;*/
	int state = eAnim_->getState();

	tex_->renderFrame(dest, row, col);
}

#pragma endregion
