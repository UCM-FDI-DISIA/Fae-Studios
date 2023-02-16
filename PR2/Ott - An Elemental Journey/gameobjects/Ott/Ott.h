#include "../Entity.h"
#include "../../gameflow/play/PlayState.h"
#include "../Sanctuary.h"

enum ANIM_STATE { IDLE, WALKING, LAND, JUMPING, PEAK, FALLING, ATTACK, TP_IN, TP_OUT };

class Ott : public Entity {
protected:

    bool left = false, right = false, up = false, attack = false, upC = false, down = false;

    bool lookingFront = true; // indica hacia dónde debe mirar el sprite

    //Analog joystick dead zone
    const int JOYSTICK_DEAD_ZONE = 8000; // EL MÁXIMO VALOR ES 32000, POR ESO PONEMOS UNA DEAD ZONE TAN APARENTEMENTE GRANDE
    const int MAX_VERTICAL_SPEED = 8;

    const double jumpForce = -5;  // velocidad puesta en la coordenada Y al saltar

    bool climb = false; // indica si Ott está escalando una enredadera

    bool tp = false; // indica si Ott está en medio de un teletransporte a través de lámparas o no

    // animation parameters
    ANIM_STATE animState = IDLE; // estado actual de animación
    const int ANIMATION_FRAME_RATE = 40; // cada cuantos frames se comprueba el estado de la animación y se cambia/avanza
    int timer = 0; // timer para avanzar 1 en cada frame hasta llegar a ANIMATION_FRAME_RATE
    int row = 0; // fila de spritesheet
    int col = 0; // columna de spritesheet

    SDL_Rect onGround;
    bool ismoving = false;
    bool notGroundedBefore = false;
    Vector2D tpPosition;

    bool isJumping = false;

    int horizontalSpeed = 1;
    int climbForce = 1;

    //Parámetros que controlan la vida debil
    bool weakened = false;
    int timeWeak = 3, weakTimer;
    //Game Controller 1 handler
    GameObject* lastSanctuary = nullptr;
public:
    Ott(const Vector2D& position, Texture* texture, PlayState* game, const Scale& scale = Scale(1.0f, 1.0f));
    /// Destructora de la clase GameObject
    virtual ~Ott() = default;

    void canClimb(){ climb = true; };
    bool canJump();
    void jump();
    // Renderizado 
    virtual void render(const SDL_Rect& Camera) const;

    void setAnimState(ANIM_STATE newState);

    /// Obtención del rectángulo destino del objeto
    virtual void update();

    /// \param event SDL_Event con el evento a manejar
    virtual void handleEvents();

    //Evento de daño
    virtual void recieveDamage(int elem);

    inline void saveSactuary(GameObject* s) { lastSanctuary = s; }

    inline GameObject* getCurrentSactuary() { return lastSanctuary; }

    virtual bool collide(const SDL_Rect& obj, SDL_Rect& result);

    virtual bool collide(GameObject* c);

    void setTpPoint(const Vector2D& newPos);

    void setSpeed();

    void updateAnimState();
private:
    virtual void die();
};