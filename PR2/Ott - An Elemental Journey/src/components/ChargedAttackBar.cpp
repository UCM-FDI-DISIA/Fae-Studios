#include "../utils/checkML.h"
#include "ChargedAttackBar.h"

void ChargedAttackBar::render() {
	SDL_Rect tmp = hImage_->getLastHeartPos();
	tmp.x += 90;
	tmp.w = texture_->getFrameWidth() * 2.25;
	tmp.h = texture_->getFrameHeight() * 2.25;
	texture_->renderFrame(tmp, 0, charges_);
}