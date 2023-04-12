#include "FinalBossBehaviorComponent.h"
#include "Health.h"
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
	}
}
