#pragma once
#include "../utils/checkML.h"
#include "../components/Transform.h"
#include"../components/Image.h"
#include "PlayState.h"
#include "../states/GameStateMachine.h"
#include "../sdlutils/InputHandler.h"
#include <vector>
#include "../components/PhysicsComponent.h"
#include "../components/EnemyMovement.h"
#include "../game/Constructors.h"
#include "../components/FramedImage.h"
#include "../components/Generations.h"
#include "../components/SlimeStates.h"
#include "../components/ColliderVine.h"	
#include "../components/ImageVine.h"
#include "../components/GrowVine.h"
#include "../components/VineManager.h"
#include "../game/ecs.h"
#include "../components/Acceleration.h"
#include "../components/Pivot.h"
#include "../components/Health.h"
#include "../components/EnemyContactDamage.h"
#include "../components/Destruction.h"
#include "../components/WaterBossAnimationComponent.h"

#include "../components/FadeTransitionComponent.h"
#include "menus/PauseMenuState.h"

PlayState::PlayState() : GameState(ecs::_state_PLAY) {
	mngr_->setPlayer(constructors::player(mngr_, 700, 1500, 100, 120));
	mngr_->setCamera(constructors::camera(mngr_, 700, 2000, sdlutils().width(), sdlutils().height()));
	player_ = mngr_->getPlayer();
	camera_ = mngr_->getCamera();

	std::cout << "prueba" << std::endl;
	player_->getComponent<FramedImageOtt>()->initComponent();
	player_->getComponent<Transform>()->initComponent();
	player_->getComponent<PhysicsComponent>()->initComponent();
	player_->getComponent<PlayerInput>()->initComponent();
	player_->getComponent<PlayerAttack>()->initComponent();
	player_->getComponent<Health>()->initComponent();
	fade = mngr_->addEntity(ecs::_grp_FADEOUT);
	fade->addComponent<FadeTransitionComponent>(true, 1);
	fade->getComponent<FadeTransitionComponent>()->activateWithoutExecute();

	// se reinicializan los componentes del jugador porque muchos tienen referencias entre ellos y con la cámara 
	// y no se podrían coger de otra forma más que forzando el initComponent()
	player_->reinitCmpts();

	/*
	//prueba para movimiento de agua
	auto waterM = mngr_->addEntity(ecs::_grp_WATER);
	//500, 2000, 100, 120
	waterM->addComponent<Transform>(3500, 600, 300, 420);
	waterM->addComponent<Image>(&sdlutils().images().at("pixelWhite"));
	*/
	// COMENTO A LOS ENEMIGOS PORQUE ME ESTÁN DANDO POR CULO UN RATO CHAU BESOS

	auto waterBoss = mngr_->addEntity(ecs::_grp_CHARACTERS);
	int x = 100;
	int y = 1000;
	float scale = 2.5f;
	auto waterPh= waterBoss->addComponent<PhysicsComponent>(anims::SLIME);
	waterPh->setVelocity(Vector2D(-1,0));
	waterPh->setGravity(false);
	waterPh->lookDirection(false);
	waterBoss->addComponent<Transform>(x, y, 110 * scale, 110 * scale);
	waterPh->createCollider();
	waterBoss->addComponent<FramedImage>(&sdlutils().images().at("water_boss"), 4, 8);
	waterBoss->addComponent<Acceleration>();
	waterBoss->addComponent<Health>(5, ecs::Fire, false);
	waterBoss->addComponent<EnemyContactDamage>();
	waterBoss->addComponent<WaterBossAnimationComponent>(anims::WATERBOSS_ANIM);

	// OBJETOS QUE DESTRUYE BOSS AGUA
	x = 600;
	y = 1300;
	scale = 1.0f;
	auto waterObj = mngr_->addEntity(ecs::_grp_GROUND);
	auto watObjPh = waterObj->addComponent<PhysicsComponent>();
	watObjPh->setGravity(false);
	waterObj->addComponent<Transform>(x, y, 100 * scale, 100 * scale);
	waterObj->addComponent<Image>(&sdlutils().images().at("pixelWhite"));
	waterObj->addComponent<Destruction>(waterBoss);

	// OBJETO DESTRUCTIBLE 2
	x =1200;
	y = 1300;
	scale = 1.0f;
	auto waterObj2 = mngr_->addEntity(ecs::_grp_GROUND);
	auto watObjPh2 = waterObj2->addComponent<PhysicsComponent>();
	watObjPh2->setGravity(false);
	waterObj2->addComponent<Transform>(x, y, 100 * scale, 100 * scale);
	waterObj2->addComponent<Image>(&sdlutils().images().at("pixelWhite"));
	waterObj2->addComponent<Destruction>(waterBoss);



	auto box0 = mngr_->addEntity(ecs::_grp_CHARACTERS);
	 x = 100;
	 y = 1000;
	 scale = 1.0f;
	auto boxPh0 = box0->addComponent<PhysicsComponent>();
	boxPh0->setGravity(false);
	box0->addComponent<Transform>(x, y, 110 * scale, 110 * scale);
	box0->addComponent<Image>(&sdlutils().images().at("pixelWhite"));
	box0->addComponent<Pivot>(waterBoss,0);

	auto box1 = mngr_->addEntity(ecs::_grp_CHARACTERS);
	x = 100;
	y = 1200;
	scale = 1.0f;
	auto boxPh1 = box1->addComponent<PhysicsComponent>();
	boxPh1->setGravity(false);
	box1->addComponent<Transform>(x, y, 110 * scale, 110 * scale);
	box1->addComponent<Image>(&sdlutils().images().at("pixelWhite"));
	box1->addComponent<Pivot>(waterBoss, 1);

	auto box2 = mngr_->addEntity(ecs::_grp_CHARACTERS);
	x = 800;
	y = 1200;
	scale = 1.0f;
	auto boxPh2 = box2->addComponent<PhysicsComponent>();
	boxPh2->setGravity(false);
	box2->addComponent<Transform>(x, y, 110 * scale, 110 * scale);
	box2->addComponent<Image>(&sdlutils().images().at("pixelWhite"));
	box2->addComponent<Pivot>(waterBoss, 2);

	auto box3 = mngr_->addEntity(ecs::_grp_CHARACTERS);
	x = 800;
	y = 1000;
	scale = 1.0f;
	auto boxPh3 = box3->addComponent<PhysicsComponent>();
	boxPh3->setGravity(false);
	box3->addComponent<Transform>(x, y, 110 * scale, 110 * scale);
	box3->addComponent<Image>(&sdlutils().images().at("pixelWhite"));
	box3->addComponent<Pivot>(waterBoss, 3);
	


	//constructors::eSlime(mngr_, "fireSlime", 600, 1100, 1.0f);
	//constructors::eMelee(mngr_, "waterBug", 2400, 1000, 1.0f);
	//constructors::eRanged(mngr_, "earthMushroom", 1700, 1000, 1.0f);
	//constructors::map(mngr_);
	//constructors::eSlime(mngr_, "fireSlime", 800, 2100, 1.0f, ecs::Fire);
	// constructors::eMelee(mngr_, "waterBug", 2400, 2000, 1.0f, ecs::Water);
	// constructors::eRanged(mngr_, "earthMushroom", 1700, 2000, 1.0f, ecs::Earth);
	map_ = constructors::map(mngr_, this)->getComponent<MapComponent>();
	initialEnemies = enemies;
}

