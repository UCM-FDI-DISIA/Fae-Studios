#include "checkML.h"
#include "SDLApplication.h"
#include <iostream>
//#include "PlayState.h"
#include "gameflow/menus/MainMenuState.h"
#include "dependencies/Parser.h"

SDLApplication::SDLApplication() {
    //Hacemos toda la inicialización previa de SDL
    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();
    window = SDL_CreateWindow(WINDOW_NAME.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              WINDOW_WIDTH,WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if(window == nullptr || renderer == nullptr) throw SDLError("Error loading SDL window or renderer"); //Lanzamos una excepción si no se ha cargado la ventana o el renderer
    else {
        //Creamos texturas;
        textureManager = new TextureManager(this);
        fontManager = new FontManager(this);
        TextureParser::parse(textureRoute, textureRoutes);
        FontParser::parse(fontRoute, fontRoutes);
        //createTextures();
        stateMachine = new GameStateMachine();
        stateMachine->pushState(new MainMenuState(this));
        run(); //Y ejecutamos el juego
    }
}

SDLApplication::~SDLApplication() {
    delete stateMachine;
    delete fontManager;
    delete textureManager;

    //Borramos las cosas referentes a SDL
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    //Cerramos la aplicación
    TTF_Quit();
    SDL_Quit();
}

/*void SDLApplication::createTextures() {
    for(int i = 0; i < NUM_TEXTURES; ++i) { //Recorremos todo el array de texturas y las inicializamos
        try {
            Texture* texture = new Texture(renderer, TEXT_DESCR[i].filename,
                                           TEXT_DESCR[i].numRows, TEXT_DESCR[i].numCols);
            textures.insert({ TEXT_DESCR[i].name,texture }); //Las insertamos en nuestro diccionario de texturas
        }
        catch (SDLError& e) {
            throw e;
        }
    }

    try {
        for(int j = 0; j < 1; ++j) {
            Font* f = new Font(FONTS[j].filename, 20);
            fonts.insert({FONTS[j].name, f});
        }
    }
    catch(SDLError& e) {
        throw e;
    }
}*/

void SDLApplication::run() { //CAMBIAR
    uint32_t startTime, frameTime; //Nos guardaremos el tiempo entre frames y el tiempo en el que se inicia cada frame
    startTime = SDL_GetTicks();

    while(!exit) {
        frameTime = SDL_GetTicks() - startTime;
        handleEvents(); //Manejamos los eventos
        if (frameTime >= FRAME_RATE) {
            update(); //Actualizamos cada FRAME_RATE ticks
            startTime = SDL_GetTicks();
        }
        render(); //Renderizamos los gameobjects
        changeState(); //Se cambia de estado si es necesario
    }
    while (!exit) { //Una vez que hayamos perdido o ganado, se mostrará el gameover o win en pantalla hasta que cerremos el juego
        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);
        handleEvents();
    }
}

void SDLApplication::changeState() {
    if (change) { //Si se tiene que cambiar
        while (!stateMachine->empty())
            stateMachine->popState(); //Vacía la pila de estados
        stateMachine->pushState(nextState); //Mete el nuevo estado
        change = false; //Se pone la flag a false
    }
}

void SDLApplication::render() const {
    SDL_RenderClear(renderer);
    stateMachine->currentState()->render(); //Llama al render del estado actual
    SDL_RenderPresent(renderer);
}

void SDLApplication::update() {
    stateMachine->currentState()->update(); //Llama al update del estado actual
}

void SDLApplication::handleEvents() {
    SDL_Event event;
    while(SDL_PollEvent(&event) && !exit) {
        stateMachine->currentState()->handleEvents(event); //Llama al handleEvents del estado actual
    }
}

SDL_Rect SDLApplication::getWindowRect() const {
    SDL_Rect window;
    window.x = 0; window.y = 0;
    window.w = WINDOW_WIDTH; window.h = WINDOW_HEIGHT;
    return window;
}

void SDLApplication::quitGame() {
    exit = true; //Activamos la flag de salida del bucle principal
}

/*void SDLApplication::loadGame() {
    PlayState* newPlay = new PlayState(this); //Creamos un nuevo PlayState
    newPlay->loadGame(); //Llamamos a su método de cargado
    nextState = newPlay; //El nuevo PlayState será el próximo estado
    change = true; //Ponemos la flag a true
}

void SDLApplication::saveGame() {
    GameState* pause = stateMachine->pop(); //Nos guardamos un puntero con el estado de pausa actual
    dynamic_cast<PlayState*>(stateMachine->currentState())->saveGame(); //Llamamos al método de guardado del PlayState que estaba debajo en la pila
    stateMachine->pushState(pause); //Metemos de nuevo el estado de pausa
}*/

Texture* SDLApplication::getTexture(const string& name, int stateID) {
    Texture* TMP = textureManager->getTexture(name, stateID);
    if (TMP == nullptr) {
        try {
            textureManager->createTexture(textureRoutes.at(name), stateID);
            return textureManager->getTexture(name, stateID);
        }
        catch (exception& e) {
            throw e;
        }
    }
    else return TMP;
}

Font* SDLApplication::getFont(const string& name) {
    Font* TMP = fontManager->getFont(name);
    if (TMP == nullptr) {
        try {
            fontManager->createFont(fontRoutes.at(name));
            return fontManager->getFont(name);
        }
        catch (exception& e) {
            throw e;
        }
    }
    else return TMP;
}

void SDLApplication::changeVolume(int type, int value) {
    switch (type) {
    case 0: generalVolume = value; break;
    case 1: musicVolume = value; break;
    case 2: soundsVolume = value; break;
    }
}

int SDLApplication::getVolume(int type) const {
    switch (type) {
    case 0: return generalVolume;
    case 1: return musicVolume;
    case 2: return soundsVolume;
    }
}