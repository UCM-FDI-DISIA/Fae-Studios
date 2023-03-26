#include "EarthBossManager.h"
#include "ImageVine.h"
#include "../sdlutils/SDLUtils.h"
#include "GrowVine.h"
#include "../utils/Vector2D.h"
#include "FramedImage.h"
#include "EarthBossAttack.h"
#include "Health.h"
#include <time.h>
#include "Health.h"
#include "Trigger.h"
#include "EnterBossRoom.h"
void EarthBossManager::initComponent() {
	//INICIALIZACION DEL PLAYER
	player = mngr_->getPlayer();
	animController = ent_->addComponent<EarthBossAnimationController>(this);

	//CREAR TRIGGER
	trigger = mngr_->addEntity(ecs::_grp_TRIGGER);
	SDL_Rect trigger_Rect;
	trigger_Rect.x = roomDimensions.x + 200;
	trigger_Rect.y = roomDimensions.y;
	trigger_Rect.w = roomDimensions.w;
	trigger_Rect.h = roomDimensions.h;
	trigger->addComponent<Transform>(trigger_Rect);
	trigger->addComponent<EnterBossRoom>(roomDimensions);
	trigger->addComponent<Trigger>();
}
EarthBossManager::EarthBossManager(SDL_Rect rD) : roomDimensions(rD) {
}
void EarthBossManager::setState(int newState) {
	switch (newState) {
		case PRESENTATION:animController->setState(anims::EARTHBOSSPRESENT, presentBoss, nullptr); break;
		case ATTACKVERTICAL:animController->setState(anims::EARTHBOSSATTACK, boss, nullptr); break;
		case PAUSE:animController->setState(anims::PAUSE_ANIM, pause, nullptr); break;
		case MINIPAUSE:animController->setState(anims::MINIPAUSE_ANIM, pause, nullptr); break;
	}
}
void EarthBossManager::initializeEntities() {
	//animController = ent_->addComponent<EarthBossAnimationController>(this);
	//CREACIÓN DE LAS 6 ENREDADERAS LATERALES
	SDL_Rect vine_Rect;
	vine_Rect.x = roomDimensions.x + roomDimensions.w + offSet;
	vine_Rect.w = roomDimensions.w;
	//vine_Rect.h = sdlutils().images().at("vineBoss").height();
	vine_Rect.h = roomDimensions.h / 6 + offSet;
	for (int i = 0; i < NUM_VINES; ++i) {
		//COLISIONAR Y DAÑAR AL JUGADOR
		Vector2D finPosVine = Vector2D(roomDimensions.x + offSet*2, roomDimensions.y + (roomDimensions.h / 6)*i);
		Entity* vine = mngr_->addEntity(ecs::_grp_MINIBOSS);
		if (i % 2 == 0)vine_Rect.y = roomDimensions.y + (roomDimensions.h / 6 )*i + vine_Rect.h - offSet*2;
		else vine_Rect.y = ((vineVector[i - 1]->getComponent<Transform>()->getPosition().getY()) + (vine_Rect.h / 2.5));
		vine->addComponent<Transform>(vine_Rect);
		vine->addComponent<ImageVine>(&sdlutils().images().at("vineBoss"), 1, false);
		vine->addComponent<GrowVine>(finPosVine, 7, -1, "horizontal", true);
		//vine->addComponent<EarthBossAttack>();
		vine->getComponent<GrowVine>()->isGrowing(false);
		vineVector.push_back(vine);
	}

	// CREACION DE LOS 5 WARNINGS SUPERIORES
	SDL_Rect warning_Rect;
	warning_Rect.x = roomDimensions.x;
	warning_Rect.y = roomDimensions.y + offSet;
	warning_Rect.w = (sdlutils().images().at("warning").width() / 28) * 2;
	warning_Rect.h = sdlutils().images().at("warning").height() * 2;
	for (int j = 0; j < 5; ++j) {
		float offsetAux = ((roomDimensions.w / 5) - ((sdlutils().images().at("warning").width() / 28) * 2)) / 2;
		Entity* warning = mngr_->addEntity(ecs::_grp_MINIBOSS);
		warning_Rect.x = roomDimensions.x + +offsetAux + ((roomDimensions.w/5) * j);
		warning->addComponent<Transform>(warning_Rect);
		warning->addComponent<FramedImage>(&sdlutils().images().at("warning"), sdlutils().images().at("warning").getNumRows(), sdlutils().images().at("warning").getNumCols());
		warningVector.push_back(warning);
	}

	//CREACIÓN DE LOS 3 WARNINGS LATERALES
	warning_Rect.x -= offSet;
	warning_Rect.y = roomDimensions.y;;
	warning_Rect.w = (sdlutils().images().at("warning").width()/28)*2;
	warning_Rect.h = sdlutils().images().at("warning").height()*2;
	for (int j = 0; j < 3; ++j) {
		float offsetAux = ((roomDimensions.h / 3) - (sdlutils().images().at("warning").height() * 2)) / 2;
		Entity* warning = mngr_->addEntity(ecs::_grp_MINIBOSS);
		warning_Rect.y = roomDimensions.y + +offsetAux+ ((roomDimensions.h / 3) * j);
		warning->addComponent<Transform>(warning_Rect);
		warning->addComponent<FramedImage>(&sdlutils().images().at("warning"), sdlutils().images().at("warning").getNumRows(), sdlutils().images().at("warning").getNumCols());
		warningVector.push_back(warning);
	}

	//CREACIÓN DEL BOSS
	SDL_Rect boss_Rect;
	boss_Rect.x = roomDimensions.x;
	boss_Rect.y = roomDimensions.y - roomDimensions.h;
	boss_Rect.h = roomDimensions.h;
	boss_Rect.w = roomDimensions.w / 5;
    finPosBoss = Vector2D{ (float)roomDimensions.x , (float)roomDimensions.y + (float)roomDimensions.h };
    iniPosBoss = Vector2D{ (float)roomDimensions.x , (float)roomDimensions.y - (float)roomDimensions.h };
	boss = mngr_->addEntity(ecs::_grp_MINIBOSS);
	boss->addComponent<Transform>(boss_Rect);
	boss->addComponent<FramedImage>(&sdlutils().images().at("fallingWorm"), sdlutils().images().at("fallingWorm").getNumRows(), sdlutils().images().at("fallingWorm").getNumCols());
	healthBar = mngr_->addEntity(ecs::_grp_UI);
	healthBar->addComponent<BossHealthBar>(ent_, 1, &sdlutils().images().at("bossHealthBar"), &sdlutils().images().at("bossLife"));
	boss->addComponent<Health>(healthBar->getComponent<BossHealthBar>(), 2, ecs::Earth, false);
	boss->addComponent<EarthBossAttack>();

	//CREACIÓN DEL PAUSA
	pause = mngr_->addEntity(ecs::_grp_MINIBOSS);
	pause->addComponent<Transform>(boss_Rect);
	pause->addComponent<FramedImage>(&sdlutils().images().at("pixel"), sdlutils().images().at("pixel").getNumRows(), sdlutils().images().at("pixel").getNumCols());

	//CREACIÓN DE LA PRESENTACIÓN
	SDL_Rect presentation_Rect;
	presentation_Rect.x = roomDimensions.x + (roomDimensions.w/4)*2;
	presentation_Rect.y = roomDimensions.y + (roomDimensions.h - (roomDimensions.h / 2.5) + 10);
	presentation_Rect.h = roomDimensions.h / 2;
	presentation_Rect.w = roomDimensions.w / 2;
	presentBoss = mngr_->addEntity(ecs::_grp_MINIBOSS);
	presentBoss->addComponent<Transform>(presentation_Rect);
	presentBoss->addComponent<FramedImage>(&sdlutils().images().at("animationWorm"), sdlutils().images().at("animationWorm").getNumRows(), sdlutils().images().at("animationWorm").getNumCols());

	//CREACION DE LA PLATAFORMA CON LA ENREDADERA
	SDL_Rect platformVine_Rect;
	platformVine_Rect.w = sdlutils().images().at("vinePlatform").width()*2;
	platformVine_Rect.h = sdlutils().images().at("vinePlatform").height()*2;
	platformVine_Rect.x = platformVector[0]->getComponent<Transform>()->getPosition().getX() - 15;
	platformVine_Rect.y = platformVector[0]->getComponent<Transform>()->getPosition().getY() + platformVine_Rect.h* 2;
	vinePlatform = mngr_->addEntity(ecs::_grp_INTERACTION);
	vinePlatform->addComponent<Transform>(platformVine_Rect);
	vinePlatform->addComponent<FramedImage>(&sdlutils().images().at("vinePlatform"), sdlutils().images().at("vinePlatform").getNumRows(), sdlutils().images().at("vinePlatform").getNumCols());
	vinePlatform->addComponent<EarthBossAttack>();
	createVinePlatform();

	animController->setAnimation(true);
	setState(PRESENTATION);
}

