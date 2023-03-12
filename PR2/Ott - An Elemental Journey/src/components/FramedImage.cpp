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
	auto rect = getRect();
	if (cam != nullptr) {
		auto camera = cam->camera;
		rect.x -= camera.x;
		rect.y -= camera.y;
	}

	texture->renderFrame(rect, 0, 0);
}

void FramedImage::initComponent() {
    transform = ent_->getComponent<Transform>();
	auto camera = mngr_->getCamera();
	if (camera != nullptr) {
		cam = mngr_->getCamera()->getComponent<CameraComponent>();
	}
	else cam = nullptr;
}

void FramedImageOtt::initComponent()
{
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
		// shieldTex_ = mngr_->getTexture(elemNum + 4);
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
		tex_ = &sdlutils().images().at("ott_luz");
	}
	else if (newElem == ecs::Earth) {
		tex_ = &sdlutils().images().at("ott_tree");
	}
	else if (newElem == ecs::Water) {
		tex_ = &sdlutils().images().at("ott_water");
	}
	else if (newElem == ecs::Fire) {
		tex_ = &sdlutils().images().at("ott_fire");
	}
}

FramedImageOtt::~FramedImageOtt()
{

}