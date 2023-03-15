#include "PlayerAttack.h"
#include "Transform.h"
#include "Health.h"
#include "../game/ecs.h"
#include "../ecs/Entity.h"
#include "PhysicsComponent.h"
#include "Image.h"
#include "Bullet.h"
#include "../sdlutils/SDLUtils.h"
#include "FramedImage.h" 

PlayerAttack::PlayerAttack(int width, int height) : tr_(nullptr), health_(nullptr), anim_(nullptr), physics(nullptr) {
	triggerHeight = height;
	triggerWidth = width;
	//triggerWH = Vector2D(width, height);
	canAttack = false;
	watAtackTriggWH = Vector2D(WATER_ATTACK_WIDTH, WATER_ATTACK_HEIGHT);
	waterAttackActive = false;
	earthAttackActive = false;
};

void PlayerAttack::initComponent() {
	tr_ = ent_->getComponent<Transform>();
	health_ = ent_->getComponent<Health>();
	anim_ = ent_->getComponent<PlayerAnimationComponent>();
	physics = ent_->getComponent<PhysicsComponent>();
}

void PlayerAttack::update() {

	if (anim_->getState() == ATTACK) { // ESTADO DE ATAQUE

		if (SDL_GetTicks() - startAttackingTime > AttackTime && canAttack) { // TIEMPO PARA HACER EL ATAQUE JUNTO CON LA ANIMACION
			switch (health_->getElement())
			{
			case ecs::Light: {
				MoveTrigger(Vector2D(triggerWidth, triggerHeight)); // Se mueven los triggers a la posici�n actual
				trigger = { trigger.x, trigger.y, triggerWidth, triggerHeight };
				attackEnemy(trigger);
				break;
			}
			case ecs::Earth:
				//MoveTrigger(Vector2D(EARTH_ATTACK_WIDTH, EARTH_ATTACK_HEIGHT)); // Se mueven los triggers a la posici�n actual
				if (!earthAttackActive)
				{
					trigger = { trigger.x, trigger.y, 0,EARTH_ATTACK_HEIGHT }; //cambiar altura 
					tAttack = mngr_->addEntity(ecs::_grp_PROYECTILES);
					tAttack->addComponent<Transform>(Vector2D(trigger.x, trigger.y), EARTH_ATTACK_WIDTH, EARTH_ATTACK_HEIGHT);
					tAttack->addComponent<FramedImage>(&sdlutils().images().at("earth_attack"), 1, 10);
					tAttack->addComponent<earthAnimationController>(anims::EARTH_ATTACK);

					colTrigger = 0;
					earthAttackActive = true;
				}
				break;
			case ecs::Fire: {
				if (chargedAttack) {
					remainingAttacks = 3;
					lastFireBallTime = SDL_GetTicks() - timeBetweenFireBalls;
					chargedAttack = false;
				}
				else spawnFireball();
				break;
			}
			case ecs::Water: {

				// Trigger de ataque
				trigger = { trigger.x, trigger.y, (int)watAtackTriggWH.getX(), (int)watAtackTriggWH.getY() };

				// Si no hay ya uno activo
				if (!waterAttackActive) {

					if (chargedAttack) {
						waterAttackDuration = 2 * WATER_ATTACK_DURATION;
						waterChargedAttack(trigger);
					}
					else {
						waterAttackDuration = WATER_ATTACK_DURATION;

						wAttack = mngr_->addEntity(ecs::_grp_PROYECTILES);
						wAttack->addComponent<Transform>(Vector2D(trigger.x, trigger.y), WATER_ATTACK_WIDTH, WATER_ATTACK_HEIGHT);
						wAttack->addComponent<FramedImage>(&sdlutils().images().at("earth_attack"), 1, 10);
						wAttack->addComponent<WaterAnimationController>(anims::WATER_ATTACK);
						waterAttackActive = true;


					}
				}
				break;
			}
			default: {
				break;
			}
			}

			canAttack = false;
		}
	}

	if (waterAttackActive) {

		// ATAQUE CARGADO

		if (chargedAttack) {
			MoveTrigger(watAtackTriggWH);
			trigger = { trigger.x, trigger.y, (int)watAtackTriggWH.getX(), (int)watAtackTriggWH.getY() };

			// Transform
			wAttack->getComponent<Transform>()->setPosition(Vector2D(trigger.x, trigger.y));

			// Si han pasado los segundos totales de la duracion, mata el ataque
			if ((SDL_GetTicks() >= waterDurationTimer + waterAttackDuration) || health_->getElement() != ecs::Water) {
				waterAttackActive = false;
				wAttack->setAlive(false);
				chargedAttack = false;
			}

			// Si ha pasado el tiempo del tick, hace da�o
			if (SDL_GetTicks() >= waterTickTimer) {

				// Ataca enemigo
				attackEnemy(trigger);
				waterTickTimer = SDL_GetTicks() + WATER_ATTACK_TICK_TIME;
			}
		}
		else {
			// Transform
			auto trAttack = wAttack->getComponent<Transform>();
			moveAttack(trAttack);
			auto waterAnimation = wAttack->getComponent<FramedImage>();
			auto waterStateAnimation = wAttack->getComponent<WaterAnimationController>();

			auto colAnim = waterAnimation->getCurrentCol();
			if (!physics->getLookDirection()) waterAnimation->flipTexture(true);
			else waterAnimation->flipTexture(false);
			if (colTrigger != colAnim + 1)
			{
				colTrigger = colAnim + 1;
				trigger.w = colTrigger * (trAttack->getWidth() / waterAnimation->getTexture()->getNumCols());
			}
			MoveTrigger(Vector2D(trigger.w, WATER_ATTACK_HEIGHT));

			if (waterStateAnimation->getState() == WATER_ADVANCE)
			{
				if (attackEnemy(trigger))
				{
					waterAnimation->setCol(colTrigger - 1);
					waterStateAnimation->setState(WATER_BACK, colTrigger - 1);
				}

			}
		}
	}
	else if (earthAttackActive)
	{
		// Transform
		auto trAttack = tAttack->getComponent<Transform>();
		moveAttack(trAttack);
		auto earthAnimation = tAttack->getComponent<FramedImage>();
		auto earthStateAnimation = tAttack->getComponent<earthAnimationController>();

		auto colAnim = earthAnimation->getCurrentCol();
		if (!physics->getLookDirection()) earthAnimation->flipTexture(true);
		else earthAnimation->flipTexture(false);
		if (colTrigger != colAnim + 1)
		{
			colTrigger = colAnim + 1;
			trigger.w = colTrigger * (trAttack->getWidth() / earthAnimation->getTexture()->getNumCols());
		}
		MoveTrigger(Vector2D(trigger.w, EARTH_ATTACK_HEIGHT));

		if (earthStateAnimation->getState() == ADVANCE)
		{
			if (attackEnemy(trigger))
			{
				earthAnimation->setCol(colTrigger - 1);
				earthStateAnimation->setState(BACK, colTrigger - 1);
			}

		}
	}

	if (remainingAttacks > 0 && SDL_GetTicks() - lastFireBallTime >= timeBetweenFireBalls) {
		spawnFireball();
		lastFireBallTime = SDL_GetTicks();
		--remainingAttacks;
	}
}

