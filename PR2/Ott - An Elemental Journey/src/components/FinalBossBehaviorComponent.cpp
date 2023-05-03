#include "FinalBossBehaviorComponent.h"
#include "Health.h"
#include "Image.h"
#include "WaterBubbleComponent.h"
#include "FireWallComponent.h"
#include "FistComponent.h"
#include "AttractionComponent.h"
#include "BlackHoleAnimationComp.h"
#include "EnemyContactDamage.h"
#include "DamageArea.h"
FinalBossBehaviorComponent::FinalBossBehaviorComponent(MapComponent* map) :Component()
{
	currentElement = rand() % 6;
	lastElem = currentElement;
	bossTransform = nullptr; bossHealth = nullptr;
	map_ = map;
	timeBetweenAttacks = SDL_GetTicks() + ATTACK_TIME;
	stunned = false;
	isWeakPoints = false;
}

void FinalBossBehaviorComponent::initComponent()
{
	bossHealth = ent_->getComponent<Health>();
	bossTransform = ent_->getComponent<Transform>();
}

void FinalBossBehaviorComponent::update()
{
	if (stunned /*&& SDL_GetTicks() < timeStunned*/)
	{
		if (!isWeakPoints)
		{	
			std::cout << "stunned" << std::endl;
			spawnWeakPoints();
			isWeakPoints = true;
		}
		else if (SDL_GetTicks() > timeStunned)
		{
			std::cout << "NO stunned" << std::endl;
			deleteWeakPoints();
			stunned = false;
			isWeakPoints = false;
		}
	}
	else
	{
		if (spikes.size() > 0  && SDL_GetTicks() < timeBetweenAttacks && SDL_GetTicks() > timeCure)
		{
			std::cout << "me curo" << std::endl;
			bossHealth->cureHealth();
			timeCure += CURE_TIME;
		}
		//Temporizador de ataque (ataca cada 5 segundos)
		else if (SDL_GetTicks() > timeBetweenAttacks) {
			// Actualizamos 5 seg más
			timeBetweenAttacks +=ATTACK_TIME;
			//Switch de los diferentes ataques del boss
			switch (currentElement)
			{
			case 0: std::cout << "Ataque tierra boss final" << std::endl; spawnSpikes(); break;

			case 1: std::cout << "Ataque agua boss final" << std::endl; spawnBubbles(); break;
			case 2: std::cout << "Ataque fuego boss final" << std::endl; spawnFireWall(); break;
			case 3: std::cout << "Ataque oscuridad boss final" << std::endl; spawnBlackHole();break;
			case 4: std::cout << "Ataque puno boss final" << std::endl; spawnFist(); break;
			case 5: std::cout << "Ataque punoTop boss final" << std::endl; spawnFistTop(); break;
			default: std::cout << "Ataque generico boss final" << std::endl; spawnFist(); break;

			}
			//Cambia de elemento aleatoriamente
			lastElem = currentElement;
			do {
				currentElement = rand() % 6;
			} while (lastElem == currentElement);

		}
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
	//bubbles.clear(); // Esto me lo he inventado por la cara

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
	Vector2D spawnPos = pTransf->getPosition() + Vector2D(0, pTransf->getHeight() / 2);
	// Burguja
	Entity* fireW = mngr_->addEntity(ecs::_grp_PROYECTILES);

	fireW->addComponent<Transform>(spawnPos - Vector2D(0, FIREWALL_HEIGHT / 2), FIREWALL_WIDTH * pTransf->getScale(), FIREWALL_HEIGHT * pTransf->getScale());
	//fireW->addComponent<Image>(&sdlutils().images().at("pixelWhite"));
	fireW->addComponent<FramedImage>(&sdlutils().images().at("finalBossFireWall"), 1, 14);
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
	Entity* fist = mngr_->addEntity(ecs::_grp_BOSS_FIST);

	fist->addComponent<Transform>(Vector2D(mngr_->getPlayer()->getComponent<Transform>()->getPosition().getX()-1000, mngr_->getPlayer()->getComponent<Transform>()->getPosition().getY()), FIST_SIZE, FIST_SIZE);
	fist->addComponent<Image>(&sdlutils().images().at("BossFist"));
	fist->addComponent<FistComponent>(0);

}

void FinalBossBehaviorComponent::spawnFistTop() {

	// Transform del boss
	auto pTransf = ent_->getComponent<Transform>();
	// Burguja
	Entity* fist = mngr_->addEntity(ecs::_grp_BOSS_FIST);

	fist->addComponent<Transform>(Vector2D(mngr_->getPlayer()->getComponent<Transform>()->getPosition().getX(), mngr_->getPlayer()->getComponent<Transform>()->getPosition().getY()-1000), FIST_SIZE, FIST_SIZE);
	fist->addComponent<Image>(&sdlutils().images().at("BossFistTop"));
	fist->addComponent<FistComponent>(1);


}
// Ataque de tierra
void FinalBossBehaviorComponent::spawnSpikes() {
 	int spikesNum = map_->bossSpikesNum();

	// Crea enredaderas y añade componentes
 	for (int i = 0; i < spikesNum; ++i) {
		spikes.push_back(mngr_->addEntity(ecs::_grp_FINAL_BOSS_SPIKES));
		SDL_Rect rect = map_->getBossSpikesPos(i);
		spikes[i]->addComponent<Transform>(Vector2D(rect.x, rect.y), rect.w, rect.h);
		spikes[i]->addComponent<Image>(&sdlutils().images().at("hangingSpike"));
		spikes[i]->addComponent<DamageArea>(ecs::Earth, false, this);
	}
	timeCure = SDL_GetTicks() + CURE_TIME;

}
void FinalBossBehaviorComponent::deleteSpikes() {
	for (auto it = spikes.begin(); it != spikes.end(); ++it) {
		(*it)->setAlive(false);
		std::cout << "Spike Seteado a false " << std::endl;
	}
	spikes.clear();
}
// Cuando el jugador ataca la zarza, se elimina del vector
void FinalBossBehaviorComponent::deleteSpikeFromVec(Entity* s)
{
	s->setAlive(false);
	spikes.erase(std::remove(spikes.begin(), spikes.end(), s), spikes.end());
	std::cout << "Tam spikesVec: " << spikes.size() << std::endl;

	if (spikes.size() == 0) stunned = true; timeStunned = SDL_GetTicks() + STUNNED_TIME;
}
// Puntos débiles cuando está stuneado
void FinalBossBehaviorComponent::spawnWeakPoints() {
	int weakPointsNum = map_->bossWeakSpotsNum();

	// Crea enredaderas y añade componentes
	for (int i = 0; i < weakPointsNum; ++i) {
		weakPoints.push_back(mngr_->addEntity(ecs::_grp_FINAL_BOSS_COLLIDERS));
		SDL_Rect rect = map_->getBossWeakSpotsPos(i);
		weakPoints[i]->addComponent<Transform>(Vector2D(rect.x, rect.y), rect.w, rect.h);
	}

}
void FinalBossBehaviorComponent::deleteWeakPoints() {
	for (auto it = weakPoints.begin(); it != weakPoints.end(); ++it) {
		(*it)->setAlive(false);
		std::cout << "Spot Seteado a false " << std::endl;
	}
	weakPoints.clear();
}

void FinalBossBehaviorComponent::deleteBubbleFromVec(Entity* bubble) {

	bubble->setAlive(false);
	bubbles.erase(std::remove(bubbles.begin(), bubbles.end(), bubble), bubbles.end());
	std::cout << "Tam BubblesVec: " << bubbles.size() << std::endl;
}
