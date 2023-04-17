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
	Vector2D posIni;
	Vector2D posFinalT;
	Transform* tr_;
	std::string orientation;
	bool goesBack;
	bool reached = false;
	int speed;
	int dir;
	bool grow = true;
	bool ungrow = false;
public:
	GrowVine(Vector2D posT, int s, int d, std::string o, bool back) : posFinalT(posT), speed(s), dir(d), orientation(o), goesBack(back), tr_(nullptr) {
	}
	virtual ~GrowVine() {}
	constexpr static ecs::cmpId_type id = ecs::_GROWVINE;
	void initComponent() override;
	void update() override;
	void startUngrowing() { ungrow = true; reached = false; };
	void isGrowing(bool g) { grow = g; }
	bool getGrow() { return grow; }
};