void EarthBossManager::verticalAttackPosition() {
	//QUE LA SALA SEPA DONDE ESTA EL JUGADOR Y SE DIVIDA ENTRE CINCO PARA CAMBIAR LA
	//POS DEL BOSS VERTICAL
	auto tr_ = boss->getComponent<Transform>();
	auto playerPos = player->getComponent<Transform>()->getPosition().getX();
	if (playerPos < (roomDimensions.x + (roomDimensions.w / 5))) {
		tr_->setPosition(iniPosBoss);
		bossWarning = 0;
	}
	else if (playerPos < (roomDimensions.x + (2 * (roomDimensions.w / 5)))) {
		tr_->setPosition(Vector2D(roomDimensions.x + (roomDimensions.w / 5), roomDimensions.y - roomDimensions.h));
		bossWarning = 1;
	}
	else if (playerPos < (roomDimensions.x + (3 * (roomDimensions.w / 5)))) {
		tr_->setPosition(Vector2D(roomDimensions.x + (2 * (roomDimensions.w / 5)), roomDimensions.y - roomDimensions.h));
		bossWarning = 2;
	}
	else if (playerPos < (roomDimensions.x + (4 * (roomDimensions.w / 5)))) {
		tr_->setPosition(Vector2D(roomDimensions.x + (3 * (roomDimensions.w / 5)), roomDimensions.y - roomDimensions.h));
		bossWarning = 3;
	}
	else {
		tr_->setPosition(Vector2D(roomDimensions.x + (4 * (roomDimensions.w / 5)), roomDimensions.y - roomDimensions.h));
		bossWarning = 4;
	} 
}

