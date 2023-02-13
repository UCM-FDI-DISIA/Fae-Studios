#include "../Entity.h"
#include "../../gameflow/play/PlayState.h"

enum ANIM_STATE { IDLE, WALKING, LAND, JUMPING, PEAK, FALLING };

class Ott : public Entity {
protected:
    //Analog joystick dead zone
    const int JOYSTICK_DEAD_ZONE = 8000; // EL MÁXIMO VALOR ES 32000, POR ESO PONEMOS UNA DEAD ZONE TAN APARENTEMENTE GRANDE

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
    bool ismoving = false;
    bool notGroundedBefore = false;
    Vector2D speed = { 0,0 };

    //Parámetros que controlan la vida debil
    bool weakened = false;
    int timeWeak = 3, weakTimer;
    //Game Controller 1 handler
public:
    Ott(const Vector2D& position, Texture* texture, PlayState* game, const Scale& scale = Scale(1.0f, 1.0f));
    /// Destructora de la clase GameObject
    virtual ~Ott() = default;

    bool canJump();
    void jump();
    // Renderizado 
    virtual void render() const;
    /// Obtención del rectángulo destino del objeto
    virtual void update();

    inline bool isGrounded() { return ground; };

    void useGravity();

    /// \param event SDL_Event con el evento a manejar
    virtual void handleEvents(const SDL_Event& event);

    //Evento de daño
    virtual void recieveDamage(int elem);
};