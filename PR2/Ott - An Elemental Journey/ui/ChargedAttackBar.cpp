#include "ChargedAttackBar.h"

void ChargedAttackBar::render(const SDL_Rect& Camera) const {
    SDL_Rect dest = getRect();
    texture->renderFrame(dest, 0, charges);
}

void ChargedAttackBar::reallocate() {

}
