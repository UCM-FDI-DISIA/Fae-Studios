#include "EndState.h"
#include "../sdlutils/Font.h"
#include "../components/Transform.h"
#include "../components/Text.h"
#include "../sdlutils/SDLUtils.h"
#include <string>
#include "../sdlutils/InputHandler.h"
#include "GameStateMachine.h"
#include "PlayState.h"
#include "StartState.h"

EndState::EndState() : GameState(ecs::_state_END){
    //Añadimos 2 textos en pantalla como una entidad con componente "Text"
    auto defeatText = mngr_->addEntity(ecs::_grp_UI);
    std::string texto = "Game Over: You lose!";
    SDL_Color azulOscuro = {17,10,208};
    SDL_Color transparente = {255, 255, 255, 1};
    Font& f = sdlutils().fonts().at("ARIAL24");
    defeatText->addComponent<Text>(texto, f, azulOscuro, transparente);
    Vector2D textPos = Vector2D((sdlutils().width() - defeatText->getComponent<Text>()->getWidth()) / 2, 100);
    defeatText->getComponent<Text>()->setPosition(textPos);

    auto continueText = mngr_->addEntity(ecs::_grp_UI);
    std::string texto2 = "Press space to continue";
    SDL_Color negro = {0,0,39};
    SDL_Color blanco = {255, 255, 255};
    continueText->addComponent<Text>(texto2, f, negro, blanco);
    Vector2D textPos2 = Vector2D((sdlutils().width() - continueText->getComponent<Text>()->getWidth()) / 2, (sdlutils().height() - continueText->getComponent<Text>()->getHeight()) / 2);
    continueText->getComponent<Text>()->setPosition(textPos2);
}

void EndState::handleInput() {
    //Si pulsamos al espacio reseteamos la partida
    if (InputHandler::instance()->isKeyJustDown(SDLK_SPACE)) {
        GameStateMachine::instance()->emptyStack();
        GameStateMachine::instance()->pushState(new PlayState);
        GameStateMachine::instance()->pushState(new StartState);
    }
}

