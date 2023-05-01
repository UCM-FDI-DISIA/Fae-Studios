#pragma once
#include "../ecs/Component.h"
#include "../utils/Vector2D.h"
#include <iostream>
#include <SDL.h>
#include "../ecs/anims.h"
#include "../ecs/colliders.h"
class PhysicsComponent : public Component
{
public:
    PhysicsComponent(bool activate = true);
    PhysicsComponent(colliders::Colliders c);
    PhysicsComponent(Vector2D vel) : velocity_(vel) {}
    virtual ~PhysicsComponent();
    virtual void initComponent();
    virtual void update();
    void knockback(bool dir);
    constexpr static ecs::cmpId_type id = ecs::_PHYSICS;
    Vector2D& getVelocity();
    SDL_Rect getCollider() const;
    inline void slowed() { velocity_ = Vector2D(velocity_.getX() / 2, velocity_.getY()); }
    inline void lookDirection(bool b) { lookingRight = b; }
    inline bool getLookDirection() { return lookingRight; }
    inline void setGrounded(bool value) { grounded = value; if (grounded && !inWater) verticalSpeed = 0; }
    inline bool isGrounded() { return grounded; }
    inline void setClimbing(bool value, int dir) { climbing = value; dirClimbing = dir; if(value) verticalSpeed = 0; }
    inline bool isClimbing() { return climbing; }
    inline void setVelocity(Vector2D value) { velocity_ = value; }
    inline void setGravity(bool g) { gravity = g; }
    inline void setVerticalSpeed(float value) { verticalSpeed = value; }
    inline float getHorizontalSpeed() { return horizontalSpeed; };
    void jump();
    void createCollider();
    inline void setWater(bool value) { inWater = value; }
    inline bool getWater() { return inWater; }
    inline void setFloating(bool value) { floating = value; }
    inline bool getFloating() { return floating; }
    inline void Stop() { stopped = true; lastSpeed = velocity_; }
    inline void Resume(bool verticalTrigger = false) { stopped = false; if(verticalTrigger) velocity_ = lastSpeed; }
    inline bool isStopped() { return stopped; }
    inline bool inKnocback()  { return isKnockback; }
    inline bool getGravity() { return gravity; }
    inline void setJumpWater(bool c) { inWaterJumpArea = c; }
    /*inline void saveLastPos(const SDL_Rect& col)
    {
        int wPlayerRect = getCollider().w;
        auto tr = ent_->getComponent<Transform>();
        if (wPlayerRect * offset < col.w)
        {
            lastPos = tr->getPosition();
        }
    }*/
    /*inline void setLastPos()
    {
        auto tr = ent_->getComponent<Transform>();
        tr->setPosition(lastPos);
    }*/
    void saveLastPos(const SDL_Rect& col);
    void setLastPos();
    //virtual void render();
private:
    SDL_Rect collider;
    Vector2D colliderOffset, colliderWH, lastSpeed;
    const int MAX_VERTICAL_SPEED = 8;
    const double X_KNOCKBACK_FORCE = 5;
    double knockbackTimer = 0;
    double knockbackTime = 15;
    bool isKnockback = false, lookingRight = true, grounded = false, climbing = false, gravity = true;
    bool stopped = false;
    float verticalSpeed = 0;
    const float horizontalSpeed = 1.8f;
    const float jumpingHorizontalSpeed = 1.8f * 1.25f;
    Vector2D velocity_;
    float dirClimbing = 0;
    Vector2D lastPos;
    colliders::Colliders typeofCollider;
    //jumpforces
    int jumpForce;
    const int earthJumpForce = -10;
    const int waterJumpForce = -7;
    const float offset = 0.9;
    //booleanos de agua
    bool inWater = false, floating = false, inWaterJumpArea = false, isJumpingF = false;

};
