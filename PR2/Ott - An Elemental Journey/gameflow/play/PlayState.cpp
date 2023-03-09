#pragma once
#include "PlayState.h"
#include "../../SDLApplication.h"
#include "../../componentes/EnemyAnimationController.h"
#include "../../componentes/TestEnemyInput.h"
#include "../../componentes/EnemyMovement.h"

PlayState::PlayState(SDLApplication* app) : GameState(PLAY_STATE, app) {
	
	Mix_Init(MIX_INIT_FLAC | MIX_INIT_MOD | MIX_INIT_MP3 | MIX_INIT_OGG | MIX_INIT_MID);
	Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 2048);
	music = Mix_LoadMUS("../../sounds/musics/Ambient 4.wav");
	Mix_PlayMusic(music, -1);
	manager_ = new Manager(app);
	manager_->createMap();
	manager_->createPlayer();
	auto player = manager_->getPlayer()->getComponent<Transform>()->getPos();
	auto enemy = manager_->addEntity(ecs::_grp_PROYECTILES);
	enemy->addComponent<Transform>(player.getX(), player.getY(), 100, 100);
	enemy->addComponent<FramedImageEnemy>(app->getTexture("slime", PLAY_STATE));
	enemy->addComponent<EnemyAnimationComponent>(anims::SLIME_ANIM);
	enemy->addComponent<TestEnemyInput>();
	/*auto ph = player->addComponent<PhysicsComponent>();
	ph->setVelocity({ 1,0 });
	ph->lookDirection(true);
	player->addComponent<EnemyMovement>();*/
}

void PlayState::checkCollisions()
{
	vector<Entity*> characters = manager_->getEntitiesByGroup(ecs::_grp_CHARACTERS);
	vector<Entity*> ground = manager_->getEntitiesByGroup(ecs::_grp_GROUND);
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
						cout << "ground touched" << endl;
						colVector = Vector2D(colVector.getX(), 0);
						physics->setGrounded(true);
					}
					else if (!physics->isGrounded()) {
						cout << "ceiling touched" << endl;
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
}
void PlayState::update() {
	checkCollisions();
	manager_->update();
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

