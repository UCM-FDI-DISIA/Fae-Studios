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
#include "../game/ecs.h"
#include "../components/Acceleration.h"
#include "../components/Pivot.h"
#include "../components/Health.h"
#include "../components/EnemyContactDamage.h"
#include "../components/Destruction.h"


PlayState::PlayState() : GameState(ecs::_state_PLAY) {
	/*Mix_Init(MIX_INIT_FLAC | MIX_INIT_MOD | MIX_INIT_MP3 | MIX_INIT_OGG | MIX_INIT_MID);
	Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 2048);
	//music = Mix_LoadMUS("../../sounds/musics/Ambient 4.	wav"); la m�sica va a ser cambiada a un json
	Mix_PlayMusic(music, -1);*/

	mngr_->setPlayer(constructors::player(mngr_, 500, 1000, 100, 120));
	mngr_->setCamera(constructors::camera(mngr_, 700, 1000, sdlutils().width(), sdlutils().height()));
	player_ = mngr_->getPlayer();
	camera_ = mngr_->getCamera();

	player_->getComponent<FramedImageOtt>()->initComponent();
	player_->getComponent<Transform>()->initComponent();
	player_->getComponent<PhysicsComponent>()->initComponent();
	player_->getComponent<PlayerInput>()->initComponent();
	player_->getComponent<PlayerAttack>()->initComponent();
	player_->getComponent<Health>()->initComponent();

	//prueba para movimiento de agua
	auto waterM = mngr_->addEntity(ecs::_grp_WATER);
	//500, 2000, 100, 120
	waterM->addComponent<Transform>(3500, 600, 300, 420);
	waterM->addComponent<Image>(&sdlutils().images().at("pixelWhite"));

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
	//waterBoss->addComponent<EnemyAnimationComponent>(anims::WATERBOSS_ANIM);

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
	constructors::eMelee(mngr_, "waterBug", 2400, 1000, 1.0f);
	constructors::eRanged(mngr_, "earthMushroom", 1700, 1000, 1.0f);
	constructors::map(mngr_);
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

    if (doNotDetectKeyboardInput && InputHandler::instance()->allKeysUp()) doNotDetectKeyboardInput = false;
    if (!doNotDetectKeyboardInput) {
        if (InputHandler::instance()->isKeyJustDown(SDLK_ESCAPE)) {
            //GameStateMachine::instance()->pushState(new PauseMenuState());
        }
    }
   
}

void PlayState::checkCollisions() {
	std::vector<Entity*> characters = mngr_->getEntities(ecs::_grp_CHARACTERS);
	std::vector<Entity*> ground = mngr_->getEntities(ecs::_grp_GROUND);
	for (Entity* e : characters) {
		auto eTr = e->getComponent<Transform>();
		auto physics = e->getComponent<PhysicsComponent>();
		auto health = e->getComponent<Health>();
		SDL_Rect r1 = physics->getCollider();
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
	}
}

std::pair<bool, bool> PlayState::checkCollisionWithVine() {
	bool interact = false;
	bool canGoUp = false;
	interactionIt = mngr_->getEntities(ecs::_grp_VINE).begin();
	SDL_Rect tr_ = player_->getComponent<PhysicsComponent>()->getCollider();
	while (!interact && interactionIt != mngr_->getEntities(ecs::_grp_VINE).end()) {
		Entity* ents = *interactionIt;
		if (ents->hasComponent<ColliderVine>()) {
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
	checkCollisions();
	GameState::update();
}

void PlayState::AddEnredadera() {
    Entity* aux = (*interactionIt);
    if (!(aux->getComponent<AddVine>()->doesntHaveVine())) {
        aux->getComponent<AddVine>()->setVine();
        aux->getComponent<AddVine>()->getVine()->addComponent<ImageVine>(&sdlutils().images().at("enredadera"));
        SDL_Rect dest;
        dest = aux->getComponent<AddVine>()->getVine()->getComponent<Transform>()->getRect();
        dest.h -= player_->getComponent<Transform>()->getRect().h / 2.5;
        aux->getComponent<AddVine>()->getVine()->addComponent<ColliderVine>(dest);
        aux->getComponent<AddVine>()->getVine()->addComponent<GrowVine>(aux->getComponent<AddVine>()->getPosFin(),
            Vector2D(aux->getComponent<AddVine>()->getPosFin().getX(), aux->getComponent<AddVine>()->getPosFin().getY() + player_->getComponent<Transform>()->getRect().h / 2));
    }
}

void PlayState::Teleport() {
    int cAnim = player_->getComponent<PlayerAnimationComponent>()->getState();
    if (cAnim != IDLE && cAnim != RUN) return;
    Entity* aux = *interactionIt;
    Entity* tpLamp = aux->getComponent<LampComponent>()->getConnectedLamp();
    Vector2D newPos = tpLamp->getComponent<Transform>()->getPosition();
    player_->getComponent<PlayerAnimationComponent>()->startTP(newPos);
}

void PlayState::Save() {
    player_->getComponent<Health>()->saveSactuary();
}
