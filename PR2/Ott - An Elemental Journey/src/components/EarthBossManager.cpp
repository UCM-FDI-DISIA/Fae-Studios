#include "EarthBossManager.h"
#include "ImageVine.h"
#include "../sdlutils/SDLUtils.h"
#include "GrowVine.h"
#include "../utils/Vector2D.h"
#include "FramedImage.h"

EarthBossManager::EarthBossManager(SDL_Rect rD) : roomDimensions(rD) {
	//initializeEntities();
	animController = ent_->addComponent<EarthBossAnimationController>(this);
}
void EarthBossManager::setState(int newState) {
	state = newState;
	switch (newState) {
		case PRESENTATION:animController->setState(anims::EARTHBOSSPRESENT, presentBoss); break;
		case ATTACKVERTICAL:animController->setState(anims::EARTHBOSSATTACK, boss); break;
		case PAUSE:animController->setState(anims::PAUSE_ANIM, pause); break;
		//case WARNING:animController->setState(anims::WARNINGEARTH, presentBoss); break;
	}
	

}
void EarthBossManager::initializeEntities() {

	//CREACIÓN DE LAS 3 ENREDADERAS LATERALES
	SDL_Rect vine_Rect;
	vine_Rect.x = roomDimensions.x + roomDimensions.w + offSet;
	vine_Rect.w = roomDimensions.w;
	vine_Rect.h = roomDimensions.h/3;
	Vector2D finPosVine = Vector2D(roomDimensions.x, roomDimensions.y);
	for (int i = 0; i < NUM_VINES; ++i) {
		//COLISIONAR Y DAÑAR AL JUGADOR
		Entity* vine = mngr_->addEntity(ecs::_grp_GROUND);
		vine->addComponent<ImageVine>(&sdlutils().images().at("vineBoss"), sdlutils().images().at("vineBoss").getNumRows(), sdlutils().images().at("vineBoss").getNumCols());
		vine_Rect.y = roomDimensions.y + (vine_Rect.h * i);
		vine->addComponent<Transform>(vine_Rect);
		finPosVine.setX(vine_Rect.y + (vine_Rect.h * i));
		vine->addComponent<GrowVine>(finPosVine, 2, -1);
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
		warning->addComponent<FramedImage>(&sdlutils().images().at("warning"), sdlutils().images().at("warning").getNumRows(), sdlutils().images().at("warning").getNumCols());
		warning_Rect.x = roomDimensions.x + (warning_Rect.w * j);
		warning->addComponent<Transform>(warning_Rect);
		warningVector.push_back({ warning, j });
	}

	//CREACIÓN DE LOS 3 WARNINGS LATERALES
	warning_Rect.x -= offSet;
	warning_Rect.y = roomDimensions.y;
	warning_Rect.w = sdlutils().images().at("warning").width();
	warning_Rect.h = roomDimensions.h/3;
	for (int j = 0; j < 3; ++j) {
		Entity* warning = mngr_->addEntity(ecs::_grp_MINIBOSS);
		warning->addComponent<FramedImage>(&sdlutils().images().at("warning"), sdlutils().images().at("warning").getNumRows(), sdlutils().images().at("warning").getNumCols());
		warning_Rect.y = roomDimensions.y + (warning_Rect.h * j);
		warning->addComponent<Transform>(warning_Rect);
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
	boss->addComponent<FramedImage>(&sdlutils().images().at("animationWorm"), sdlutils().images().at("animationWorm").getNumRows(), sdlutils().images().at("animationWorm").getNumCols());
	boss->addComponent<Transform>(boss_Rect);
	boss->addComponent<GrowVine>(finPosBoss, 2, 1);
	//HEALTH, INTERSECCIONAR Y DAÑAR AL JUGADOR

	//CREACIÓN DEL PAUSA
	pause->addComponent<FramedImage>(&sdlutils().images().at("pixel"), sdlutils().images().at("pixel").getNumRows(), sdlutils().images().at("pixel").getNumCols());
	pause->addComponent<Transform>(boss_Rect);

	//CREACIÓN DE LA PRESENTACIÓN
	SDL_Rect presentation_Rect;
	presentation_Rect.x = roomDimensions.x;
	presentation_Rect.y = roomDimensions.y;
	presentation_Rect.h = roomDimensions.h;
	presentation_Rect.w = roomDimensions.w;
	presentBoss = mngr_->addEntity(ecs::_grp_MINIBOSS);
	presentBoss->addComponent<FramedImage>(&sdlutils().images().at("animationWorm"), sdlutils().images().at("animationWorm").getNumRows(), sdlutils().images().at("animationWorm").getNumCols());
	presentBoss->addComponent<Transform>(presentation_Rect);
}

void EarthBossManager::update() {
	if (isFight) {
		if(state == WARNING){}
		else if(state == ATTACKVERTICAL){}
		else if(state == ATTACKHORIZONTAL){}

	}
}
void EarthBossManager::verticalAttackPosition() {
	//QUE LA SALA SEPA DONDE ESTA EL JUGADOR Y SE DIVIDA ENTRE CINCO PARA CAMBIAR LA
	//POS DEL BOSS VERTICAL
}