void EarthBossManager::horizontalAttack() {
	switch (vine1)
	{
		case 1:
			refvine1 = vineVector[0];
			refvine2 = vineVector[1]; 
			break;
		case 2:
			refvine1 = vineVector[2];
			refvine2 = vineVector[3]; 
			break;
		case 3:
			refvine1 = vineVector[4];
			refvine2 = vineVector[5]; 
			break;
	}

	switch (vine2)
	{
		case 1:
			refvine3 = vineVector[0];
			refvine4 = vineVector[1];
			break;
		case 2:
			refvine3 = vineVector[2];
			refvine4 = vineVector[3];
			break;
		case 3:
			refvine3 = vineVector[4];
			refvine4 = vineVector[5];
			break;
	}
	refvine1->getComponent<GrowVine>()->isGrowing(true);
	refvine2->getComponent<GrowVine>()->isGrowing(true);
	refvine3->getComponent<GrowVine>()->isGrowing(true);
	refvine4->getComponent<GrowVine>()->isGrowing(true);
	
}

void EarthBossManager::choosingVine() {
	srand(time(NULL) * _getpid() * rand());
	int aux = rand() % 4;
	while (aux == numRandVine || aux == 0) {
		aux = rand() % 4;
	};
	for (int i = 1; i < 4; ++i) {
		if (i != aux) {
			if (vine1 == -1) vine1 = i;
			else vine2 = i;
		}
	}
	numRandVine = aux;
}

