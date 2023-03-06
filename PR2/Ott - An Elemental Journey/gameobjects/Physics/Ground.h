#include "../CollisionObject.h"
#pragma once

class Ground : public CollisionObject {
private:

public:
    Ground(const Vector2D& position, Texture* texture, const Scale& scale = Scale(1.0f, 1.0f)) : CollisionObject(position, texture, scale) {};
};

class Wall : public CollisionObject {
private:

public:
    Wall(const Vector2D& position, Texture* texture, const Scale& scale = Scale(1.0f, 1.0f)) : CollisionObject(position, texture, scale) {};

};