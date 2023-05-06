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
#include "../states/GameStateMachine.h"
#include "../states/PlayState.h"



FinalBossBehaviorComponent::FinalBossBehaviorComponent(MapComponent* map) :Component()
{
	currentElement = rand() % 5;
	lastElem = currentElement;
	bossTransform = nullptr; bossHealth = nullptr;
	map_ = map;
	timeCounter = SDL_GetTicks();
	stunned = false;
	isWeakPoints = false;
	waitingForReset = false;
	lastTime = SDL_GetTicks();
}

FinalBossBehaviorComponent::~FinalBossBehaviorComponent() {
	deleteWeakPoints();
	deleteBlackHoles();
	deleteBubbles();
	deleteSpikes();
	for (auto f : fists) {
		f->getComponent<FistComponent>()->notErase();
		f->setAlive(false);
	}
}

void FinalBossBehaviorComponent::initComponent()
{
	bossHealth = ent_->getComponent<Health>();
	bossTransform = ent_->getComponent<Transform>();
	bossAnim = ent_->getComponent<FinalBossAnimation>();
	player = mngr_->getPlayer();
}

void FinalBossBehaviorComponent::update()
{
	if (SDL_GetTicks() - lastTime > TIME_DIFF) {
		timeCounter = SDL_GetTicks() - (lastTime - timeCounter);
	}
	if (!bossHealth->isDead())
	{
		
		if (player->getComponent<Health>()->isDead()) { waitingForReset = true;  }
		else
		{
			if (waitingForReset) { reset(); waitingForReset = false; }
		
			if (stunned /*&& SDL_GetTicks() < timeStunned*/)
			{
				if (!isWeakPoints)
				{	
					spawnWeakPoints();
					isWeakPoints = true;
					bossAnim->setState(STUN_BOSS);
				}
				else if (SDL_GetTicks() > timeStunned)
				{
					deleteWeakPoints();
					stunned = false;
					isWeakPoints = false;
					bossAnim->setState(IDLE_BOSS2);
				}
			}
			else
			{
				if (spikes.size() > 0  && SDL_GetTicks() - timeCounter < ATTACK_TIME && SDL_GetTicks() - timeCure > CURE_TIME)
				{
					bossHealth->cureHealth(1);
					timeCure = SDL_GetTicks();
			
				}
				//Temporizador de ataque (ataca cada 5 segundos)
				else if (SDL_GetTicks() - timeCounter > ATTACK_TIME ) {
					// Actualizamos 5 seg más
					timeCounter = SDL_GetTicks();
					//Switch de los diferentes ataques del boss

					if (numAttacks < 5) {

						switch (currentElement)
						{			
					
						case 0: spawnFistTop(); break;
						case 1: spawnBubbles(); break;
						case 2: spawnFireWall(); break;
						case 3: spawnBlackHole();break;
						case 4: spawnFist(); break;
						default: spawnFist(); break;
					
						}
						numAttacks++;

						//Cambia de elemento aleatoriamente
						lastElem = currentElement;
						do {
							srand((unsigned)time(NULL));
							currentElement = rand() % 5;
						} while (lastElem == currentElement);
					}
					else {

						numAttacks = 0;
						spawnSpikes(); 
						timeCure = SDL_GetTicks();
						bossAnim->setState(HEALTH_BOSS); 
					}

				}
			}
		}
	}
	else if (finalCountdown && SDL_GetTicks() - timeCounter > FINAL_COUNTDOWN) {
		ent_->setAlive(false);
		static_cast<PlayState*>(stateMachine().getPlayState())->endGame();
	}

	lastTime = SDL_GetTicks();
}

void FinalBossBehaviorComponent::reset()
{
	//boss
	bossHealth->resetHealth();
	bossAnim->setState(IDLE_BOSS2);
	//ataques
	deleteBlackHoles();
	deleteBubbles();
	deleteWeakPoints();
	deleteSpikes();
	//timers
	timeCounter = SDL_GetTicks() + ATTACK_TIME;

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

	fireW->addComponent<Transform>(spawnPos - Vector2D(0,FIREWALL_HEIGHT / 3), FIREWALL_WIDTH * pTransf->getScale(), FIREWALL_HEIGHT * pTransf->getScale());
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
	fists.push_back(fist);
	auto it = --(fists.end());
	fist->addComponent<FistComponent>(0, it, &fists);
}

void FinalBossBehaviorComponent::spawnFistTop() {

	// Transform del boss
	auto pTransf = ent_->getComponent<Transform>();
	// Burguja
	Entity* fist = mngr_->addEntity(ecs::_grp_BOSS_FIST);

	fist->addComponent<Transform>(Vector2D(mngr_->getPlayer()->getComponent<Transform>()->getPosition().getX(), mngr_->getPlayer()->getComponent<Transform>()->getPosition().getY()-1000), FIST_SIZE, FIST_SIZE);
	fist->addComponent<Image>(&sdlutils().images().at("BossFistTop"));
	fists.push_back(fist);
	auto it = --(fists.end());
	fist->addComponent<FistComponent>(1, it, &fists);
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

}
void FinalBossBehaviorComponent::deleteSpikes() {
	for (auto it = spikes.begin(); it != spikes.end(); ++it) {
		(*it)->setAlive(false);
	}
	spikes.clear();
	bossAnim->setState(IDLE_BOSS2);
}
// Cuando el jugador ataca la zarza, se elimina del vector
void FinalBossBehaviorComponent::deleteSpikeFromVec(Entity* s)
{
	s->setAlive(false);
	spikes.erase(std::remove(spikes.begin(), spikes.end(), s), spikes.end());

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
	}
	weakPoints.clear();
}

void FinalBossBehaviorComponent::deleteBubbleFromVec(Entity* bubble) {

	bubble->setAlive(false);
	bubbles.erase(std::remove(bubbles.begin(), bubbles.end(), bubble), bubbles.end());
}
