#pragma once
#include "../utils/Vector2D.h"
#include "../ecs/Component.h"
#include "../ecs/anims.h"
#include <SDL.h>
#include "EnemyMovement.h"
#include"../ecs/Entity.h"
#include "FramedImage.h"

class EarthBossManager;
class FramedImage;

class EarthBossAnimationController : public Component {
public:
    constexpr static ecs::cmpId_type id = ecs::_ENEMYANIM;

    EarthBossAnimationController(EarthBossManager* e) : emngr_(e) {};
    virtual ~EarthBossAnimationController() {};
    void initComponent();
    virtual void update();
    void setState(anims::Entities newState, Entity* e);
    void endAnim();
    inline int getTPerFrame(anims::Entities eAnims) { return anims::animations[eAnims][0].tPerFrame / FRAME_ANIMATION_TIME; }
    inline int getNFrames(anims::Entities eAnims) { return anims::animations[eAnims][0].numFrames; }
    inline int getRowNum(anims::Entities eAnims) { return anims::animations[eAnims][0].rowNum; }
    inline int getColNum(anims::Entities eAnims) { return anims::animations[eAnims][0].colNum; }
    inline bool isDamaged() { return damaged; }
    inline void damage() { damaged = true; }

private:
    bool damaged = false;
    anims::Entities state;
    FramedImage* image;
    EarthBossManager* emngr_;
    float timer;

    int damageTimer_, damageStartTime_, timer_ = 0;
    const int maxDamagedTimer_ = 500, FRAME_ANIMATION_TIME = 6;
};

