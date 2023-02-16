#include "ChargedAttackBar.h"

void ChargedAttackBar::render() const {
    SDL_Rect dest = getRect();
    dest.w /= 9;
    texture->renderFrame(dest, 0, charges);
}

void ChargedAttackBar::reallocate() {

}