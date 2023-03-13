//LIMPIO

#pragma once
#include "../ecs/Component.h"
#include "../utils/Vector2D.h"
#include "../ecs/Entity.h"
#include "../sdlutils/Texture.h"
#include "Transform.h"
#include "ColliderVine.h"

class GrowVine : public Component
{
private:
	Vector2D posFinalT;
	Transform* tr_;
	int speed;
	int dir;
public:
	GrowVine(Vector2D posT, int s, int d) : posFinalT(posT), speed(s), dir(d), tr_(nullptr) {
	}
	virtual ~GrowVine() {}
	constexpr static ecs::cmpId_type id = ecs::_GROWVINE;
	void initComponent() override;
	void update() override;
};