PlayState::~PlayState() {
	/*Mix_HaltMusic();
	Mix_FreeMusic(music);
	Mix_Quit();*/
}

void PlayState::blockKeyboardInputAfterUnfreeze() {
    doNotDetectKeyboardInput = true;
}

void PlayState::handleInput() {
    GameState::handleInput();
	
	if (doNotDetectKeyboardInput && InputHandler::instance()->allKeysUp() && fade->getComponent<FadeTransitionComponent>()->hasEndedAnimation()) doNotDetectKeyboardInput = false;
	
	if (!doNotDetectKeyboardInput) {
		if (InputHandler::instance()->isKeyJustDown(SDLK_ESCAPE)) {
			fade->getComponent<FadeTransitionComponent>()->setFunction([]() { GameStateMachine::instance()->pushState(new PauseMenuState()); });
			fade->getComponent<FadeTransitionComponent>()->changeSpeed(5);
			fade->getComponent<FadeTransitionComponent>()->revert();
			doNotDetectKeyboardInput = true;
		}
	}
}

void PlayState::checkCollisions(std::list<Entity*> entities) {
	int aa = 0;
	for (Entity* e : entities) {
		auto eTr = e->getComponent<Transform>();
		auto physics = e->getComponent<PhysicsComponent>();
		auto health = e->getComponent<Health>();
		SDL_Rect r1 = physics->getCollider();
		r1.x += physics->getVelocity().getX();
		r1.y += physics->getVelocity().getY();
		// std::cout << r1.x << " " << r1.y << std::endl;
		Vector2D& colVector = physics->getVelocity();

		auto mov = e->getComponent<EnemyMovement>();

		auto grounds = map_->checkCollisions(r1);

		for (std::pair<SDL_Rect, SDL_Rect> gr : grounds) { // WALL COLLISION
			if (gr.first.w < gr.first.h && ((gr.first.x <= gr.second.x + (gr.second.w / 2) && physics->getLookDirection()) ||
				(gr.first.x > gr.second.x + (gr.second.w / 2) && !physics->getLookDirection()))) {
				colVector = Vector2D(0, colVector.getY());
				if (mov != nullptr) {
					mov->ChangeDirection(false, gr.first);
				}
			}
		}
		/*
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
		}*/
		int i = 0;
		for (std::pair<SDL_Rect, SDL_Rect> gr : grounds) {
			auto areaColision = gr.first;

			if (areaColision.w >= areaColision.h) {

				if (!physics->isGrounded() && areaColision.y > r1.y + r1.w / 2) {
					//cout << "ground touched" << endl;
					if (!(physics->getWater()) || (physics->getWater() && health->getElement() == ecs::Water))
					{
						colVector = Vector2D(colVector.getX(), 0);
					}
					physics->setGrounded(true);
				}
				else if (!physics->isGrounded()) {
					//cout << "ceiling touched" << endl;
					if (!(physics->getWater()) || (physics->getWater() && health->getElement() == ecs::Water))
					{
						colVector = Vector2D(colVector.getX(), 1);
						physics->setVerticalSpeed(1);
					}
				}
				if (mov != nullptr) mov->ChangeDirection(true, areaColision);

				++i;
				break;
			}
		}
		
		if(i == 0) physics->setGrounded(false);

		/*
 		int i = 0;
		for (Entity* g : ground) { // GROUND COLLISION
			SDL_Rect r2 = g->getComponent<Transform>()->getRect();
			SDL_Rect areaColision; // area de colision 	
			bool interseccion = SDL_IntersectRect(&r1, &r2, &areaColision);
			if (interseccion)
			{
				if (areaColision.w >= areaColision.h) {

					if (!physics->isGrounded() && areaColision.y > r1.y + r1.w / 2) {
						//cout << "ground touched" << endl;
						if (!(physics->getWater()) || (physics->getWater() && health->getElement() == ecs::Water))
						{
							colVector = Vector2D(colVector.getX(), 0);
						}
						physics->setGrounded(true);
					}
					else if (!physics->isGrounded()) {
						//cout << "ceiling touched" << endl;
						if (!(physics->getWater()) || (physics->getWater() && health->getElement() == ecs::Water))
						{
							colVector = Vector2D(colVector.getX(), 1);
							physics->setVerticalSpeed(1);
						}
					}
					if (mov != nullptr) mov->ChangeDirection(true, areaColision);

					break;
				}
			}
			else if (i == ground.size() - 1) physics->setGrounded(false);
			++i;
		}
		*/
		//colisiones con el material de agua 
		int j = 0;
		std::vector <Entity*> water = mngr_->getEntities(ecs::_grp_WATER);
		for (Entity* w : water) {
			SDL_Rect r3 = w->getComponent<Transform>()->getRect();
			SDL_Rect areaColision; // area de colision 	
			bool interseccion = SDL_IntersectRect(&r1, &r3, &areaColision);
			if (interseccion)
			{
				physics->setWater(true); ++j;
				if (health->getElement() != ecs::Water) { physics->setGrounded(false); }
				//comprobación de si esta en la zona de flote, de momento sin variable de ancho de zona de flote 
				if (areaColision.y <= r3.y + 5) {
					physics->setFloating(true);
				}
				else {
					physics->setFloating(false);
				}
			}

		}
		if (j == 0) { physics->setWater(false); physics->setFloating(false); }
		aa++;
	}
}

