#include "../../checkML.h"
#include "MenuState.h"
#include "../../SDLApplication.h"

void MenuState::render() const {
    menuBg->render(app->getWindowRect());
    GameState::render({ 0,0,0,0 });
}