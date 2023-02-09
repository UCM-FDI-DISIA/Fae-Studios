#pragma once
#include "../GameState.h"
#include <list>
#include "../../gameobjects/Entity.h"

enum ANIM_STATE { IDLE, JUMPING, PEAK, FALLING, LAND };


class Ground : public CollisionObject {
private:

public:
    Ground(const Vector2D& position, Texture* texture, const Scale& scale = Scale(1.0f, 1.0f));
};

class PlayState : public GameState
{
private:
    double gravity = 0.08f;
    Ground* gr;
    list<Entity*> physicObjects;
    list<Ground*> groundObjects;

public:
    PlayState(SDLApplication* app);
    void ottCollide(const SDL_Rect& Ott, const SDL_Rect& onGround, SDL_Rect& colRect, bool& col, bool& ground);
    virtual void update();
    inline double Gravity() { return gravity; };
};


class JumpObject : public Entity {
protected:
    //Analog joystick dead zone
    const int JOYSTICK_DEAD_ZONE = 8000; // EL M�XIMO VALOR ES 32000, POR ESO PONEMOS UNA DEAD ZONE TAN APARENTEMENTE GRANDE

    bool jumpFlag = true;
    bool jumping = false;
    const double jumpForce = -5;

    ANIM_STATE animState = IDLE;
    const int ANIMATION_FRAME_RATE = 40;
    int timer = 0;
    int row = 0;
    int col = 0;

    SDL_Rect onGround;
    bool ground = false;
    bool notGroundedBefore = false;
    Vector2D speed = { 0,0 };

    //Game Controller 1 handler
public:
    JumpObject(const Vector2D& position, Texture* texture, PlayState* game, const Scale& scale = Scale(1.0f, 1.0f));
    /// Destructora de la clase GameObject
    virtual ~JumpObject() = default;

    bool canJump();
    void jump();
    // Renderizado 
    virtual void render() const;
    /// Obtenci�n del rect�ngulo destino del objeto
    virtual void update();

    inline bool isGrounded() { return ground; };

    void useGravity();

    /// \param event SDL_Event con el evento a manejar
    virtual void handleEvents(const SDL_Event& event);
};