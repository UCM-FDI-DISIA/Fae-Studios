#include "FramedImage.h"
#pragma once
#pragma region OTT
FramedImageOtt::FramedImageOtt() : tex_(nullptr) 
{

}

void FramedImageOtt::initComponent()
{
	if(tex_ == nullptr) tex_ = mngr_->getTexture(0);
	tr_ = ent_->getComponent<Transform>();
	shieldTex_ = mngr_->getTexture(4);
	pAnim_ = ent_->getComponent<PlayerAnimationComponent>();

}

void FramedImageOtt::render()
{
	SDL_Rect dest; dest.x = tr_->getPos().getX(); dest.y = tr_->getPos().getY();
	dest.w = tr_->getW(); dest.h = tr_->getH();
	dest.x -= mngr_->getCamera()->getComponent<CameraComponent>()->camera.x;
	dest.y -= mngr_->getCamera()->getComponent<CameraComponent>()->camera.y;
	if (pAnim_->isInvincible() && SDL_GetTicks() % 2 == 0) return;
	bool lookRight = ent_->getComponent<PhysicsComponent>()->getLookDirection();
	SDL_RendererFlip flip = SDL_FLIP_NONE;
	if (!lookRight) flip = SDL_FLIP_HORIZONTAL;
	int state = pAnim_->getState();
	if (col == (pAnim_->getNFrames(state) - 1 + pAnim_->getColNum(state)) && ((SDL_GetTicks() - pAnim_->getStartTicks()) / pAnim_->getTPerFrame(state)) % pAnim_->getNFrames(state) == 0) pAnim_->endAnim();
	switch (state)
	{
		// hacer algo con el cálculo de las columnas porque es repetición de código
		// cuando OTT cambia de elemento debería verse primero el elemento que es actualmente 

		case IDLE: col = (SDL_GetTicks() / pAnim_->getTPerFrame(IDLE)) % pAnim_->getNFrames(IDLE); tex_->renderFrame(dest, pAnim_->getRowNum(IDLE), col, 0, flip); break;
		case WALK: col = (SDL_GetTicks() / pAnim_->getTPerFrame(WALK)) % pAnim_->getNFrames(WALK); tex_->renderFrame(dest, pAnim_->getRowNum(WALK), col, 0, flip); break;
		case RUN: col = (SDL_GetTicks() / pAnim_->getTPerFrame(RUN)) % pAnim_->getNFrames(RUN); tex_->renderFrame(dest, pAnim_->getRowNum(RUN), col, 0, flip); break;
		case JUMP_UP: col = (SDL_GetTicks() / pAnim_->getTPerFrame(JUMP_UP)) % pAnim_->getNFrames(JUMP_UP); tex_->renderFrame(dest, pAnim_->getRowNum(JUMP_UP), col, 0, flip); break;
		case PEAK: tex_->renderFrame(dest, pAnim_->getRowNum(PEAK), 4, 0, flip); break;
		case FALL: tex_->renderFrame(dest, pAnim_->getRowNum(FALL), 5, 0, flip); break;
		case LAND: col = ((SDL_GetTicks() / pAnim_->getTPerFrame(LAND)) + 6) % pAnim_->getNFrames(LAND) + 6; tex_->renderFrame(dest, pAnim_->getRowNum(LAND), col, 0, flip); break;
		case VANISH: col = ((SDL_GetTicks() - pAnim_->getStartTicks()) / pAnim_->getTPerFrame(VANISH)) % pAnim_->getNFrames(VANISH); tex_->renderFrame(dest, pAnim_->getRowNum(VANISH), col, 0, flip); break;
		case DIE: col = ((SDL_GetTicks() - pAnim_->getStartTicks()) / pAnim_->getTPerFrame(DIE)) % pAnim_->getNFrames(DIE); tex_->renderFrame(dest, pAnim_->getRowNum(DIE), col, 0, flip); break;
		case ATTACK: col = ((SDL_GetTicks() - pAnim_->getStartTicks()) / pAnim_->getTPerFrame(ATTACK)) % pAnim_->getNFrames(ATTACK) + pAnim_->getColNum(ATTACK); tex_->renderFrame(dest, pAnim_->getRowNum(ATTACK), col, 0, flip); break;
		default: break;
	}

	if (isShielded) {
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

