#pragma once
#ifndef PROYECTOS2_SDLAPPLICATION_H
#define PROYECTOS2_SDLAPPLICATION_H

#include <string>
#include <unordered_map>
#include <list>
#include <random>
#include <ctime>
#include <typeinfo>
#include <fstream>
#include "dependencies/Texture.h"
#include "dependencies/Exceptions.h"
#include "ui/UIText.h"
#include "gameflow/GameStateMachine.h"
#include "loaders/TextureLoader.h"
#include "loaders/FontLoader.h"

//Definimos las constantes de nuestro juego
const uint WINDOW_WIDTH = 1600; ///< Anchura de la ventana
const uint WINDOW_HEIGHT = 900; ///< Altura de la ventana
const uint FRAME_RATE = 5; ///< Framerate del juego
const std::string WINDOW_NAME = "Testeo de UI"; ///< Nombre de la ventana del juego


//Debido a que las texturas están en diferentes rutas si trabajamos en Windows o en Mac, lo detectamos aquí asignando
//las rutas correspondientes a cada sistema operativo.
#ifdef __APPLE__ //MacOS (CLion)
const std::string textureRoute = "../images/";
const std::string fontRoute = "../fonts/";
const std::string levelRoute = "../levels/";
const std::string levelTextureRoute = "../images/levels/";
#endif

#ifdef __WINDOWS__ //Windows (Visual Studio)
const std::string textureRoute = "../../images/";
const std::string fontRoute = "../../fonts/";
const std::string levelRoute = "../../levels/";
const std::string levelTextureRoute = "../../images/levels/";
#endif

/// Clase que se encarga del juego en su total
class SDLApplication {
private:
    SDL_GameController* gGameController = NULL;
    bool exit = false; ///< Indica si el juego se va a cerrar o no

    SDL_Window* window = nullptr; ///< Puntero a la ventana de SDL
    SDL_Renderer* renderer = nullptr; ///< Puntero al renderer de SDL

    unordered_map<std::string, TextureDescription> textureRoutes;
    unordered_map<std::string, FontDescription> fontRoutes;
    
    TextureLoader* textureManager = nullptr;
    FontLoader* fontManager = nullptr;


    GameStateMachine* stateMachine = nullptr; ///< Puntero a la máquina de estados del juego

    int generalVolume = 100;
    int musicVolume = 100;
    int soundsVolume = 100;

    /// Crea las texturas y las guarda en el array de texturas
    //void createTextures();

    /// Ejecuta nuestro juego
    void run();

    /// Llama a renderizar los diferentes objetos de cada estado
    void render() const;

    /// Llama a actualizar los diferentes objetos de cada estado
    void update();

    /// Llama al manejo de eventos de los diferentes objetos de cada estado
    void handleEvents();

    /// Cambia el estado del juego por el siguiente en caso de que el estado pida un cambio
    void changeState();

public:
    GameState* nextState = nullptr; ///< Puntero al estado que va a continuación
    bool change = false; ///< Flag que indica si se va a cambiar de estado

    /// Constructora de la clase Game
    SDLApplication();

    /// Destructora de la clase Game
    ~SDLApplication();

    /// Devuelve un SDL_Rect con la posición y tamaño de toda la ventana
    /// \return SDL_Rect con la posición y tamaño de toda la ventana
    SDL_Rect getWindowRect() const;

    /// Cierra el juego
    void quitGame();

    /// Carga una partida
    //void loadGame();

    /// Devuelve una textura dado su nombre en el diccionario de texturas
    /// \param name String con el nombre de la textura en el diccionario
    /// \return Puntero a la textura
    Texture* getTexture(const string& name, STATEID stateID);

    /// Devuelve una fuente dado su nombre en el diccionario de fuentes
    /// \param name String con el nombre de la textura en el diccionario
    /// \return Puntero a la fuente
    Font* getFont(const string& name);

    /// Devuelve el puntero a la máquina de estados
    /// \return Puntero a la máquina de estados
    GameStateMachine* getStateMachine() { return stateMachine; }

    SDL_Renderer* getRenderer() { return renderer; }

    TextureLoader* getTextureManager() { return textureManager; }

    void changeVolume(int type, int value);

    int getVolume(int type) const;

    /// Guarda la partida
    //void saveGame();
};

#endif //PROYECTOS2_SDLAPPLICATION_H