void EarthBossManager::update() {
	if (isFight) {
		stateManagment();
		if (attackingHorizontally) {
			if (!refvine1->getComponent<GrowVine>()->getGrow()) {
				attackingHorizontally = false;
				vine1 = -1;
				vine2 = -1;
				if (actualState < states.size() - 1)  ++actualState;
				else actualState = 1;
				changeState = true;
			}
		}
		else if (attackingVertically) {
			auto bossPos = boss->getComponent<Transform>();
			if (bossPos->getPosition().getY() < finPosBoss.getY()) {
				if (bossPos->getPosition().getX() <= vinePlatform->getComponent<Transform>()->getPosition().getX() &&
					(bossPos->getPosition().getX() + bossPos->getWidth()) >= vinePlatform->getComponent<Transform>()->getPosition().getX()) {
					verticalSpeed = 1;
				}
				bossPos->setPosition(Vector2D(bossPos->getPosition().getX(), bossPos->getPosition().getY() + verticalSpeed));
			}
			else {
				if (actualState < states.size() - 1)  ++actualState;
				else actualState = 1;
				bossPos->setPosition(Vector2D(bossPos->getPosition().getX(), roomDimensions.y - roomDimensions.h));

				attackingVertically = false;
				changeState = true;
				createVinePlatform();
				verticalSpeed = 3;
			}
		}
	}
}
void EarthBossManager::createVinePlatform() {
	srand(time(NULL) * _getpid() * rand());
	int aux = rand() % 5;
	SDL_Rect platformVine_Rect = vinePlatform->getComponent<Transform>()->getRect();
	platformVine_Rect.x = platformVector[aux]->getComponent<Transform>()->getPosition().getX() - 15;
	platformVine_Rect.y = platformVector[aux]->getComponent<Transform>()->getPosition().getY() - 5;
	vinePlatform->getComponent<Transform>()->setPosition(Vector2D(platformVine_Rect.x, platformVine_Rect.y));
}

void EarthBossManager::stateManagment() {
	if (changeState) {
		if (states[actualState] == PRESENTATION) {
			if (animController->getPresentationReps() < 3) {
				presentBoss->getComponent<Transform>()->setPosition(Vector2D(presentBoss->getComponent<Transform>()->getPosition().getX() - presentBoss->getComponent<Transform>()->getWidth()/2, presentBoss->getComponent<Transform>()->getPosition().getY()));
			}
			else {
				player->getComponent<PhysicsComponent>()->Resume();
				setState(states[++actualState]);
			} 
		}
		else {
			if (states[actualState] != ATTACKHORIZONTAL && states[actualState] != ATTACKVERTICAL) {
				animController->setAnimation(true);
				if(states[actualState] == WARNING) {
					if (states[actualState +2] == ATTACKHORIZONTAL) choosingVine();
					else if (states[actualState + 2] == ATTACKVERTICAL) verticalAttackPosition();

					if (bossWarning != -1) {
						animController->setState(anims::WARNINGEARTH, warningVector[bossWarning], warningVector[bossWarning]);
						bossWarning = -1;
					}
					else animController->setState(anims::WARNINGEARTH, warningVector[4+ vine1], warningVector[4+ vine2]);
					
				}
				else if (states[actualState] != WARNING) {
					setState(states[actualState]);
				}
			
				if (actualState < states.size() - 1)  ++actualState;
				else actualState = 1;
			}
			else if(states[actualState] == ATTACKHORIZONTAL) {
				horizontalAttack();
				attackingHorizontally = true;
				animController->setAnimation(false);
			}
			else if(states[actualState] == ATTACKVERTICAL) {
				attackingVertically = true;
				animController->setAnimation(false);
			}
		}
		changeState = false;
	}
}

void EarthBossManager::die() {
	boss->getComponent<Transform>()->setPosition(Vector2D(boss->getComponent<Transform>()->getPosition().getX(), roomDimensions.y - roomDimensions.h));
	isFight = false;
	trigger->getComponent<EnterBossRoom>()->unlockDoors();
}