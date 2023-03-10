#include "../utils/checkML.h"
#include "FramedImage.h"
#include "../sdlutils/Texture.h"
#include "../ecs/Entity.h"
#include "CameraComponent.h"
#include "PhysicsComponent.h"
#include "Health.h"


SDL_Rect FramedImage::getRect() const
{
    SDL_Rect destRect;

    destRect.x = transform->getPosition().getX(); destRect.y = transform->getPosition().getY();
    destRect.w = transform->getWidth(); destRect.h = transform->getHeight();

    return destRect;
}

void FramedImage::render() {
    texture->render({ currentCol * getFrameWidth(), currentRow * getFrameHeight(), getFrameWidth(), getFrameHeight() }, getRect());
}

void FramedImage::initComponent() {
    transform = ent_->getComponent<Transform>();
}

void FramedImageOtt::initComponent()
{
	// está muy feo coger las texturas así, hay que cambiar esto de alguna forma
	//tex_ = mngr_->getTexture(0);
	tr_ = ent_->getComponent<Transform>();
	//shieldTex_ = mngr_->getTexture(4);
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
	SDL_Rect dest; dest.x = tr_->getPosition().getX(); dest.y = tr_->getPosition().getY();
	dest.w = tr_->getWidth(); dest.h = tr_->getHeight();
	dest.x -= mngr_->getCamera()->getComponent<CameraComponent>()->camera.x;
	dest.y -= mngr_->getCamera()->getComponent<CameraComponent>()->camera.y;
	if (pAnim_->isInvincible() && SDL_GetTicks() % 2 == 0) return;

	SDL_RendererFlip flip = SDL_FLIP_NONE;
	bool lookRight = ent_->getComponent<PhysicsComponent>()->getLookDirection();
	if (!lookRight) flip = SDL_FLIP_HORIZONTAL;

	int state = pAnim_->getState();

	//tex_->renderFrame(dest, pAnim_->getRowNum(state), col, 0, flip);

	if (isShielded) { // esto habría que cambiarlo de alguna forma, me parece feo que se ponga aquí
		int elemNum = ent_->getComponent<Health>()->getElement();
		//shieldTex_ = mngr_->getTexture(elemNum + 4);
		SDL_Rect shieldRect;
		shieldRect.x = tr_->getPosition().getX() - mngr_->getCamera()->getComponent<CameraComponent>()->camera.x;
		shieldRect.y = tr_->getPosition().getY() - mngr_->getCamera()->getComponent<CameraComponent>()->camera.y + 40;
		shieldRect.w = 50; shieldRect.h = 50;
		if (lookRight) shieldRect.x += 50;
		shieldTex_->render(shieldRect);
	}
}

void FramedImageOtt::elementChanged(int newElem)
{
	//tex_ = mngr_->getTexture(newElem);
}
#pragma endregion
