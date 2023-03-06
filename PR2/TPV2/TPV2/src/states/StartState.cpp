#include "../utils/checkML.h"
#include "StartState.h"
#include "../sdlutils/SDLUtils.h"
#include "../components/Text.h"
#include "../sdlutils/InputHandler.h"
#include "GameStateMachine.h"
#include "PlayState.h"

StartState::StartState() : GameState(ecs::_state_START) {
    //Ponemos un texto
    auto defeatText = mngr_->addEntity(ecs::_grp_UI);
    std::string texto = "Press space to start";
    SDL_Color azulOscuro = {17,10,208};
    SDL_Color transparente = {255, 255, 255, 1};
    Font& f = sdlutils().fonts().at("ARIAL24");
    defeatText->addComponent<Text>(texto, f, azulOscuro, transparente);
    Vector2D textPos = Vector2D((sdlutils().width() - defeatText->getComponent<Text>()->getWidth()) / 2, (sdlutils().height() - defeatText->getComponent<Text>()->getHeight()) / 2 + 100);
    defeatText->getComponent<Text>()->setPosition(textPos);
}

void StartState::handleInput() {
    //Paramos la lectura de teclado hasta que no se hayan levantado todas las teclas
    if (doNotDetectKeyboardInput && InputHandler::instance()->allKeysUp()) doNotDetectKeyboardInput = false;

    //Si pulsamos el espacio vamos a la partida
    if (!doNotDetectKeyboardInput) {
        if (InputHandler::instance()->isKeyJustDown(SDLK_SPACE)) {
            dynamic_cast<PlayState*>(GameStateMachine::instance()->getPlayState())->initAfterFreeze();
            GameStateMachine::instance()->popState();
        }
    }
}