#include "EarthBossManager.h"
#include "ImageVine.h"
#include "../sdlutils/SDLUtils.h"
#include "GrowVine.h"
#include "../utils/Vector2D.h"
#include "FramedImage.h"

void EarthBossManager::initComponent() {
	//INICIALIZACION DEL PLAYER
	player = mngr_->getPlayer();
	animController = ent_->addComponent<EarthBossAnimationController>(this);
}
EarthBossManager::EarthBossManager(SDL_Rect rD) : roomDimensions(rD) {
}
void EarthBossManager::setState(int newState) {
	switch (newState) {
		case PRESENTATION:animController->setState(anims::EARTHBOSSPRESENT, presentBoss, nullptr); break;
		case ATTACKVERTICAL:animController->setState(anims::EARTHBOSSATTACK, boss, nullptr); break;
		case PAUSE:animController->setState(anims::PAUSE_ANIM, pause, nullptr); break;
	}
}
void EarthBossManager::initializeEntities() {
	//animController = ent_->addComponent<EarthBossAnimationController>(this);
	//CREACIÓN DE LAS 6 ENREDADERAS LATERALES
	SDL_Rect vine_Rect;
	vine_Rect.x = roomDimensions.x + roomDimensions.w + offSet;
	vine_Rect.w = roomDimensions.w;
	vine_Rect.h = roomDimensions.h/3;
	for (int i = 0; i < NUM_VINES; ++i) {
		//COLISIONAR Y DAÑAR AL JUGADOR
		Vector2D finPosVine = Vector2D(roomDimensions.x, roomDimensions.y + (roomDimensions.h / 3)*i);
		Entity* vine = mngr_->addEntity(ecs::_grp_MINIBOSS);
		if (i % 2 == 0)vine_Rect.y = roomDimensions.y + (vine_Rect.h * ((i + 1) / 2) + (vine_Rect.h / 5));
		else vine_Rect.y = ((vineVector[i - 1]->getComponent<Transform>()->getPosition().getY()) + (vine_Rect.h / 2.5));
		vine->addComponent<Transform>(vine_Rect);
		vine->addComponent<ImageVine>(&sdlutils().images().at("vineBoss"), sdlutils().images().at("vineBoss").getNumRows(), sdlutils().images().at("vineBoss").getNumCols());
		vine->addComponent<GrowVine>(finPosVine, 7, -1, "horizontal", true);
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
		warningVector.push_back({ warning, j });
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
		warningVector.push_back({ warning, j+5 });
	}

	//CREACIÓN DEL BOSS
	SDL_Rect boss_Rect;
	boss_Rect.x = roomDimensions.x;
	boss_Rect.y = roomDimensions.y - offSet;
	boss_Rect.h = roomDimensions.h;
	boss_Rect.w = roomDimensions.w / 5;
	Vector2D finPosBoss = Vector2D{ (float)roomDimensions.x , (float)roomDimensions.y + (float)roomDimensions.h };
	boss = mngr_->addEntity(ecs::_grp_MINIBOSS);
	boss->addComponent<Transform>(boss_Rect);
	boss->addComponent<FramedImage>(&sdlutils().images().at("animationWorm"), sdlutils().images().at("animationWorm").getNumRows(), sdlutils().images().at("animationWorm").getNumCols());
	boss->addComponent<GrowVine>(finPosBoss, 2, 1, "vertical", false);
	//HEALTH, INTERSECCIONAR Y DAÑAR AL JUGADOR

	//CREACIÓN DEL PAUSA
	pause = mngr_->addEntity(ecs::_grp_MINIBOSS);
	pause->addComponent<Transform>(boss_Rect);
	pause->addComponent<FramedImage>(&sdlutils().images().at("pixel"), sdlutils().images().at("pixel").getNumRows(), sdlutils().images().at("pixel").getNumCols());

	//CREACIÓN DE LA PRESENTACIÓN
	SDL_Rect presentation_Rect;
	presentation_Rect.x = roomDimensions.x;
	presentation_Rect.y = roomDimensions.y;
	presentation_Rect.h = roomDimensions.h;
	presentation_Rect.w = roomDimensions.w;
	presentBoss = mngr_->addEntity(ecs::_grp_MINIBOSS);
	presentBoss->addComponent<Transform>(presentation_Rect);
	presentBoss->addComponent<FramedImage>(&sdlutils().images().at("animationWorm"), sdlutils().images().at("animationWorm").getNumRows(), sdlutils().images().at("animationWorm").getNumCols());

	//CREACION DE LAS PLATAFORMAS
	SDL_Rect platform_Rect;
	platform_Rect.w = roomDimensions.x - (2 * offSet);
	platform_Rect.h = roomDimensions.h / 20;
	platform_Rect.x = roomDimensions.x + offSet;
	platform_Rect.y = vineVector[2]->getComponent<Transform>()->getRect().y + platform_Rect.h;
	for (int k = 0; k < 5; ++k) {
		Entity* platform = mngr_->addEntity(ecs::_grp_MINIBOSS);
		platform->addComponent<Transform>(platform_Rect.x, platform_Rect.y, platform_Rect.w, platform_Rect.h);
		platform_Rect.x = roomDimensions.x + offSet + ((roomDimensions.x / 5) * k);
		if (k % 2 == 0) platform_Rect.y = vineVector[2]->getComponent<Transform>()->getRect().y + platform_Rect.h;
		else platform_Rect.y = vineVector[1]->getComponent<Transform>()->getRect().y + platform_Rect.h;
		platformVector.push_back({ platform, k });
		//platform->addComponent<FramedImage>(); // rellenar
	}

	animController->setAnimation(true);
	setState(PRESENTATION);
}

