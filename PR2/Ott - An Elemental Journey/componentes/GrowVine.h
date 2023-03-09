#pragma once
#include "Component.h"
#include "../dependencies/Vector2D.h"
#include "../Src/Entity.h"
#include "../dependencies/Texture.h"
#include "Transform.h"
class ColliderVine;
class GrowVine : public Component
{
private:
	Vector2D posFinalT;
	Vector2D posFinalC;
	ColliderVine* cl_;
	Transform* tr_;
public:
	GrowVine(Vector2D posT, Vector2D posC) : posFinalT(posT), posFinalC(posC), tr_(nullptr), cl_(nullptr) {
	
	}
	virtual ~GrowVine(){}
	constexpr static cmpId_type id = ecs::_GROWVINE;
	void initComponent() override;
	void update() override;
};

