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
#include "../components/BossDoor.h"

#include "../components/FadeTransitionComponent.h"
#include <fstream>
#include "menus/PauseMenuState.h"
#include "../components/ElementObject.h"
#include <iostream>
#include "../components/ActiveWater.h"

PlayState::PlayState() : GameState(ecs::_state_PLAY) {
	currentMap = ecs::EARTH_MAP;

	mngr_->setPlayer(constructors::player(mngr_, 700, 1500, 100, 120));
	mngr_->setCamera(constructors::camera(mngr_, 700, 2000, sdlutils().width(), sdlutils().height()));
	player_ = mngr_->getPlayer();
	camera_ = mngr_->getCamera();

    fade = mngr_->addEntity(ecs::_grp_FADEOUT);
	fade->addComponent<FadeTransitionComponent>(true, 1);
	fade->getComponent<FadeTransitionComponent>()->setFunction([this]() {doNotDetectKeyboardInput = false; sdlutils().musics().at(sdlutils().levels().at(map_->getCurrentLevel()).bgsong).play(); });
	fade->getComponent<FadeTransitionComponent>()->activate();

	// se reinicializan los componentes del jugador porque muchos tienen referencias entre ellos y con la cámara 
	// y no se podrían coger de otra forma más que forzando el initComponent()
	player_->reinitCmpts();

	// Inicializar el array de salas
	visitedRooms.reserve(ecs::LAST_MAP_ID);
	for (int i = 0; i < ecs::LAST_MAP_ID; ++i) {
		visitedRooms.push_back({});
	}

	map_ = constructors::map(mngr_, this, (int)(currentMap))->getComponent<MapComponent>();
	initialEnemies = enemies;
}

