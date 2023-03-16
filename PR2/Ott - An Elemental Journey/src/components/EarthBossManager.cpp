#include "EarthBossManager.h"
#include "ImageVine.h"
#include "../sdlutils/SDLUtils.h"
#include "GrowVine.h"
#include "../utils/Vector2D.h"
#include "FramedImage.h"

void EarthBossManager::initComponent() {
	//INICIALIZACION DEL PLAYER Y TRANSFORM
	player = mngr_->getPlayer();
	//tr_ = ent_->getComponent<Transform>();
}
EarthBossManager::EarthBossManager(SDL_Rect rD) : roomDimensions(rD) {
}
void EarthBossManager::setState(int newState) {
	state = newState;
	switch (newState) {
		case PRESENTATION:animController->setState(anims::EARTHBOSSPRESENT, presentBoss, nullptr); break;
		case ATTACKVERTICAL:animController->setState(anims::EARTHBOSSATTACK, boss, nullptr); break;
		case PAUSE:animController->setState(anims::PAUSE_ANIM, pause, nullptr); break;
		//case WARNING:animController->setState(anims::WARNINGEARTH, presentBoss); break;
	}
}
void EarthBossManager::initializeEntities() {
	animController = ent_->addComponent<EarthBossAnimationController>(this);
	//CREACIÓN DE LAS 3 ENREDADERAS LATERALES
	SDL_Rect vine_Rect;
	vine_Rect.x = roomDimensions.x + roomDimensions.w + offSet;
	vine_Rect.w = roomDimensions.w;
	vine_Rect.h = roomDimensions.h/3;
	Vector2D finPosVine = Vector2D(roomDimensions.x, roomDimensions.y);
	for (int i = 0; i < NUM_VINES; ++i) {
		//COLISIONAR Y DAÑAR AL JUGADOR
		Entity* vine = mngr_->addEntity(ecs::_grp_MINIBOSS);
		vine_Rect.y = roomDimensions.y + (vine_Rect.h * i);
		vine->addComponent<Transform>(vine_Rect);
		vine->addComponent<ImageVine>(&sdlutils().images().at("vineBoss"), sdlutils().images().at("vineBoss").getNumRows(), sdlutils().images().at("vineBoss").getNumCols());
		finPosVine.setX(vine_Rect.y + (vine_Rect.h * i));
		vine->addComponent<GrowVine>(finPosVine, 2, -1, "horizontal");
		vineVector.push_back(vine);
	}

	//CREACIÓN DE LOS 5 WARNINGS SUPERIORES
	SDL_Rect warning_Rect;
	warning_Rect.x = roomDimensions.x;
	warning_Rect.y = roomDimensions.y + offSet;
	warning_Rect.w = roomDimensions.w / 5;
	warning_Rect.h = sdlutils().images().at("warning").height();
	for (int j = 0; j < 5; ++j) {
		Entity* warning = mngr_->addEntity(ecs::_grp_MINIBOSS);
		warning->addComponent<Transform>(warning_Rect);
		warning->addComponent<FramedImage>(&sdlutils().images().at("warning"), sdlutils().images().at("warning").getNumRows(), sdlutils().images().at("warning").getNumCols());
		warning_Rect.x = roomDimensions.x + (warning_Rect.w * j);
		warningVector.push_back({ warning, j });
	}

	//CREACIÓN DE LOS 3 WARNINGS LATERALES
	warning_Rect.x -= offSet;
	warning_Rect.y = roomDimensions.y;
	warning_Rect.w = sdlutils().images().at("warning").width();
	warning_Rect.h = roomDimensions.h/3;
	for (int j = 0; j < 3; ++j) {
		Entity* warning = mngr_->addEntity(ecs::_grp_MINIBOSS);
		warning->addComponent<Transform>(warning_Rect);
		warning->addComponent<FramedImage>(&sdlutils().images().at("warning"), sdlutils().images().at("warning").getNumRows(), sdlutils().images().at("warning").getNumCols());
		warning_Rect.y = roomDimensions.y + (warning_Rect.h * j);
		warningVector.push_back({ warning, j+5 });
	}

	//CREACIÓN DEL BOSS
	SDL_Rect boss_Rect;
	boss_Rect.x = roomDimensions.x;
	boss_Rect.y = roomDimensions.y - offSet;
	boss_Rect.h = roomDimensions.h;
	boss_Rect.w = roomDimensions.w / 5;
	Vector2D finPosBoss = Vector2D{ (float)boss_Rect.x , (float)boss_Rect.y + (float)boss_Rect.h };
	boss = mngr_->addEntity(ecs::_grp_MINIBOSS);
	boss->addComponent<Transform>(boss_Rect);
	boss->addComponent<FramedImage>(&sdlutils().images().at("animationWorm"), sdlutils().images().at("animationWorm").getNumRows(), sdlutils().images().at("animationWorm").getNumCols());
	boss->addComponent<GrowVine>(finPosBoss, 2, 1, "vertical");
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
void EarthBossManager::update() {
	if (isFight) {
		if(state == WARNING){}
		else if(state == ATTACKVERTICAL){}
		else if(state == ATTACKHORIZONTAL){}

	}
}
