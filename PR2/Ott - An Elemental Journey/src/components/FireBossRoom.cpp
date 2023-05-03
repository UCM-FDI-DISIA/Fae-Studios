#include "FireBossRoom.h"
#include "FramedImage.h"
#include "GeneralAnimationController.h"
#include "../game/Constructors.h"
FireBossRoom::FireBossRoom()
{
}


void FireBossRoom::initComponent()
{
	camera = mngr_->getCamera();
	tr_ = ent_->getComponent<Transform>();
	minion = mngr_->addEntity(ecs::_grp_MINIBOSS);
	minion->addComponent<Transform>(Vector2D(tr_->getPosition().getX() + tr_->getWidth()/3, tr_->getPosition().getY() + tr_->getHeight() - 145), 150, 150);
	image = minion->addComponent<FramedImage>(&sdlutils().images().at("fireBug"), 2, 21);
	image->setRow(0);
	currentAnim = IDLE_MINION;
	endWall = mngr_->addEntity(ecs::_grp_GROUND);
	endWall->addComponent<Transform>(Vector2D(tr_->getPosition().getX() + tr_->getWidth() * 0.9, tr_->getPosition().getY() - tr_->getHeight()), tr_->getWidth() * 0.1, tr_->getHeight() * 2);
	endWall->addComponent<Image>(&sdlutils().images().at("vine"));
}
void FireBossRoom::resetFight()
{
	minion = mngr_->addEntity(ecs::_grp_MINIBOSS);
	minion->addComponent<Transform>(Vector2D(tr_->getPosition().getX() + tr_->getWidth() / 3, tr_->getPosition().getY() + tr_->getHeight() - 145), 150, 150);
	image = minion->addComponent<FramedImage>(&sdlutils().images().at("fireBug"), 2, 21);
	image->setRow(0);
	currentAnim = IDLE_MINION;
	entered = false;
	restartTimer = SDL_GetTicks();
}
void FireBossRoom::update()
{

	Entity* p = mngr_->getPlayer();
	Transform* player = p->getComponent<Transform>();
	if (restartTimer != -1) {
		if (SDL_GetTicks() - restartTimer <= timeRestart * 1000) return;
		else {
			restartTimer = -1;
		}
	}
	int c = anims::animations[eAnims][currentAnim].colNum;
	int col = (SDL_GetTicks() / anims::animations[eAnims][currentAnim].tPerFrame) % anims::animations[eAnims][currentAnim].numFrames + anims::animations[eAnims][currentAnim].colNum;
	image->setCol(col);
	
	if (!entered) {
		if ((player->getPosition().getX() > tr_->getPosition().getX() && (player->getPosition().getX() + player->getWidth() / 2) < tr_->getPosition().getX() + tr_->getWidth() && player->getPosition().getY() + player->getHeight() > tr_->getPosition().getY() && player->getPosition().getY() < tr_->getPosition().getY() + tr_->getHeight())) {
			showBar = true;
			currentAnim = DIE_MINION;
			col = anims::animations[eAnims][currentAnim].colNum;
			startTime = SDL_GetTicks();
			camera->getComponent<CameraComponent>()->cameraShake(true);
			auto mTr = minion->getComponent<Transform>();
			mngr_->getFireBoss()->getComponent<FireBossComponent>()->activateBoss();
			entered = true;

			Mix_PauseMusic();
			sdlutils().musics().at("fire_boss_fight").play();
		}
	}
	if (endWall) {
		float colisionEnd = endWall->getComponent<Transform>()->getPosition().getX();
		if (player->getPosition().getX() + player->getWidth() > colisionEnd) {
			player->setPosition(Vector2D(colisionEnd - player->getWidth(), player->getPosition().getY()));
		}
	}
	if (endWall != nullptr && mngr_->getFireBoss()->hasComponent<Health>() && mngr_->getFireBoss()->getComponent<Health>()->getHealth() <= 0) {
		showBar = false;
		endWall->setAlive(false); 
		endWall = nullptr;
		ent_->setAlive(false);
	}
	if (restartTimer == -1 && p->getComponent<Health>()->getHealth() <= 0) {
		showBar = false;
		mngr_->getFireBoss()->getComponent<FireBossComponent>()->resetBoss();
		resetFight();
	}
	if (currentAnim == DIE_MINION && ((SDL_GetTicks()-startTime) > (anims::animations[eAnims][currentAnim].tPerFrame * anims::animations[eAnims][currentAnim].numFrames) + 1)) {
		camera->getComponent<CameraComponent>()->cameraShake(false);
		minion->setAlive(false);
	}
}

FireBossRoom::~FireBossRoom()
{
}