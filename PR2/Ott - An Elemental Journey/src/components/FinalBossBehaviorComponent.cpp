#include "FinalBossBehaviorComponent.h"
#include "Health.h"
#include "Image.h"
#include "WaterBubbleComponent.h"
#include "FireWallComponent.h"
#include "FistComponent.h"
FinalBossBehaviorComponent::FinalBossBehaviorComponent()
{
	currentElement = rand() % 4;
	bossTransform = nullptr; bossHealth = nullptr;
}

void FinalBossBehaviorComponent::initComponent()
{
	bossHealth = ent_->getComponent<Health>();
	bossTransform = ent_->getComponent<Transform>();
}

void FinalBossBehaviorComponent::update()
{
	//Temporizador de ataque
	if (SDL_GetTicks() - lastAttack >= timeBetweenAttacks) {
		lastAttack = SDL_GetTicks();

		//Switch de los diferentes ataques del boss
		switch (currentElement)
		{
		case 0: std::cout << "Ataque tierra boss final" << std::endl; break;
		case 1: std::cout << "Ataque agua boss final" << std::endl; spawnBubbles(); break;
		case 2: std::cout << "Ataque fuego boss final" << std::endl; spawnFireWall(); break;
		case 3: std::cout << "Ataque oscuridad boss final" << std::endl; break;
		default: std::cout << "Ataque generico boss final" << std::endl; fist(); break;
		}
		//Cambia de elemento aleatoriamente
		int lastElem = currentElement;
		do {
			currentElement = rand() % 4;
		} while (lastElem == currentElement);

	}
}

void FinalBossBehaviorComponent::spawnBubbles() //Ataque de agua 
{
	// Transform del boss
	auto pTransf = ent_->getComponent<Transform>();
	// Burguja
	Entity* bubble = mngr_->addEntity(ecs::_grp_BUBBLE);

	bubble->addComponent<Transform>(pTransf->getPosition(), BUBBLE_DIM * pTransf->getScale(), BUBBLE_DIM * pTransf->getScale());
	bubble->addComponent<Image>(&sdlutils().images().at("attackBubble"));
	bubble->addComponent<Health>(100, ecs::Water);
	bubble->addComponent<WaterBubbleComponent>();
}

void FinalBossBehaviorComponent::spawnFireWall() //Ataque fuego
{
	// Transform del boss
	auto pTransf = ent_->getComponent<Transform>();
	// Burguja
	Entity* fireW = mngr_->addEntity(ecs::_grp_PROYECTILES);

	fireW->addComponent<Transform>(pTransf->getPosition() - Vector2D(200, FIREWALL_HEIGHT / 2), FIREWALL_WIDTH * pTransf->getScale(), FIREWALL_HEIGHT * pTransf->getScale());
	fireW->addComponent<Image>(&sdlutils().images().at("pixelWhite"));
	fireW->addComponent<FireWallComponent>(Vector2D(1, 0));
}

void FinalBossBehaviorComponent::spawnBlackHole() {

	// Transform del boss
	auto pTransf = ent_->getComponent<Transform>();
	// Agujero negro
	Entity* blackHole = mngr_->addEntity(ecs::_grp_BUBBLE);

	blackHole->addComponent<Transform>(pTransf->getPosition(), BUBBLE_DIM * pTransf->getScale(), BUBBLE_DIM * pTransf->getScale());
	blackHole->addComponent<Image>(&sdlutils().images().at("attackBubble"));
	blackHole->addComponent<Health>(100, ecs::Dark);
	blackHole->addComponent<WaterBubbleComponent>();

}

void FinalBossBehaviorComponent::fist() {

	//// Transform del boss
	//auto pTransf = ent_->getComponent<Transform>();
	//// Burguja
	//Entity* fist = mngr_->addEntity(ecs::_grp_PROYECTILES);

	//fist->addComponent<Transform>(Vector2D(0-FIST_SIZE, FIST_SIZE*2), FIST_SIZE,FIST_SIZE);
	//fist->addComponent<Image>(&sdlutils().images().at("pixelWhite"));
	//fist->addComponent<FistComponent>();

}
