//LIMPIO

#pragma once
#include <string>
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
	std::string orientation;
	int speed;
	int dir;
public:
	GrowVine(Vector2D posT, int s, int d, std::string o) : posFinalT(posT), speed(s), dir(d), orientation(o), tr_(nullptr) {
	}
	virtual ~GrowVine() {}
	constexpr static ecs::cmpId_type id = ecs::_GROWVINE;
	void initComponent() override;
	void update() override;
};
