#include "WinState.h"
#include "../utils/checkML.h"
#include <string>
#include "../sdlutils/SDLUtils.h"
#include "../components/Text.h"
#include "GameStateMachine.h"
#include "PlayState.h"
#include "StartState.h"
#include "../sdlutils/InputHandler.h"

WinState::WinState() : GameState(ecs::_state_END) {
    // Ponemos 2 textos en pantalla
    auto winText = mngr_->addEntity(ecs::_grp_UI);
    std::string texto = "VICTORY! YOU'VE WON";
    SDL_Color dorado = { 255,215,0 };
    SDL_Color transparente = { 255, 255, 255, 1 };
    Font& f = sdlutils().fonts().at("ARIAL24");
    winText->addComponent<Text>(texto, f, dorado, transparente);
    Vector2D textPos = Vector2D((sdlutils().width() - winText->getComponent<Text>()->getWidth()) / 2, 100);
    winText->getComponent<Text>()->setPosition(textPos);

    auto continueText = mngr_->addEntity(ecs::_grp_UI);
    std::string texto2 = "Press space to continue";
    SDL_Color negro = { 0,0,39 };
    SDL_Color blanco = { 255, 255, 255 };
    continueText->addComponent<Text>(texto2, f, negro, blanco);
    Vector2D textPos2 = Vector2D((sdlutils().width() - continueText->getComponent<Text>()->getWidth()) / 2, (sdlutils().height() - continueText->getComponent<Text>()->getHeight()) / 2);
    continueText->getComponent<Text>()->setPosition(textPos2);
}

void WinState::handleInput() {
    //Si pulsamos al espacio volvemos al inicio del juego
    if (InputHandler::instance()->isKeyJustDown(SDLK_SPACE)) {
        GameStateMachine::instance()->emptyStack();
        GameStateMachine::instance()->pushState(new PlayState);
        GameStateMachine::instance()->pushState(new StartState);
    }
}