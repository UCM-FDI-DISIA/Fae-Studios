#pragma once
#include "../ecs/Component.h"
#include "../utils/Vector2D.h"
#include "../ecs/Entity.h"
#include "../sdlutils/Texture.h"
#include "ColliderVine.h"
#include "GrowVine.h"
#include "ImageVine.h"
#include "../sdlutils/SDLUtils.h"
enum VineType{NORMAL, EVIL};
class VineManager : public Component
{
private:
    VineType texture_;
    Vector2D iniPos;
    Vector2D finPos;
    int width;
    int height;
    int dir;
    int speed;
    float rotation;
    Entity* vine;
    bool hasVine = false;

public:
    constexpr static ecs::cmpId_type id = ecs::_VINEMANAGER;
    VineManager(VineType t, Vector2D ini, Vector2D fin, int d, float r, int w, int h, int s) : texture_(t), iniPos(ini), finPos(fin), dir(d), rotation(r), width(w), height(h), speed(s), vine(nullptr) {};
    virtual ~VineManager() {}
    void createVine();
    void addVine();
    inline Vector2D getIniPos() {
        return iniPos;
    }
    inline Vector2D getFinPos() {
        return finPos;
    }
    inline int getWidth() {
        return width;
    }
    inline int getHeigth() {
        return height;
    }
    inline int getDir() {
        return dir;
    }
    inline float getRotation() {
        return rotation;
    }
    inline Entity* getVine() {
        return vine;
    }
};
