#include "CollisionObject.h"

const double DEFAULT_SPEED = 5;

#pragma once
class MovingObject : public CollisionObject
{
protected:
    Vector2D dir;
    double speed = DEFAULT_SPEED;
    
public:
    MovingObject(Vector2D pos, Texture* texture, Vector2D dir, Scale scale = Scale(1.0f, 1.0f)) :
        CollisionObject(pos, texture, scale), dir(dir) {};
    virtual ~MovingObject();
    virtual void update() {};
    virtual void render() {};
};

/*
#pragma once
#ifndef PROYECTOSSDL_GAMEOBJECT_H
#define PROYECTOSSDL_GAMEOBJECT_H

#include "SDL.h"
#include "../dependencies/Vector2D.h"
#include "../dependencies/Texture.h"

struct Scale {
    float widthScale = 1.0f;
    float heightScale = 1.0f;
    Scale(float scaleW, float scaleH) : widthScale(scaleW), heightScale(scaleH) {};
};

/// Clase abstracta que declara la funcionalidad com�n a todos los objetos del juego
class GameObject {
protected:
    Vector2D position; ///< Posici�n del objeto en pantalla
    uint width = 0; ///< Anchura del objeto
    uint height = 0;  ///< Altura del objeto
    Texture* texture = nullptr; ///< Puntero a la textura del objeto;

    /// Constructora de la clase GameObject
    /// \param position Vector con la posici�n del objeto
    /// \param texture Puntero a la textura del objeto
    /// \param scale float con la escala en pantalla del objeto
    GameObject(const Vector2D& position, Texture* texture, const Scale& scale = Scale(1.0f, 1.0f));

public:
    /// Destructora de la clase GameObject
    virtual ~GameObject() = default;

    /// Renderiza nuestro objeto en pantalla
    virtual void render() const;

    /// Obtenci�n del rect�ngulo destino del objeto
    /// \return SDL_Rect con el destino del contador en pantalla
    SDL_Rect getRect() const;

    /// Actualiza posici�n o valores del objeto
    virtual void update() {};

    /// Manejo de eventos tales como la pulsaci�n de una tecla
    /// \param event SDL_Event con el evento a manejar
    virtual void handleEvents(const SDL_Event& event) {};

};

#endif //PROYECTOSSDL_GAMEOBJECT_H
*/