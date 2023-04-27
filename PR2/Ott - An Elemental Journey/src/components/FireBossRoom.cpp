#include "FireBossRoom.h"
#include "FramedImage.h"
#include "GeneralAnimationController.h"
FireBossRoom::FireBossRoom()
{
}


void FireBossRoom::initComponent()
{
	tr_ = ent_->getComponent<Transform>();
	minion = mngr_->addEntity(ecs::_grp_MINIBOSS);
	minion->addComponent<Transform>(Vector2D(tr_->getPosition().getX() + tr_->getWidth()/2, tr_->getPosition().getY() + tr_->getHeight() - 145), 150, 150);
	image = minion->addComponent<FramedImage>(&sdlutils().images().at("fireBug"), 2, 21);
	image->setRow(0);
	currentAnim = IDLE_MINION;
}

void FireBossRoom::update()
{
	int c = anims::animations[eAnims][currentAnim].colNum;
	int col = (SDL_GetTicks() / anims::animations[eAnims][currentAnim].tPerFrame) % anims::animations[eAnims][currentAnim].numFrames + anims::animations[eAnims][currentAnim].colNum;
	image->setCol(col);

	if (!entered) {
		Entity* p = mngr_->getPlayer();
		Transform* player = p->getComponent<Transform>();
		if (player->getPosition().getX() > tr_->getPosition().getX() && (player->getPosition().getX() + player->getWidth() / 2) < tr_->getPosition().getX() + tr_->getWidth() && player->getPosition().getY() + player->getHeight() > tr_->getPosition().getY() && player->getPosition().getY() < tr_->getPosition().getY() + tr_->getHeight()) {
			currentAnim = DIE_MINION;
			startTime = SDL_GetTicks();
			entered = true;
		}
	}
	if (currentAnim == DIE_MINION && ((SDL_GetTicks()-startTime) > (anims::animations[eAnims][currentAnim].tPerFrame * anims::animations[eAnims][currentAnim].numFrames) + 1)) {
		minion->setActive(false);
	}
}

FireBossRoom::~FireBossRoom()
{
}