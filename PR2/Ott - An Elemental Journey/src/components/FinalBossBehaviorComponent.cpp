#include "FinalBossBehaviorComponent.h"
#include "Health.h"
#include "Image.h"
#include "WaterBubbleComponent.h"
#include "FireWallComponent.h"
#include "FistComponent.h"
#include "AttractionComponent.h"
#include "BlackHoleAnimationComp.h"
FinalBossBehaviorComponent::FinalBossBehaviorComponent(MapComponent* map) :Component()
{
	currentElement = rand() % 5;
	bossTransform = nullptr; bossHealth = nullptr;
	map_ = map;
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
		case 0: /*std::cout << "Ataque tierra boss final" << std::endl;*/ break;
		case 1: std::cout << "Ataque agua boss final" << std::endl; spawnBubbles(); break;
		case 2:/* std::cout << "Ataque fuego boss final" << std::endl; spawnFireWall();*/ break;
		case 3: std::cout << "Ataque oscuridad boss final" << std::endl; spawnBlackHole(); break;
		case 4: /*std::cout << "Ataque pu�o boss final" << std::endl;/* spawnFist();*/ break;
		default: /*std::cout << "Ataque generico boss final" << std::endl; /*spawnFist();*/ break;
		}
		//Cambia de elemento aleatoriamente
		int lastElem = currentElement;
		do {
			currentElement = rand() % 5;
		} while (lastElem == currentElement);

	}
}

// Mata agujeros negros y elimina del vector
void FinalBossBehaviorComponent::deleteBlackHoles() {
	for (auto it = blackHoles.begin(); it != blackHoles.end(); ++it) {
		(*it)->setAlive(false);
	}
	blackHoles.clear();
}

// Mata burbujas y elimina del vector
void FinalBossBehaviorComponent::deleteBubbles() {
	int i = 1;
	for (auto it = bubbles.begin(); it != bubbles.end(); ++it) {
		(*it)->setAlive(false);
		std::cout << "Seteado a false " << i << std::endl;

		++i;
	}
	bubbles.clear();
}

void FinalBossBehaviorComponent::spawnBubbles() //Ataque de agua 
{
	int bubblesNum = map_->bubblesNum();

	// Crea bubbles y añade componentes
	for (int i = 0; i < bubblesNum; ++i) {
		bubbles.push_back(mngr_->addEntity(ecs::_grp_BUBBLE));
		SDL_Rect rect = map_->getBubblePos(i);

		bubbles[i]->addComponent<Transform>(Vector2D(rect.x, rect.y), rect.w, rect.h);
		bubbles[i]->addComponent<Image>(&sdlutils().images().at("attackBubble"));
		bubbles[i]->addComponent<Health>(100, ecs::Water);
		bubbles[i]->addComponent<WaterBubbleComponent>(this);
	}
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

	int blackHolesNum = map_->blackHolesNum();

	// Crea blackHoles y añade componentes
	for (int i = 0; i < blackHolesNum; ++i) {
		blackHoles.push_back(mngr_->addEntity(ecs::_grp_BLACKHOLE));
		SDL_Rect rect = map_->getBlackHolePos(i);
		blackHoles[i]->addComponent<Transform>(Vector2D(rect.x, rect.y), rect.w, rect.h);
		blackHoles[i]->addComponent<FramedImage>(&sdlutils().images().at("blackHole"), 1, 4);
		blackHoles[i]->addComponent<AttractionComponent>(this);
		blackHoles[i]->addComponent<BlackHoleAnimationComp>();
	}
}

void FinalBossBehaviorComponent::spawnFist() {

	// Transform del boss
	auto pTransf = ent_->getComponent<Transform>();
	// Burguja
	Entity* fist = mngr_->addEntity(ecs::_grp_PROYECTILES);

	fist->addComponent<Transform>(Vector2D(mngr_->getPlayer()->getComponent<Transform>()->getPosition().getX(), mngr_->getPlayer()->getComponent<Transform>()->getPosition().getY()), FIST_SIZE, FIST_SIZE);
	fist->addComponent<Image>(&sdlutils().images().at("BossFist"));
	fist->addComponent<FistComponent>();

}
