#pragma once
#include "../utils/Vector2D.h"
#include "../ecs/Component.h"
#include "../ecs/anims.h"
#include <SDL.h>
#include "EnemyMovement.h"
#include"../ecs/Entity.h"

enum EarthAnims { PRESENTATION, STOP };

class Health;
class FramedImage;

class EarthBossAnimationController : public Component {
public:
    constexpr static ecs::cmpId_type id = ecs::_ENEMYANIM;

    EarthBossAnimationController(anims::Entities e) : eAnims(e) {};
    virtual ~EarthBossAnimationController() {};
    void initComponent();
    virtual void update();
    inline int getState() { return currentAnimation; }
    void setState(int newState);
    void endAnim();
    inline int getTPerFrame(int i) { return anims::animations[eAnims][i].tPerFrame / FRAME_ANIMATION_TIME;; }
    inline int getNFrames(int i) { return anims::animations[eAnims][i].numFrames; }
    inline int getRowNum(int i) { return anims::animations[eAnims][i].rowNum; }
    inline int getColNum(int i) { return anims::animations[eAnims][i].colNum; }
    inline bool isDamaged() { return damaged; }
    inline void damage() { damaged = true; }

private:
    bool damaged = false;
    int currentAnimation = PRESENTATION;
    anims::Entities eAnims;
    FramedImage* image;
    Health* health_;
    EnemyMovement* eMovement_;
    EnemyAttack* eAttack_;

    int damageTimer_, damageStartTime_, timer_ = 0;
    const int maxDamagedTimer_ = 500, FRAME_ANIMATION_TIME = 6;
};
