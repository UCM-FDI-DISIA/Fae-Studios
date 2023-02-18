#pragma once
#ifndef PROYECTOSSDL_GAMEOBJECT_H
#define PROYECTOSSDL_GAMEOBJECT_H

#include "SDL.h"
#include "../dependencies/Vector2D.h"
#include "../dependencies/Texture.h"
#include <list>
class GameState;

enum GO_TYPE { LAMP, SANCTUARY, OTT, DEFAULT };

struct Scale {
    float widthScale = 1.0f;
    float heightScale = 1.0f;
    Scale(float scaleW, float scaleH) : widthScale(scaleW), heightScale(scaleH) {};
};

/// Clase abstracta que declara la funcionalidad común a todos los objetos del juego
class GameObject {
protected:
    Vector2D position; ///< Posición del objeto en pantalla
    uint width = 0; ///< Anchura del objeto
    uint height = 0;  ///< Altura del objeto
    Texture* texture = nullptr; ///< Puntero a la textura del objeto;
    GO_TYPE type = DEFAULT;


    GameObject() = default;

    /// Constructora de la clase GameObject
    /// \param position Vector con la posición del objeto
    /// \param texture Puntero a la textura del objeto
    /// \param scale float con la escala en pantalla del objeto
    GameObject(const Vector2D& position, Texture* texture, const Scale& scale = Scale(1.0f, 1.0f), GO_TYPE type = DEFAULT);

public:
    /// Destructora de la clase GameObject
    virtual ~GameObject() = default;

    list<GameObject*>::iterator it;

    /// Renderiza nuestro objeto en pantalla
    virtual void render(const SDL_Rect& Camera = {0,0,0,0}) const;

    /// Obtención del rectángulo destino del objeto
    /// \return SDL_Rect con el destino del contador en pantalla
    SDL_Rect getRect() const;

    /// Actualiza posición o valores del objeto
    virtual void update() {};

    /// Manejo de eventos tales como la pulsación de una tecla
    /// \param event SDL_Event con el evento a manejar
    virtual void handleEvents() {};

    GO_TYPE getType();
};

#endif //PROYECTOSSDL_GAMEOBJECT_H
