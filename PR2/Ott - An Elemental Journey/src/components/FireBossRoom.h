#pragma once
#include "../ecs/Component.h"
#include "Transform.h"

class FireBossRoom : public Component
{
private:
	enum  ANIMATIONS
	{
		IDLE_MINION, DIE_MINION, HIT_MINION, DELAY_MINION, MOVE_MINION
	};
	Transform* tr_;
	class FramedImage* image;

	Entity* camera = nullptr;
	bool showBar = false;
	void resetFight();
public:
	FireBossRoom();
	virtual ~FireBossRoom();
	virtual void initComponent();
	virtual void update();
	inline bool getShowBar() { return showBar; }
	anims::Entities eAnims = anims::MELEE_ANIM;
	Entity* endWall;
	Entity* minion;
	int currentAnim, startTime;
	int restartTimer = -1, timeRestart = 3;
	bool entered = false;
	constexpr static ecs::cmpId_type id = ecs::_TRIGGER;
};

