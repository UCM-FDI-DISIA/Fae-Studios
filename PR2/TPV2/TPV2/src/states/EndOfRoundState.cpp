#include "../utils/checkML.h"
#include "EndOfRoundState.h"
#include "../sdlutils/SDLUtils.h"
#include "../components/Text.h"
#include "GameStateMachine.h"
#include "../sdlutils/InputHandler.h"
#include "PlayState.h"

EndOfRoundState::EndOfRoundState() : GameState(ecs::_state_END_OF_ROUND){
    //Añadimos 1 texto en pantalla como una entidad con componente "Text"
    auto continueText = mngr_->addEntity(ecs::_grp_UI);
    std::string texto = "Press space to continue";
    SDL_Color negro = {0,0,39};
    SDL_Color blanco = {255, 255, 255};
    Font& f = sdlutils().fonts().at("ARIAL24");
    continueText->addComponent<Text>(texto, f, negro, blanco);
    Vector2D textPos = Vector2D((sdlutils().width() - continueText->getComponent<Text>()->getWidth()) / 2, (sdlutils().height() - continueText->getComponent<Text>()->getHeight()) / 2);
    continueText->getComponent<Text>()->setPosition(textPos);
}

void EndOfRoundState::handleInput() {
    //Si pulsamos la barra espaceadora volvemos a la partida
    if (InputHandler::instance()->isKeyJustDown(SDLK_SPACE)) {
        dynamic_cast<PlayState*>(GameStateMachine::instance()->getPlayState())->initAfterFreeze();
        GameStateMachine::instance()->popState();
    }
}