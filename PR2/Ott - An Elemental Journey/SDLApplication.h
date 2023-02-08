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
#include "ui/Text.h"
#include "gameflow/GameStateMachine.h"
#include "loaders/TextureLoader.h"
#include "loaders/FontLoader.h"

//Definimos las constantes de nuestro juego
const uint WINDOW_WIDTH = 800; ///< Anchura de la ventana
const uint WINDOW_HEIGHT = 600; ///< Altura de la ventana
const uint FRAME_RATE = 5; ///< Framerate del juego
const uint NUM_TEXTURES = 5; ///< Número de texturas totales que el juego tiene que leer
const uint NUM_LEVELS = 3; ///< Número de niveles totales que el juego tiene que leer
const uint WALL_THICKNESS = 15; ///< Anchura de las paredes
const float CLOCK_SIZE = 0.15f; ///< Tamaño del reloj en la esquina inferior izquierda
const float HEARTS_SIZE = 5.0f; ///< Tamaño de los corazones de la barra de vida
const float REWARDS_SIZE = 0.1f; ///< Tamaño de las recompensas
const uint REWARD_PROBABILITY = 99; ///< Probabilidad de que aparezca una recompensa
const uint NUM_REWARDS = 6; ///< Número de rewards totales incorporados al juego
const std::string WINDOW_NAME = "Testeo de UI"; ///< Nombre de la ventana del juego


//Debido a que las texturas están en diferentes rutas si trabajamos en Windows o en Mac, lo detectamos aquí asignando
//las rutas correspondientes a cada sistema operativo.
#ifdef __APPLE__ //MacOS (CLion)
const std::string textureRoute = "../images/";
const std::string fontRoute = "../fonts/";
#endif

#ifdef __WINDOWS__ //Windows (Visual Studio)
const std::string textureRoute = "../../images/";
const std::string fontRoute = "../../fonts/";
#endif

/// Array con las rutas de las texturas, sus filas y columnas, y su descriptivo
/*const TextureDescription TEXT_DESCR[NUM_TEXTURES] = {
        {textureRoute + "side2.png", 1, 1, "sideWall"},
        {textureRoute + "topside.png", 1, 1, "topWall"},
        {textureRoute + "paddle2.png", 1, 1, "paddle"},
        {textureRoute + "bricks2.png", 2, 3, "bricks"},
        {textureRoute + "ball2.png", 1, 1, "ball"},
        {textureRoute + "gameover1.png", 1, 1, "gameover"},
        {textureRoute + "youwin.png", 1, 1, "win"},
        {textureRoute + "digits2.jpeg", 3, 4, "digits"},
        {textureRoute + "hearts.png", 1, 13, "hearts"},
        {textureRoute + "rewards.png", 10, 8, "rewards"},
        {textureRoute + "menubackground.png", 1, 1, "background"},
        {textureRoute + "startbutton.png", 1, 3, "start"},
        {textureRoute + "loadbutton.png", 1, 3, "load"},
        {textureRoute + "pausemenubackground.png", 1, 1, "pausebackground"},
        {textureRoute + "quitbutton.png", 1, 3, "quit"},
        {textureRoute + "resumebutton.png", 1, 3, "resume"},
        {textureRoute + "savebutton.png", 1, 3, "save"},
        {textureRoute + "continuebutton.png", 1, 3, "continue"},
        {textureRoute + "mainmenu.png", 1,3, "mainmenu"}
};*/

/*const TextureDescription TEXT_DESCR[NUM_TEXTURES] = {
    {textureRoute + "mainbg.png", 1, 1, "mainmenubackground"},
    {textureRoute + "button.png", 1, 3, "button"},
    {textureRoute + "quitbutton.png", 1, 3, "quitbutton"},
    {textureRoute + "slider.png", 3, 1, "slider"},
    {textureRoute + "needle.png", 1, 3, "needle"}
};

/// Array con las rutas de las fuentes y su descriptivo
const FontDescription FONTS[1] {
        {fontRoute + "armin.ttf", "armin"}
};*/

/// Clase que se encarga del juego en su total
class SDLApplication {
private:
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
    Texture* getTexture(const string& name, int stateID);

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
