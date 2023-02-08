#pragma once
#include "../GameState.h"

class InputObject : public GameObject {
protected:
    //Analog joystick dead zone
    const int JOYSTICK_DEAD_ZONE = 8000; // EL MÁXIMO VALOR ES 32000, POR ESO PONEMOS UNA DEAD ZONE TAN APARENTEMENTE GRANDE
    int xDir = 0;
    int yDir = 0;
    int arrowAngle = 0;
    //Game Controller 1 handler
public:
    InputObject(const Vector2D& position, Texture* texture, const Scale& scale = Scale(1.0f, 1.0f));
    /// Destructora de la clase GameObject
    virtual ~InputObject() = default;

    // Renderizado 
    virtual void render() const;
    /// Obtención del rectángulo destino del objeto
    virtual void update();

    /// \param event SDL_Event con el evento a manejar
    virtual void handleEvents(const SDL_Event& event);
};

class PlayState : public GameState 
{
public:
    PlayState(SDLApplication* app);

};

