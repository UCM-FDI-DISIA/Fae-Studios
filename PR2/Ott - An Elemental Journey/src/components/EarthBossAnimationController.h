#pragma once
#include "../utils/Vector2D.h"
#include "../ecs/Component.h"
#include "../ecs/anims.h"
#include <SDL.h>
#include "EnemyMovement.h"
#include"../ecs/Entity.h"
#include "FramedImage.h"
#include <vector>

class EarthBossManager;
class FramedImage;

class EarthBossAnimationController : public Component {
public:
    constexpr static ecs::cmpId_type id = ecs::_ENEMYANIM;

    EarthBossAnimationController(EarthBossManager* e) : emngr_(e) {};
    virtual ~EarthBossAnimationController() {};
    void initComponent();
    virtual void update();
    void setState(anims::Entities newState, Entity* e1, Entity* e2);
    void endAnim();
    inline int getTPerFrame(anims::Entities eAnims) { return anims::animations[eAnims][0].tPerFrame / FRAME_ANIMATION_TIME; }
    inline int getNFrames(anims::Entities eAnims) { return anims::animations[eAnims][0].numFrames; }
    inline int getRowNum(anims::Entities eAnims) { return anims::animations[eAnims][0].rowNum; }
    inline int getColNum(anims::Entities eAnims) { return anims::animations[eAnims][0].colNum; }
    inline void setAnimation(bool a) { thereIsAnimation = a; }
    inline int getPresentationReps() { return animPresentacion; }
    inline void presentationRepsReset() { animPresentacion = 0; }

private:
    bool thereIsAnimation = false;
    anims::Entities state;
    FramedImage* image1;
    FramedImage* image2;
    EarthBossManager* emngr_;
    float timer;

    int animPresentacion = 0;
    int warningRepetition = 0;
    int damageTimer_, damageStartTime_, timer_ = 0;
    const int maxDamagedTimer_ = 500, FRAME_ANIMATION_TIME = 6;
};

