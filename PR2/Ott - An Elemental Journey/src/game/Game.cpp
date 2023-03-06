#include "Game.h"
#include "../states/GameStateMachine.h"
#include "../states/menus/MainMenuState.h"
#include "../utils/checkML.h"
#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/InputHandler.h"


Game::Game() {
    //Creamos la ventana de SDL con el nombre, la altura y la anchura, y la ruta de assets correspondiente
    SDLUtils::init(WINDOW_NAME, WINDOW_WIDTH, WINDOW_HEIGHT, jsonRoute);
    sdlutils().showCursor(); //Mostramos el cursor
    SoundEffect::setChannelVolume(10, -1); //Bajamos el volumen total del juego
}

void Game::run() {
    stateMachine().instance()->pushState(new MainMenuState());

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
            stateMachine().instance()->currentState()->render();
            sdlutils().presentRenderer(); //Presentamos el renderer
            stateMachine().instance()->currentState()->refresh(); //Refrescamos TODOS los estados de la pila al mismo tiempo, de arriba a abajo
        }
    }
    if(exit) SDLUtils::close(); //Si se acaba el bucle principal con la condición de salida, cerramos la ventana
}