void EarthBossManager::verticalAttackPosition() {
	//QUE LA SALA SEPA DONDE ESTA EL JUGADOR Y SE DIVIDA ENTRE CINCO PARA CAMBIAR LA
	//POS DEL BOSS VERTICAL
	auto tr_ = boss->getComponent<Transform>();
	auto playerPos = player->getComponent<Transform>()->getPosition().getX();
	if (playerPos < (roomDimensions.x + (roomDimensions.w / 5))) tr_->setPosition(Vector2D(roomDimensions.x, roomDimensions.y - offSet));
	else if (playerPos < (roomDimensions.x + (2 * (roomDimensions.w / 5))))  tr_->setPosition(Vector2D(roomDimensions.x + (roomDimensions.w / 5), roomDimensions.y - offSet));
	else if (playerPos < (roomDimensions.x + (3 * (roomDimensions.w / 5))))  tr_->setPosition(Vector2D(roomDimensions.x + (2 * (roomDimensions.w / 5)), roomDimensions.y - offSet));
	else if (playerPos < (roomDimensions.x + (4 * (roomDimensions.w / 5))))  tr_->setPosition(Vector2D(roomDimensions.x + (3 * (roomDimensions.w / 5)), roomDimensions.y - offSet));
	else tr_->setPosition(Vector2D(roomDimensions.x + (4 * (roomDimensions.w / 5)), roomDimensions.y - offSet));

}

void EarthBossManager::horizontalAttack() {
	if (vine1 != -1 && vine2 != -1) {
		if (vine1 == 0 || vine2 == 0) {
			vineVector[0]->getComponent<GrowVine>()->isGrowing(true);
			vineVector[1]->getComponent<GrowVine>()->isGrowing(true);
		}
		if (vine1 == 1 || vine2 == 1) {
			vineVector[2]->getComponent<GrowVine>()->isGrowing(true);
			vineVector[3]->getComponent<GrowVine>()->isGrowing(true);
		}
		if (vine1 == 2 || vine2 == 2) {
			vineVector[4]->getComponent<GrowVine>()->isGrowing(true);
			vineVector[5]->getComponent<GrowVine>()->isGrowing(true);
		}
	}
}

void EarthBossManager::choosingVine() {
	int aux = rand() % 3;
	
	for (int i = 0; i < 3; ++i) {
		if (i != aux) {
			if (vine1 == -1) vine1 = i;
			else vine2 = i;
		}
	}
}

void EarthBossManager::update() {
	if (isFight) {
		stateManagment();
	}
}

void EarthBossManager::stateManagment() {
	if (changeState) {
		if (actualState != ATTACKHORIZONTAL) {
			std::cout << "Realizando " << actualState << std::endl;
			animController->setAnimation(true);
			if(actualState == WARNING) {
				choosingVine();
				animController->setState(anims::WARNINGEARTH, warningVector[5+ vine1].warning, warningVector[5+ vine2].warning);
			}
			else if (actualState != WARNING) {
				setState(states[actualState]);
			}
			
			if (actualState < states.size() - 1)  ++actualState;
			else actualState = 0;
		}
		else{
			horizontalAttack();
			std::cout << "Realizando ataque horizontal" << std::endl;
			animController->setAnimation(false);
		}
		changeState = false;
	}
}