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

	constructors::eSlime(mngr_, "fireSlime", 600, 1100, 1.0f);
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
						colVector = Vector2D(colVector.getX(), 0);
						physics->setGrounded(true);
					}
					else if (!physics->isGrounded()) {
						//cout << "ceiling touched" << endl;
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
