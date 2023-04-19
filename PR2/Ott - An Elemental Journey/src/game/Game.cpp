#include "Game.h"
#include "../states/GameStateMachine.h"
#include "../states/menus/MainMenuState.h"
#include "../utils/checkML.h"
#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SoundEffect.h"


Game::Game() {
    //Creamos la ventana de SDL con el nombre, la altura y la anchura, y la ruta de assets correspondiente
    SDLUtils::init(WINDOW_NAME, WINDOW_WIDTH, WINDOW_HEIGHT, jsonRoute);
    sdlutils().showCursor(); //Mostramos el cursor
    sdlutils().toggleFullScreen(SDLUtils::WINDOWED);
    SoundEffect::setNumberofChannels(32 * ecs::maxChannelId);
    SoundEffect::groupChannels();
    /*SDL_GameControllerAddMappingsFromFile("gamecontrollerdb.txt");
    SDL_Joystick* gGameController;
    SDL_JoystickEventState(SDL_ENABLE);
    if (SDL_NumJoysticks() < 1)
    {
        printf("Warning: No joysticks connected!\n");
    }
    gGameController = SDL_JoystickOpen(0);
    if (gGameController == NULL)
    {
        printf("Warning: Unable to open game controller! SDL Error: %s\n", SDL_GetError());
    }*/
}

void Game::run() {
    stateMachine().instance()->pushState(new MainMenuState());

    uint32_t startTime, frameTime; //Nos guardaremos el tiempo entre frames y el tiempo en el que se inicia cada frame
    startTime = SDL_GetTicks();

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


