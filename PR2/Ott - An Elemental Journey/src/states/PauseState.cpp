#include "PauseState.h"
#include <string>
#include "../sdlutils/SDLUtils.h"
#include "../components/Text.h"
#include "../sdlutils/InputHandler.h"
#include "../states/GameStateMachine.h"
#include "../utils/checkML.h"
#include "PlayState.h"

PauseState::PauseState() : GameState(ecs::_state_PAUSE) {
    //Ponemos un texto en pantalla
    auto pauseText = mngr_->addEntity(ecs::_grp_UI);
    std::string texto = "PAUSE";
    SDL_Color azulOscuro = { 17,10,208 };
    SDL_Color transparente = { 255, 255, 255, 1 };
    Font& f = sdlutils().fonts().at("ARIAL48");
    pauseText->addComponent<Text>(texto, f, azulOscuro, transparente);
    Vector2D textPos = Vector2D((sdlutils().width() - pauseText->getComponent<Text>()->getWidth()) / 2, 100);
    pauseText->getComponent<Text>()->setPosition(textPos);
    InputHandler::instance()->clearState();
}

void PauseState::handleInput() {
    //Bloqueamos la entrada de teclado hasta que se dejen de pulsar todas las teclas
    if (doNotDetectKeyboardInput && InputHandler::instance()->allKeysUp()) doNotDetectKeyboardInput = false;

    //Si presionamos el espacio, volvemos al juego
    if(!doNotDetectKeyboardInput){
        if (InputHandler::instance()->isKeyJustDown(SDLK_SPACE)) {
            dynamic_cast<PlayState*>(GameStateMachine::instance()->getPlayState())->blockKeyboardInputAfterUnfreeze();
            GameStateMachine::instance()->popState();
        }
    }
    
}