PlayState::PlayState(std::string fileName) : GameState(ecs::_state_PLAY) {
	currentMap = ecs::EARTH_MAP;

	mngr_->setPlayer(constructors::player(mngr_, 700, 1500, 100, 120));
	mngr_->setCamera(constructors::camera(mngr_, 700, 2000, sdlutils().width(), sdlutils().height()));
	player_ = mngr_->getPlayer();
	camera_ = mngr_->getCamera();

	std::ifstream file(fileName);

	player_->getComponent<Health>()->loadFromFile(file);
	player_->getComponent<PlayerInput>()->loadFromFile(file);

	fade = mngr_->addEntity(ecs::_grp_FADEOUT);
	fade->addComponent<FadeTransitionComponent>(true, 1);
	fade->getComponent<FadeTransitionComponent>()->setFunction([this]() {doNotDetectKeyboardInput = false; sdlutils().musics().at(sdlutils().levels().at(map_->getCurrentLevel()).bgsong).play(); });
	fade->getComponent<FadeTransitionComponent>()->activate();

	// se reinicializan los componentes del jugador porque muchos tienen referencias entre ellos y con la cámara 
	// y no se podrían coger de otra forma más que forzando el initComponent()
	player_->reinitCmpts();

	visitedRooms.reserve(ecs::LAST_MAP_ID);
	for (int i = 0; i < ecs::LAST_MAP_ID; ++i) {
		visitedRooms.push_back({});
	}
	map_ = constructors::map(mngr_, this, (int)ecs::EARTH_MAP, file)->getComponent<MapComponent>();

	currentMap = (ecs::maps) map_->getCurrentMap();
	initialEnemies = enemies;	
	std::string aux;
	file >> aux >> aux;
	while (aux != "_") {
		bool visited;
		file >> visited;
		visitedRooms[ecs::EARTH_MAP][std::stoi(aux)] = visited;
		file >> aux;
	}
	file >> aux >> aux;
	while (aux != "_") {
		bool visited;
		file >> visited;
		visitedRooms[ecs::WATER_MAP][std::stoi(aux)] = visited;
		file >> aux;
	}
	file >> aux >> aux;
	while (aux != "_") {
		bool visited;
		file >> visited;
		visitedRooms[ecs::FIRE_MAP][std::stoi(aux)] = visited;
		file >> aux;
	}
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
	if (doNotDetectKeyboardInput && InputHandler::instance()->allKeysUp()) {
		doNotDetectKeyboardInput = false;
	}
	
	if (!doNotDetectKeyboardInput) {
		if (InputHandler::instance()->isKeyJustDown(SDLK_ESCAPE)) {
			fade->getComponent<FadeTransitionComponent>()->setFunction([this]() { sdlutils().musics().at(sdlutils().levels().at(map_->getCurrentLevel()).bgsong).pauseMusic(); SoundEffect::haltChannel(); GameStateMachine::instance()->pushState(new PauseMenuState()); });
			fade->getComponent<FadeTransitionComponent>()->changeSpeed(2);
			fade->getComponent<FadeTransitionComponent>()->revert();
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
		auto pAttack = e->getComponent<PlayerAttack>();
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
					//en principio ahora que está bien parametrizado, podemos conservar el rebote con el techo en todos los casos
					//if (!(physics->getWater()) || (physics->getWater() && health->getElement() == ecs::Water))
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

		//colisiones con el material de agua 
		int j = 0;
		std::vector <Entity*> water = mngr_->getEntities(ecs::_grp_WATER);
		for (Entity* w : water) {
			if (w->getComponent<ActiveWater>()->getActive()) {
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
			if (ents->hasComponent<ElementObject>()) {
				mngr_->getPlayer()->getComponent<PlayerInput>()->unlockElement(ents->getComponent<ElementObject>()->getElement());
				mngr_->getPlayer()->getComponent<PlayerAnimationComponent>()->changeElem(ents->getComponent<ElementObject>()->getElement());
				mngr_->getPlayer()->getComponent<PlayerAnimationComponent>()->setState(VANISH);
				map_->unlockElement(ents->getComponent<ElementObject>()->getElement());
				ents->setAlive(false);
			}
			else
				ents->getComponent<InteractionComponent>()->interact();
            interact = true;
			std::cout << "interacción" << std::endl;
        }
        interactionIt++;
    }
}

void PlayState::update() {
	checkCollisions({ player_ });
	checkCollisions(enemies[map_->getCurrentRoom()]);
	
	GameState::update();
}

void PlayState::AddEnredadera() {
	if (player_->getComponent<Health>()->getElement() == ecs::Earth) {
		Entity* aux = (*interactionIt);
		aux->getComponent<VineManager>()->addVine();
	}
}

void PlayState::Teleport() {
	if (player_->getComponent<Health>()->getElement() == ecs::Light) {
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
		sdlutils().soundEffects().at("teleport").play(0, ecs::_channel_ALERTS);
	}
}

void PlayState::Save() {
	map_->playFadeOutAnimation();
	lastSanctuary = getCurrentInteraction();
}

void PlayState::AddLifeShard(int id) {
	player_->getComponent<Health>()->addLifeShard(id);
	map_->addShard(id);
}

// AQUÍ SE GUARDA PARTIDA
void PlayState::endRest() {
    player_->getComponent<Health>()->saveSactuary(lastSanctuary);
	// Guardar datos en archivo
	std::string hola = "../resources/saves/temporalUniqueSave.sv";
	std::ofstream saveFile(hola);

	player_->getComponent<Health>()->saveToFile(saveFile);
	player_->getComponent<PlayerInput>()->saveToFile(saveFile);
	map_->saveToFile(saveFile);
	std::string rooms = "";
	for (int i = 0; i < visitedRooms[ecs::EARTH_MAP].size(); ++i) {
		if (visitedRooms[ecs::EARTH_MAP][i]) rooms += (std::to_string(i) + " 1 ");
		else rooms += (std::to_string(i) + " 0 ");
	}
	saveFile << "earth_map_rooms " << rooms << "_" << std::endl;

	rooms = "";
	for (int i = 0; i < visitedRooms[ecs::WATER_MAP].size(); ++i) {
		if (visitedRooms[ecs::WATER_MAP][i]) rooms += (std::to_string(i) + " 1 ");
		else rooms += (std::to_string(i) + " 0 ");
	}
	saveFile << "water_map_rooms " << rooms << "_" << std::endl;

	rooms = "";
	for (int i = 0; i < visitedRooms[ecs::FIRE_MAP].size(); ++i) {
		if (visitedRooms[ecs::FIRE_MAP][i]) rooms += (std::to_string(i) + " 1 ");
		else rooms += (std::to_string(i) + " 0 ");
	}
	saveFile << "fire_map_rooms " << rooms << "_" << std::endl;
	if (saveFile.fail()) std::cout << "FALLÉ GENTE" << std::endl;
}