std::pair<bool, bool> PlayState::checkCollisionWithVine() {
	bool interact = false;
	bool canGoUp = false;
	interactionIt = mngr_->getEntities(ecs::_grp_VINE).begin();
	SDL_Rect tr_ = player_->getComponent<PhysicsComponent>()->getCollider();
	while (!interact && interactionIt != mngr_->getEntities(ecs::_grp_VINE).end()) {
		Entity* ents = *interactionIt;
		if (ents->hasComponent<ColliderVine>() && ents->getComponent<ImageVine>()->canClimb()) {
			SDL_Rect r1;
			r1.x = tr_.x + tr_.w / 3;
			r1.y = tr_.y + tr_.h - 30;
			r1.w = tr_.w / 3;
			r1.h = 1;
			SDL_Rect r2 = ents->getComponent<ColliderVine>()->getRect();

			if (SDL_HasIntersection(&r1, &r2)) {
				if (tr_.y + tr_.h * 0.6 <= r2.y) {
					canGoUp = false;
					// no dejar que se mueva hacia arriba
				}
				else canGoUp = true;
				interact = true;
			}
		}
		interactionIt++;
	}
	return std::make_pair(interact, canGoUp);
}

void PlayState::checkInteraction() {
    bool interact = false;
    interactionIt = mngr_->getEntities(ecs::_grp_INTERACTION).begin();
	auto itEnd = mngr_->getEntities(ecs::_grp_INTERACTION).end();
	SDL_Rect r1 = mngr_->getPlayer()->getComponent<Transform>()->getRect();
    while (!interact && interactionIt != itEnd) {
        Entity* ents = *interactionIt;
        SDL_Rect r2 = ents->getComponent<Transform>()->getRect();
        if (SDL_HasIntersection(&r1, &r2)) {
            ents->getComponent<InteractionComponent>()->interact();
            interact = true;
        }
        interactionIt++;
    }
}

