#pragma once
#include "Component.h"
#include "../dependencies/Vector2D.h"
#include "../Src/Entity.h"
#include "../dependencies/Texture.h"
#include "Transform.h"
class GrowVine : public Component
{
private:
	Vector2D posFinalT;
	Transform* tr_;
	int speed;
	int dir;
public:
	GrowVine(Vector2D posT, int s, int d) : posFinalT(posT),speed(s), dir(d), tr_(nullptr) {
	}
	virtual ~GrowVine(){}
	constexpr static cmpId_type id = ecs::_GROWVINE;
	void initComponent() override;
	void update() override;
};

