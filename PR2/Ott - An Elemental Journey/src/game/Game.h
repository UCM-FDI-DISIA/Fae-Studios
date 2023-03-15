#pragma once
#ifndef TPV2_GAME_H
#define TPV2_GAME_H
#include <string>
#include <map>
#include "../sdlutils/Texture.h"
#include "../ecs/Manager.h"
#include "../utils/Collisions.h"
#include "ecs.h"
#include "../utils/Singleton.h"

using namespace std;

const uint32_t WINDOW_WIDTH = 800; ///< Anchura de la ventana
const uint32_t WINDOW_HEIGHT = 600; ///< Altura de la ventana
const string WINDOW_NAME = "Ott - An Elemental Journey"; ///< Nombre de la ventana

//Rutas de los archivos en JSON. Para evitar problemas de compatibilidad entre Visual Studio (Windows) y CLion (Mac),
//ponemos las dos rutas y mediante las directivas de preprocesado __APPLE__ y __WINDOWS__ dejamos que sea el propio
//compilador quien detecte en qué sistema operativo nos encontramos
#ifdef __APPLE__
const std::string jsonRoute = "../Ott - An Elemental Journey/resources/config/ott.resources.mac.json";
#endif

#ifdef __WINDOWS__
const std::string jsonRoute = "../resources/config/ott.resources.windows.json";
#endif

///< Clase que se encarga de la ejecución del juego (ventana, texturas, etc...)
class Game : public Singleton<Game> {
    friend Singleton<Game>;
private:
    bool exit = false; ///< Indica si el juego se va a cerrar o no

    /// Constructora de la clase Game (privada porque es un singleton)
    Game();

public:
    /// Destructora de la clase Game
    ~Game() = default;

    /// Contiene el bucle principal de ejecución del juego
    void run();

    void exitGame() { exit = true; }
};

/// Una forma más sencilla de devolver Game::instance()
/// \return
inline Game& game() {
    return *Game::instance();
}

#endif //TPV2_GAME_H
