#pragma once
#include "../GameState.h"

enum ANIM_STATE { IDLE, JUMPING, PEAK, FALLING, FELL };


class Ground : public GameObject {
private:

public:
    Ground(const Vector2D& position, Texture* texture, const Scale& scale = Scale(1.0f, 1.0f));
    pair<bool, int> collide(const SDL_Rect& onGround);
};

class PlayState : public GameState
{
private:
    double gravity = 9.8f;
    Ground* gr;

public:
    PlayState(SDLApplication* app);
    void ottCollide(const SDL_Rect& Ott, const SDL_Rect& onGround, pair<bool, int>& groundCol, bool& col);
};


class JumpObject : public GameObject {
protected:
    //Analog joystick dead zone
    const int JOYSTICK_DEAD_ZONE = 8000; // EL MÁXIMO VALOR ES 32000, POR ESO PONEMOS UNA DEAD ZONE TAN APARENTEMENTE GRANDE
    int xDir = 0;
    int yDir = 0;
    int ySpeed = 0;
    int arrowAngle = 0;

    bool jumpFlag = true;
    bool jumping = false;
    
    ANIM_STATE animState = IDLE;
    const int ANIMATION_FRAME_RATE = 60;
    int timer = 0;
    int row = 0;
    int col = 0;

    SDL_Rect onGround;
    PlayState* game;
    
    //Game Controller 1 handler
public:
    JumpObject(const Vector2D& position, Texture* texture, PlayState* game, const Scale& scale = Scale(1.0f, 1.0f));
    /// Destructora de la clase GameObject
    virtual ~JumpObject() = default;

    bool canJump() {

        // aquí hay que comprobar si está pegado al suelo. Para esto hay que tener un objeto suelo en el PlayState y ver si sus rectángulos interseccionan
        // también hay que ver si se está saltando en este momento
        if (jumping) jumpFlag = false;
        return jumpFlag;
    }

    void jump() {
        if (canJump()) {
            jumping = true;
            animState = JUMPING;
        }
    }

    // Renderizado 
    virtual void render() const;
    /// Obtención del rectángulo destino del objeto
    virtual void update();

    /// \param event SDL_Event con el evento a manejar
    virtual void handleEvents(const SDL_Event& event);
};



