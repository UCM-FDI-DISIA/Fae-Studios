#include "FinalBossBehaviorComponent.h"
#include "Health.h"
#include "Image.h"
#include "WaterBubbleComponent.h"
#include "FireWallComponent.h"
FinalBossBehaviorComponent::FinalBossBehaviorComponent(int time)
{
	timeBetweenAttacks = time;
	lastAttack = -time * 1000;
}

void FinalBossBehaviorComponent::initComponent()
{
	bossHealth = ent_->getComponent<Health>();
}

void FinalBossBehaviorComponent::update()
{
	//Temporizador de ataque
	if (SDL_GetTicks() - lastAttack >= timeBetweenAttacks * 1000) {
		lastAttack = SDL_GetTicks();

		//Switch de los diferentes ataques del boss
		int currentElem = (int)bossHealth->getElement();
		switch (currentElem)
		{
		case 1: std::cout << "Ataque tierra boss final" << std::endl; break;
		case 2: std::cout << "Ataque agua boss final" << std::endl; break;
		case 3: std::cout << "Ataque fuego boss final" << std::endl; break;
		case 4: std::cout << "Ataque oscuridad boss final" << std::endl; break;
		default: std::cout << "Ataque generico boss final" << std::endl; break;
		}
		//Cambia de elemento aleatoriamente
		int newElem = rand() % 4; newElem++;
		std::cout << newElem << std::endl;
		bossHealth->setElement(newElem);
		
		spawnFireWall();
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

void FinalBossBehaviorComponent::spawnFireWall()
{
	// Transform del boss
	auto pTransf = ent_->getComponent<Transform>();
	// Burguja
	Entity* fireW = mngr_->addEntity(ecs::_grp_PROYECTILES);

	fireW->addComponent<Transform>(pTransf->getPosition() - Vector2D(200, FIREWALL_HEIGHT/2), FIREWALL_WIDTH * pTransf->getScale(), FIREWALL_HEIGHT * pTransf->getScale());
	fireW->addComponent<Image>(&sdlutils().images().at("pixelWhite"));
	fireW->addComponent<FireWallComponent>(Vector2D(1,0));
}
