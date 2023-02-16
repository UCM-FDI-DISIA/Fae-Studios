#include "../Entity.h"
#include "../../gameflow/play/PlayState.h"
#include "../Sanctuary.h"
#include <vector>
#include "Shield.h"
#include "Whip.h"

enum ANIM_STATE { IDLE, WALKING, LAND, JUMPING, 
    PEAK, FALLING, ATTACK, CHANGE, DEFEND };

class Ott : public Entity {
protected:
    Shield* shield;
    Whip* whip;
    bool left = false, right = false, 
         up = false, 
         attack = false, defend = false, 
         change=false,
         lookingFront = true,
         jumpFlag = true,
         jumping = false;

    //Analog joystick dead zone
    const int JOYSTICK_DEAD_ZONE = 8000; // EL MÁXIMO VALOR ES 32000, POR ESO PONEMOS UNA DEAD ZONE TAN APARENTEMENTE GRANDE

    const double jumpForce = -5;

    ANIM_STATE animState = IDLE;
    const int ANIMATION_FRAME_RATE = 40;
    const int ELEMENT_CHANGE_TIME = 500;
    int timer = 0;
    int row = 0;
    int col = 0;

    SDL_Rect onGround;
    //SDL_Rect shieldRect;
    bool ground = false;
    bool ismoving = false;
    bool notGroundedBefore = false;
    Vector2D speed = { 0,0 };

    // Constantes Knockback
    const double X_KNOCKBACK_FORCE = 5;
    const double Y_KNOCKBACK_FORCE = 1;


    //Parámetros que controlan la vida debil
    bool weakened = false;
    int timeWeak = 3, weakTimer;
    int invincibilityTime = 2, invencibilityTimer = 0;
    bool invincible = false;
    //Game Controller 1 handler
    GameObject* lastSanctuary = nullptr;

    vector<Texture*> textures;
    
    int nextElement = 0;
    int ElementcoldDown = ELEMENT_CHANGE_TIME;

public:
    Ott(const Vector2D& position, Texture* texture, Texture* treeTexture, Texture* waterTexture, 
        Texture* fireTexture, Texture * TextureShield, Texture * textureWhip,
        PlayState* game, const Scale& scale = Scale(1.0f, 1.0f));
    /// Destructora de la clase GameObject
    virtual ~Ott(); //hihi no borrar escudo

    bool canJump();
    void jump();
    void changeElem();
    // Renderizado 
    virtual void render(const SDL_Rect& Camera) const;
    /// Obtención del rectángulo destino del objeto
    virtual void update();

    inline bool isGrounded() { return ground; };

    void useGravity();

    /// \param event SDL_Event con el evento a manejar
    virtual void handleEvents(const SDL_Event& event);

    //Evento de daño
    virtual void recieveDamage(int elem);

    inline void saveSactuary(GameObject* s) { lastSanctuary = s; }

    inline GameObject* getCurrentSactuary() { return lastSanctuary; }

    virtual bool collide(const SDL_Rect& obj, SDL_Rect& result);

    virtual bool collide(GameObject* c);


private:
    void attacking();
    virtual void die();
    void knockback();
};