// PRIVATE

void PlayerAttack::waterChargedAttack(SDL_Rect& trigger) {

	// Añado entidad de ataque
	wAttack = mngr_->addEntity(ecs::_grp_PROYECTILES);

	// Entidad ataque
	wAttack->addComponent<Transform>(Vector2D(trigger.x, trigger.y), trigger.w, trigger.h);
	wAttack->addComponent<Image>(&sdlutils().images().at("water_attack"));

	waterAttackActive = true;
	waterDurationTimer = SDL_GetTicks();

}

void PlayerAttack::spawnFireball()
{
	//MoveTrigger(triggerWH); // Se mueven los triggers a la posici�n actual
	auto pTransf = ent_->getComponent<Transform>();
	Entity* attack = mngr_->addEntity(ecs::_grp_PROYECTILES);
	Vector2D shootPos = Vector2D(pTransf->getPosition().getX(), pTransf->getPosition().getY() + pTransf->getHeight() / 2);
	if (ent_->getComponent<PhysicsComponent>()->getLookDirection()) attack->addComponent<PhysicsComponent>(Vector2D(1, 0));
	else attack->addComponent<PhysicsComponent>(Vector2D(-1, 0));
	attack->addComponent<Transform>(shootPos, 50, 50);
	attack->addComponent<Image>(&sdlutils().images().at("ott_luz"));
	attack->addComponent<Bullet>(health_->getElement(), ent_);
}

void PlayerAttack::MoveTrigger(Vector2D attackWH) {
	int playerW = tr_->getWidth();
	int playerH = tr_->getHeight();
	Vector2D playerPos = tr_->getPosition();

	if (physics->getLookDirection()) {
		trigger.x = playerPos.getX() + playerW;
	}
	else {
		trigger.x = playerPos.getX() - attackWH.getX();
	}
	trigger.y = playerPos.getY() + playerW / 2;
}
void PlayerAttack::moveAttack(Transform* tr)
{
	int playerW = tr_->getWidth();
	int playerH = tr_->getHeight();
	Vector2D playerPos = tr_->getPosition();
	if (physics->getLookDirection()) {
		tr->setPosition(Vector2D(playerPos.getX() + playerW, playerPos.getY() + playerW / 2));
	}
	else {
		int attackWidth = 0;

		if (waterAttackActive)
			attackWidth = WATER_ATTACK_WIDTH;
		else if(earthAttackActive)
			attackWidth = EARTH_ATTACK_WIDTH;

		tr->setPosition(Vector2D(playerPos.getX() - attackWidth, playerPos.getY() + playerW / 2));
	}
}

// Ataca enemigo si esta en la zona de ataque
bool PlayerAttack::attackEnemy(SDL_Rect& attackZone) {
	bool attack = false;
	auto enemiesGrp = mngr_->getEntities(ecs::_grp_CHARACTERS);

	for (auto e : enemiesGrp) {

		SDL_Rect rect = e->getComponent<PhysicsComponent>()->getCollider();

		// Si enemigo y ataque interseccionan
		if (SDL_HasIntersection(&rect, &attackZone) && !e->hasComponent<PlayerAttack>()) {

			attack = true;
			// Hace da�o a enemigo dependiendo del elemento
			e->getComponent<Health>()->recieveDamage(health_->getElement());
		}
	}
	return attack;
}

