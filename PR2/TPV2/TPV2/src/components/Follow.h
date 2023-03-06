#pragma once
#include "Transform.h"
class Follow : public Component
{
private:
	Transform* transform;
	Transform* playerTransform;
	Entity* player;
public:
	constexpr static ecs::cmpId_type id = ecs::_CTRL;
	Follow() : Component(), transform(nullptr), player(nullptr), playerTransform(nullptr) {};
	~Follow() = default;
	void initComponent() override;
	void update() override;
};

