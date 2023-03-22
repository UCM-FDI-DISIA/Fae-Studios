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
    sdlutils().toggleFullScreen();
}

void Game::run() {
    stateMachine().instance()->pushState(new MainMenuState());

    uint32_t startTime, frameTime; //Nos guardaremos el tiempo entre frames y el tiempo en el que se inicia cada frame
    startTime = SDL_GetTicks();
    /*

    while(!exit) {

        // Singleton que comprueba el estado de los eventos de SDL respecto al input (KEYDOWN, KEYUP, MOUSEBUTTON...)
        

        handleEvents(); //Manejamos los eventos
        if (frameTime >= FRAME_RATE) {
            InputHandler::instance()->refresh();
            update(); //Actualizamos cada FRAME_RATE ticks
            startTime = SDL_GetTicks();
        }
        render(); //Renderizamos los gameobjects
        stateMachine->currentState()->refresh();
        changeState(); //Se cambia de estado si es necesario
    }
    while (!exit) { //Una vez que hayamos perdido o ganado, se mostrará el gameover o win en pantalla hasta que cerremos el juego
        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);
        handleEvents();
    }
    */

    //BUCLE DE EJECUCIÓN DEL JUEGO
    while (!exit) {
        if (InputHandler::instance()->closeWindowEvent()) { //Detectamos si se ha cerrado la ventana en todo momento
            exit = true;
        }
        else {
            frameTime = SDL_GetTicks() - startTime;
            stateMachine().instance()->currentState()->handleInput(); //Manejamos el input del estado actuals
            if (frameTime >= 5) {
                InputHandler::instance()->refresh();
                stateMachine().instance()->currentState()->update(); //Actualizamos el estado actual
                startTime = SDL_GetTicks();
            }
            sdlutils().clearRenderer(); //Limpiamos el renderer
            stateMachine().instance()->currentState()->render();
            sdlutils().presentRenderer(); //Presentamos el renderer
            stateMachine().instance()->currentState()->refresh(); //Refrescamos TODOS los estados de la pila al mismo tiempo, de arriba a abajo
        }
    }
    if(exit) SDLUtils::close(); //Si se acaba el bucle principal con la condición de salida, cerramos la ventana
}


