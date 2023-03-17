//LIMPIO

#pragma once
#include "../ecs/Component.h"
#include "../utils/Vector2D.h"
#include "../ecs/Entity.h"
#include "../sdlutils/Texture.h"
#include "Transform.h"
#include "ColliderVine.h"

class GrowVine : public Component {
private:
	Vector2D posFinalT;
	Vector2D posFinalC;
	ColliderVine* cl_;
	Transform* tr_;

public:
	constexpr static ecs::cmpId_type id = ecs::_GROWVINE;
	
	GrowVine(Vector2D posT, Vector2D posC) : posFinalT(posT), posFinalC(posC), tr_(nullptr), cl_(nullptr) {}
	
	void initComponent() override;
	void update() override;
};

