#include "../Entity.h"
#include "../../gameflow/play/PlayState.h"
#include "../Sanctuary.h"
#include "../../ui/HealthBar.h"
#include "Shield.h"
#include "Whip.h"

enum ANIM_STATE { IDLE, WALKING, LAND, JUMPING, PEAK, FALLING, ATTACK, TP_IN, TP_OUT,CHANGE,DIE, DEFEND };

class Ott : public Entity {
protected:

    bool left = false, right = false, up = false, attack = false, defend = false, upC = false, down = false,change=false, dead = false;
    bool cooldown = false;
    bool dieAnim = false;
    bool lookingFront = true; // indica hacia d�nde debe mirar el sprite
    bool isKnockback = false;
 
    const int ELEMENT_CHANGE_TIME = 500;

    //Analog joystick dead zone
    const int JOYSTICK_DEAD_ZONE = 8000; // EL M�XIMO VALOR ES 32000, POR ESO PONEMOS UNA DEAD ZONE TAN APARENTEMENTE GRANDE

    const int MAX_VERTICAL_SPEED = 8;

    const double jumpForce = -5;  // velocidad puesta en la coordenada Y al saltar

    bool climb = false;
    const double climbForce = -1;

    bool tp = false; // indica si Ott est� en medio de un teletransporte a trav�s de l�mparas o no

    // animation parameters
    ANIM_STATE animState = IDLE; // estado actual de animaci�n
    const int ANIMATION_FRAME_RATE = 40; // cada cuantos frames se comprueba el estado de la animaci�n y se cambia/avanza
    int timer = 0; // timer para avanzar 1 en cada frame hasta llegar a ANIMATION_FRAME_RATE
    int row = 0; // fila de spritesheet
    int col = 0; // columna de spritesheet

    double knockbackTimer = 0;
    double knockbackTime = 15;

    SDL_Rect onGround;
    bool ismoving = false;
    bool notGroundedBefore = false;
    Vector2D tpPosition;
    bool isJumping = false;
    double horizontalSpeed = 1.8;

    // Constantes Knockback
    const double X_KNOCKBACK_FORCE = 6;
    // const double Y_KNOCKBACK_FORCE = 1;

    //trigger ataque y ancho de ataque (pudiera aplicarse a mas ataques)
    SDL_Rect attackTrigger;
    int ATTACK_WIDTH = 100;
    //constante y timer cooldown
    const int cooldownTime = 100;
    int cooldownTimer = 0;

    Shield* shield;
    Whip* whip;

    //Par�metros que controlan la vida debil
    bool weakened = false;
    int timeWeak = 3000, weakTimer;
    int invincibilityTime = 2000, invencibilityTimer = 0;
    bool invincible = false;
    //Game Controller 1 handler
    GameObject* lastSanctuary = nullptr;

    vector<Texture*> textures;
    
    int nextElement = 0;
    int ElementcoldDown = ELEMENT_CHANGE_TIME;

public:
    Ott(const Vector2D& position, Texture* texture, Texture* treeTexture, Texture* waterTexture, 
        Texture* fireTexture, Texture * TextureShieldLuz,
        Texture* TextureShieldFire, Texture* TextureShieldWater, Texture* TextureShieldEarth,
        Texture * textureWhip,
        PlayState* game, const Scale& scale = Scale(1.0f, 1.0f));
    /// Destructora de la clase GameObject
    virtual ~Ott(); //hihi no borrar escudo

    void canClimb(){ climb = true; };
    void cannotClimb() {
        climb = false;
    }
    bool canJump();
    void jump();
    void changeElem();
    // Renderizado 
    virtual void render(const SDL_Rect& Camera) const;

    void setAnimState(ANIM_STATE newState);

    /// Obtenci�n del rect�ngulo destino del objeto
    virtual void update();

    /// \param event SDL_Event con el evento a manejar
    virtual void handleEvents();

    //Evento de da�o
    virtual bool recieveDamage(elementsInfo::elements elem, const SDL_Rect& result);

    inline uint getLife() const {return life;}

    inline void saveSactuary(GameObject* s) { lastSanctuary = s; }

    inline GameObject* getCurrentSactuary() { return lastSanctuary; }

    virtual bool collide(const SDL_Rect& obj, SDL_Rect& result);

    virtual bool collide(GameObject* c);

    void setTpPoint(const Vector2D& newPos);

    void setSpeed();

    void setPos(const Vector2D& newPos);

    void updateAnimState();

    bool isDead() { return dead; }

    void goToSanctuary();

private:
    void attacking();
    virtual void die();
    void knockback();
};