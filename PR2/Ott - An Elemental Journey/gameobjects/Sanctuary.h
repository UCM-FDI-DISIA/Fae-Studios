#pragma once
#include "GameObject.h"
#include "../dependencies/Vector2D.h"
#include "../dependencies/Texture.h"
class Sanctuary : public GameObject
{
public:
	Sanctuary( Vector2D pos,  Texture* text, const Scale& scale = Scale(1.0f, 1.0f)) : GameObject(pos, text, scale) {};
};

