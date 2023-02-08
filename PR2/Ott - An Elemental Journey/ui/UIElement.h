#pragma once
#ifndef PROYECTOS2_UIELEMENT_H
#define PROYECTOS2_UIELEMENT_H

#include "../dependencies/Vector2D.h"
#include "../dependencies/Texture.h"
#include "../gameobjects/GameObject.h"

class UIElement : public GameObject {
public:
    UIElement(const Vector2D& position, Texture* texture, const Scale& scale = Scale(1.0f, 1.0f)) : GameObject(position, texture, scale) {}
};

#endif //PROYECTOS2_UIELEMENT_H