void PlayState::update() {
	checkCollisions({ player_ });
	checkCollisions(enemies[map_->getCurrentRoom()]);
	for (auto it : enemies) {
		for (auto ot : it) {
			if (it != enemies[map_->getCurrentRoom()]) {
				ot->getComponent<PhysicsComponent>()->Stop();
			}
			else {
				ot->getComponent<PhysicsComponent>()->Resume();
			}
		}
	}
	GameState::update();
}

void PlayState::AddEnredadera() {
    Entity* aux = (*interactionIt);
	aux->getComponent<VineManager>()->addVine();
}

void PlayState::Teleport() {
    int cAnim = player_->getComponent<PlayerAnimationComponent>()->getState();
    if (cAnim != IDLE && cAnim != RUN) return;
    Entity* aux = *interactionIt;
    Entity* tpLamp = aux->getComponent<LampComponent>()->getConnectedLamp();
    Vector2D newPos = tpLamp->getComponent<Transform>()->getPosition();
	auto newRoom = tpLamp->getComponent<LampComponent>()->getRoom();
	if (aux->getComponent<LampComponent>()->getRoom() != newRoom) {
		map_->changeRoom(std::to_string(newRoom), newPos);
	}
	player_->getComponent<PlayerAnimationComponent>()->startTP(newPos);
}

void PlayState::Save() {
	map_->playFadeOutAnimation();
	lastSanctuary = getCurrentInteraction();
}

void PlayState::endRest() {
    player_->getComponent<Health>()->saveSactuary(lastSanctuary);
}
