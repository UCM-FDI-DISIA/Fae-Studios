#pragma once
#include "PlayState.h"
#include "../../SDLApplication.h"
#include "../../componentes/EnemyAnimationController.h"
#include "../../componentes/TestEnemyInput.h"
#include "../../componentes/EnemyMovement.h"
#include "../../componentes/EnemyAttack.h"
#include "../../componentes/SlimeStates.h"
#include "../../componentes/EnemyShootingAttack.h"
#include "../../componentes/PlayerInput.h"
#include "../../componentes/Bullet.h"
#include "../../componentes/EnemyMeleeAttack.h"

PlayState::PlayState(SDLApplication* app) : GameState(PLAY_STATE, app) {
	
	Mix_Init(MIX_INIT_FLAC | MIX_INIT_MOD | MIX_INIT_MP3 | MIX_INIT_OGG | MIX_INIT_MID);
	Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 2048);
	music = Mix_LoadMUS("../../sounds/musics/Ambient 4.wav");
	Mix_PlayMusic(music, -1);
	manager_ = new Manager(app);
	manager_->createMap();
	manager_->createPlayer();
	auto player = manager_->getPlayer()->getComponent<Transform>()->getPos();
	

	// Asi se añade enemigo slime

	auto enemy = manager_->addEntity(ecs::_grp_CHARACTERS);
	enemy->addComponent<Transform>(player.getX() + 100, player.getY()- 50, 240, 140);
	auto ph = enemy->addComponent<PhysicsComponent>();
	enemy->addComponent<FramedImageEnemy>(app->getTexture("waterSlime", PLAY_STATE), anims::SLIME_ANIM);
	enemy->addComponent<Health>(5, ecs::Fire, false);
	ph->setVelocity({ 1,0 });
	ph->lookDirection(true);

	auto eAttack_ = enemy->addComponent<EnemyAttack>(1200, 8, 100);
	enemy->addComponent<EnemyMovement>();
	
	auto eAnim_ = enemy->addComponent<EnemyAnimationComponent>(anims::SLIME_ANIM);
	auto meleeAttack_ = enemy->addComponent<EnemyMeleeAttack>();
	enemy->addComponent<Generations>(Generations::getMaxGeneration());
	enemy->addComponent<SlimeStates>();
	eAttack_->SetRefs(eAnim_, nullptr, meleeAttack_);
	

	// Asi se añade enemigo rango

	auto enemy2 = manager_->addEntity(ecs::_grp_CHARACTERS);
	enemy2->addComponent<Transform>(1700, 1800, 110, 110);
	auto ph2 = enemy2->addComponent<PhysicsComponent>();
	enemy2->addComponent<FramedImageEnemy>(app->getTexture("waterMushroom", PLAY_STATE), anims::RANGE_ANIM);
	enemy2->addComponent<Health>(5, ecs::Fire, false);
	ph2->setVelocity({ 0,0 });
	ph2->lookDirection(false);

	auto eAttack_2 = enemy2->addComponent<EnemyAttack>(1200, 400, 100);
	
	auto eAnim_2 = enemy2->addComponent<EnemyAnimationComponent>(anims::RANGE_ANIM);
	auto attack_2 = enemy2->addComponent<EnemyShootingAttack>();
	eAttack_2->SetRefs(eAnim_2, attack_2, nullptr);


	// Asi se añade enemigo melee

	auto enemy3 = manager_->addEntity(ecs::_grp_CHARACTERS);
	enemy3->addComponent<Transform>(2400, 1800, 230, 130);
	auto ph3 = enemy3->addComponent<PhysicsComponent>();
	enemy3->addComponent<FramedImageEnemy>(app->getTexture("waterBug", PLAY_STATE), anims::MELEE_ANIM);
	enemy3->addComponent<Health>(5, ecs::Fire, false);
	ph3->setVelocity({ 1,0 });
	ph3->lookDirection(true);

	auto eAttack_3 = enemy3->addComponent<EnemyAttack>(1200, 8, 100);
	enemy3->addComponent<EnemyMovement>();
	
	auto eAnim_3 = enemy3->addComponent<EnemyAnimationComponent>(anims::MELEE_ANIM);
	auto meleeAttack_3 = enemy3->addComponent<EnemyMeleeAttack>();
	eAttack_3->SetRefs(eAnim_3, nullptr, meleeAttack_3);
}
	
	
void PlayState::checkCollisions()
{
	vector<Entity*> characters = manager_->getEntitiesByGroup(ecs::_grp_CHARACTERS);
	vector<Entity*> ground = manager_->getEntitiesByGroup(ecs::_grp_GROUND);
	vector<Entity*> bullets = manager_->getEntitiesByGroup(ecs::_grp_PROYECTILES);
	for (Entity* e : characters) {
		auto eTr = e->getComponent<Transform>();
		SDL_Rect r1 = eTr->getRect();
		auto physics = e->getComponent<PhysicsComponent>();
		Vector2D& colVector = physics->getVelocity();

		auto mov = e->getComponent<EnemyMovement>();
		for (Entity* g : ground) { // WALL COLLISION

			SDL_Rect r2 = g->getComponent<Transform>()->getRect();
			SDL_Rect areaColision; // area de colision 	
			bool interseccion = SDL_IntersectRect(&r1, &r2, &areaColision);
			if (interseccion && (areaColision.w < areaColision.h) && ((areaColision.x <= r2.x + (r2.w / 2) && physics->getLookDirection()) ||
				(areaColision.x > r2.x + (r2.w / 2) && !physics->getLookDirection()))) {
				colVector = Vector2D(0, colVector.getY());
				if (mov != nullptr) {
					mov->ChangeDirection(false, areaColision);
				}
			}
		}

		int i = 0;
		for (Entity* g : ground) { // GROUND COLLISION
			SDL_Rect r2 = g->getComponent<Transform>()->getRect();
			SDL_Rect areaColision; // area de colision 	
			bool interseccion = SDL_IntersectRect(&r1, &r2, &areaColision);
			if (interseccion)
			{
				if (areaColision.w >= areaColision.h) {
					
					if (!physics->isGrounded() && areaColision.y > r1.y + r1.w / 2) {
						colVector = Vector2D(colVector.getX(), 0);
						physics->setGrounded(true);
					}
					else if (!physics->isGrounded()) {
						colVector = Vector2D(colVector.getX(), 1);
						physics->setVerticalSpeed(1);
					}
					if (mov != nullptr) mov->ChangeDirection(true, areaColision);

					break;
				}
			}
			else if (i == ground.size() - 1) physics->setGrounded(false);
			++i;
		}
	}

	/*for (Entity* b : bullets) {
		Entity* p = manager_->getPlayer();
		SDL_Rect r1 = p->getComponent<Transform>()->getRect();
		SDL_Rect r2 = b->getComponent<Transform>()->getRect();
		if (SDL_HasIntersection(&r1, &r2)) {
			p->getComponent<Health>()->recieveDamage(b->getComponent<Bullet>()->getElem());
			b->setAlive(false);	
		}

		for (Entity* g : ground) { // WALL COLLISION
			SDL_Rect r3 = g->getComponent<Transform>()->getRect();
			if (SDL_HasIntersection(&r2, &r3)) {
				b->setAlive(false);
			}
		}
	}*/
}
void PlayState::update() {
	checkCollisions();
	manager_->update();
	refresh();
}
void PlayState::render() const {
	manager_->render();
}

void PlayState::refresh()
{
	manager_->refresh();
}
PlayState::~PlayState()
{
	Mix_HaltMusic();
	Mix_FreeMusic(music);
	Mix_Quit();
}

