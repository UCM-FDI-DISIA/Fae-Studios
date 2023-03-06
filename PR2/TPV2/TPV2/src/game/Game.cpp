#include "Game.h"
#include "../ecs/Entity.h"
#include "../components/Transform.h"
#include"../components/Image.h"
#include"../components/FighterCtrl.h"
#include"../components/DeAcceleration.h"
#include"../components/Health.h"
#include"../components/Gun.h"
#include "../components/ShowAtOpposideSide.h"
#include "../components/DisableOnExit.h"
#include "../components/FramedImage.h"
#include "../components/Generations.h"
#include "../components/Follow.h"
#include "../states/GameStateMachine.h"
#include "../states/PlayState.h"
#include "../states/StartState.h"
#include "../utils/checkML.h"


Game::Game() {
    //Creamos la ventana de SDL con el nombre, la altura y la anchura, y la ruta de assets correspondiente
    SDLUtils::init(WINDOW_NAME, WINDOW_WIDTH, WINDOW_HEIGHT, jsonRoute);
    sdlutils().showCursor(); //Mostramos el cursor
    SoundEffect::setChannelVolume(10, -1); //Bajamos el volumen total del juego
}

void Game::run() {
    //Pusheamos un playstate que se situará al fondo de la pila siempre...
    stateMachine().instance()->pushState(new PlayState());
    //... y por encima de este, un startstate
    stateMachine().instance()->pushState(new StartState());

    //BUCLE DE EJECUCIÓN DEL JUEGO
    while (!exit) {
        if (InputHandler::instance()->closeWindowEvent()) { //Detectamos si se ha cerrado la ventana en todo momento
            exit = true;
        }
        else {
            InputHandler::instance()->refresh(); //Llamamos al refresh del input
            stateMachine().instance()->currentState()->handleInput(); //Manejamos el input del estado actuals
            stateMachine().instance()->currentState()->update(); //Actualizamos el estado actual
            sdlutils().clearRenderer(); //Limpiamos el renderer
            stateMachine().instance()->renderAllStates(); //Renderizamos TODOS los estados de la pila al mismo tiempo, de arriba a abajo
            sdlutils().presentRenderer(); //Presentamos el renderer
            stateMachine().instance()->refreshAllStates(); //Refrescamos TODOS los estados de la pila al mismo tiempo, de arriba a abajo
        }
    }
    if(exit) SDLUtils::close(); //Si se acaba el bucle principal con la condición de salida, cerramos la ventana
}


