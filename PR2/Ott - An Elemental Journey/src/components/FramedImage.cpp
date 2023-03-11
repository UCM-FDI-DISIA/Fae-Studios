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

FramedImageOtt::FramedImageOtt()
{

}

void FramedImageOtt::initComponent()
{
	// está muy feo coger las texturas así, hay que cambiar esto de alguna forma
	tex_ = &sdlutils().images().at("ott_luz");
	tr_ = ent_->getComponent<Transform>();
	shieldTex_ = &sdlutils().images().at("shield");
}

void FramedImageOtt::render()
{
	SDL_Rect dest; dest.x = tr_->getPosition().getX(); dest.y = tr_->getPosition().getY();
	dest.w = tr_->getWidth(); dest.h = tr_->getHeight();
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
		if (elemNum == ecs::Light) {
			shieldTex_ = &sdlutils().images().at("shield");
		}
		else if (elemNum == ecs::Earth) {
			shieldTex_ = &sdlutils().images().at("earthShield");
		}
		else if (elemNum == ecs::Water) {
			shieldTex_ = &sdlutils().images().at("waterShield");
		}
		else if (elemNum == ecs::Fire) {
			shieldTex_ = &sdlutils().images().at("fireShield");
		}
		SDL_Rect shieldRect;
		shieldRect.x = tr_->getPosition().getX() - mngr_->getCamera()->getComponent<CameraComponent>()->camera.x;
		shieldRect.y = tr_->getPosition().getY() - mngr_->getCamera()->getComponent<CameraComponent>()->camera.y + 40;
		shieldRect.w = 50; shieldRect.h = 50;
		if (lookRight) shieldRect.x += 50;
		shieldTex_->render(shieldRect);
	}
}

void FramedImageOtt::changeElement(ecs::elements newElem)
{
	if (newElem == ecs::Light) {
		tex_ = &sdlutils().images().at("shield");
	}
	else if (newElem == ecs::Earth) {
		tex_ = &sdlutils().images().at("earthShield");
	}
	else if (newElem == ecs::Water) {
		tex_ = &sdlutils().images().at("waterShield");
	}
	else if (newElem == ecs::Fire) {
		tex_ = &sdlutils().images().at("fireShield");
	}
}

FramedImageOtt::~FramedImageOtt()
{

}