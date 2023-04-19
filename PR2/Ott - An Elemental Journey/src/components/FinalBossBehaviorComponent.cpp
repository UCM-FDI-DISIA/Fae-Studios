#include "FinalBossBehaviorComponent.h"
#include "Health.h"
#include "Image.h"
#include "WaterBubbleComponent.h"
#include "FireWallComponent.h"
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
		default: std::cout << "Ataque generico boss final" << std::endl; break;
		}
		//Cambia de elemento aleatoriamente
		int lastElem = currentElement;
		do{
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

	fireW->addComponent<Transform>(pTransf->getPosition() - Vector2D(200, FIREWALL_HEIGHT/2), FIREWALL_WIDTH * pTransf->getScale(), FIREWALL_HEIGHT * pTransf->getScale());
	fireW->addComponent<Image>(&sdlutils().images().at("pixelWhite"));
	fireW->addComponent<FireWallComponent>(Vector2D(1,0));
}
