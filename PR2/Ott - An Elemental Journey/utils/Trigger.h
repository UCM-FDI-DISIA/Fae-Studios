#pragma once
#include "../gameobjects/GameObject.h"
class Trigger : public GameObject
{
	using Enter = void(GameObject* g);
private:
	GameObject* gameObject = nullptr;
	Enter* enter = nullptr;
public:
	Trigger(float x, float y, float w, float h, GameObject* g, Enter* en) : GameObject(Vector2D(x, y), nullptr, {w, h}) {};
	~Trigger() = default;
	void OnEnter();
};

