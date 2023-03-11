#pragma once
#include "../utils/checkML.h"
#include "../ecs/Entity.h"
#include "../components/Transform.h"
#include"../components/Image.h"
#include "PlayState.h"
#include "../states/GameStateMachine.h"
#include "../sdlutils/InputHandler.h"
#include <vector>
#include "../components/PhysicsComponent.h"
#include "../components/EnemyMovement.h"

PlayState::PlayState() : GameState(ecs::_state_PLAY) {
	Mix_Init(MIX_INIT_FLAC | MIX_INIT_MOD | MIX_INIT_MP3 | MIX_INIT_OGG | MIX_INIT_MID);
	Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 2048);
	//music = Mix_LoadMUS("../../sounds/musics/Ambient 4.wav"); la música va a ser cambiada a un json
	Mix_PlayMusic(music, -1);
}

PlayState::~PlayState() {
	Mix_HaltMusic();
	Mix_FreeMusic(music);
	Mix_Quit();
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


void PlayState::update() {
	checkCollisions();
	GameState::update();
}
