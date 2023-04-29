#include "WaterBubbleComponent.h"
#include "../components/Image.h"
#include "../components/Bullet.h"
WaterBubbleComponent::WaterBubbleComponent()
{
}


void WaterBubbleComponent::initComponent()
{
	player = mngr_->getPlayer();
	tr_ = ent_->getComponent<Transform>();
	spawnTime = SDL_GetTicks();
}

void WaterBubbleComponent::update()
{
	if (SDL_GetTicks() - lastTimeShot >= timeBetweenShots) {
		spawnShot();
		lastTimeShot = SDL_GetTicks();
	}
	if(SDL_GetTicks() - spawnTime >= lifeTime) ent_->setAlive(false); //Se destruye pasados unos segundos
}

void WaterBubbleComponent::spawnShot()
{
	auto bullet = mngr_->addEntity(ecs::_grp_PROYECTILES);
	Vector2D shootDir = player->getComponent<Transform>()->getPosition() - tr_->getPosition();
	bullet->addComponent<PhysicsComponent>(shootDir.normalize());
	bullet->addComponent<Transform>(tr_->getPosition(), ATTACK_SIZE * tr_->getScale(), ATTACK_SIZE * tr_->getScale());
	bullet->addComponent<Image>(&sdlutils().images().at("fire_attack"));
	bullet->addComponent<Bullet>(ecs::Water, ent_);
}

WaterBubbleComponent::~WaterBubbleComponent()
{
}