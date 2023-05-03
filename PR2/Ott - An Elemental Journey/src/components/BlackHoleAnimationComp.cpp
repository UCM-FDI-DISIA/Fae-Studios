#include "BlackHoleAnimationComp.h"

void BlackHoleAnimationComp::initComponent() {
	image = ent_->getComponent<FramedImage>();
}
void BlackHoleAnimationComp::update() {

	if (SDL_GetTicks() - spawnTime >= frameTime) {
		int totalCols = image->getTexture()->getNumCols();
		int newCol = (image->getCurrentCol() + 1) % totalCols;
		image->setCol(newCol);
		spawnTime = SDL_GetTicks();
	}
}