#include "../utils/checkML.h"
#include "FramedImage.h"
#include "../sdlutils/Texture.h"
#include "../ecs/Entity.h"
#include "CameraComponent.h"
#include "PhysicsComponent.h"
#include "Health.h"
#include "../states/PlayState.h"
#include "../states/GameStateMachine.h"


SDL_Rect FramedImage::getRect() const
{
    SDL_Rect destRect;

    destRect.x = transform->getPosition().getX(); destRect.y = transform->getPosition().getY();
    destRect.w = transform->getWidth(); destRect.h = transform->getHeight();

    return destRect;
}

void FramedImage::render() {
	if (ent_->hasComponent<FireBossComponent>()) {
		if (ent_->getComponent<FireBossComponent>()->isStunned() && SDL_GetTicks() % 2 == 0) return;
	}
	auto rect = getRect();
	if (cam != nullptr) {
		auto camera = cam->camera;
		rect.x -= camera.x;
		rect.y -= camera.y;
	}

	texture->renderFrame(rect, currentRow, currentCol, transform->getRotation(), flip);
}

void FramedImage::initComponent() {
    transform = ent_->getComponent<Transform>();
	auto camera = mngr_->getCamera();
	if (camera != nullptr) {
		cam = camera->getComponent<CameraComponent>();
	}
	else cam = nullptr;

	if (ent_->hasComponent<PhysicsComponent>()) {
		physics = ent_->getComponent<PhysicsComponent>();
	}
	else physics = nullptr;

}

void FramedImageOtt::initComponent()
{
	tr_ = ent_->getComponent<Transform>();
	pAnim = ent_->getComponent<PlayerAnimationComponent>();
	shieldTex_ = &sdlutils().images().at("shield");
	auto camera = mngr_->getCamera();
	if (camera != nullptr) {
		cam = camera->getComponent<CameraComponent>();
	}
	else cam = nullptr;
	if (ent_->hasComponent<PhysicsComponent>()) {
		physics = ent_->getComponent<PhysicsComponent>();
	}
	else physics = nullptr;
}

void FramedImageOtt::render()
{
	SDL_Rect dest; dest.x = tr_->getPosition().getX(); dest.y = tr_->getPosition().getY();
	dest.w = tr_->getWidth(); dest.h = tr_->getHeight();
	auto camCmpt = cam->camera;
	dest.x -= camCmpt.x;
	dest.y -= camCmpt.y;
	if (!ent_->getComponent<Health>()->isDead() && pAnim->isInvincible() && SDL_GetTicks() % 2 == 0)
		return;
	bool lookRight = true;
	SDL_RendererFlip flip = SDL_FLIP_NONE;
	if (physics != nullptr) {
		lookRight = physics->getLookDirection();
		if (!lookRight) flip = SDL_FLIP_HORIZONTAL;
	}
	//int state = pAnim_->getState();
	if (pAnim->getState() != DIE && ent_->getComponent<Health>()->isDead()) { row = pAnim->getRowNum(DIE); col = 7; }
	tex_->renderFrame(dest, row, col, 0, flip);

	if (isShielded) { // esto habría que cambiarlo de alguna forma, me parece feo que se ponga aquí
		int elemNum = ent_->getComponent<Health>()->getElement();
		// shieldTex_ = mngr_->getTexture(elemNum + 4);
		SDL_Rect shieldRect;
		shieldRect.x = tr_->getPosition().getX() - camCmpt.x;
		shieldRect.y = tr_->getPosition().getY() - camCmpt.y + 40;
		shieldRect.w = 50; shieldRect.h = 50;
		if (lookRight) shieldRect.x += 50;
		shieldTex_->renderFrame(shieldRect, shieldRow, shieldCol);
	}
}

void FramedImageOtt::hasAllRelics(bool sounds) {
	if (sounds) {
		sdlutils().soundEffects().at("relic_transformation").setVolume(50);
		sdlutils().soundEffects().at("relic_transformation").play(0, ecs::_channel_PLAYER);
	}
	hasRelics = true; 
	if(mngr_->getPlayer()->getComponent<Health>()->getElement() == ecs::Light) tex_ = &sdlutils().images().at("ott_luz_relic");
	if (mngr_->getPlayer()->getComponent<Health>()->getElement() == ecs::Earth) tex_ = &sdlutils().images().at("ott_tree_relic");
	if (mngr_->getPlayer()->getComponent<Health>()->getElement() == ecs::Water) tex_ = &sdlutils().images().at("ott_water_relic");
	if (mngr_->getPlayer()->getComponent<Health>()->getElement() == ecs::Fire) tex_ = &sdlutils().images().at("ott_fire_relic");
}

void FramedImageOtt::changeElement(ecs::elements newElem)
{
	if (newElem == ecs::Light) {
		if(hasRelics) tex_ = &sdlutils().images().at("ott_luz_relic");
		else tex_ = &sdlutils().images().at("ott_luz");
		shieldTex_ = &sdlutils().images().at("shield");
	}
	else if (newElem == ecs::Earth) {
		if (hasRelics) tex_ = &sdlutils().images().at("ott_tree_relic");
		else tex_ = &sdlutils().images().at("ott_tree");
		shieldTex_ = &sdlutils().images().at("earthShield");
	}
	else if (newElem == ecs::Water) {
		if (hasRelics) tex_ = &sdlutils().images().at("ott_water_relic");
		else tex_ = &sdlutils().images().at("ott_water");
		shieldTex_ = &sdlutils().images().at("waterShield");
	}
	else if (newElem == ecs::Fire) {
		if (hasRelics) tex_ = &sdlutils().images().at("ott_fire_relic");
		else tex_ = &sdlutils().images().at("ott_fire");
		shieldTex_ = &sdlutils().images().at("fireShield");
	}
}

FramedImageOtt::~FramedImageOtt()
{

}