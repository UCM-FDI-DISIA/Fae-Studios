#pragma once
#include "Component.h"
class PlayerAnimationComponent : public Component
{
public:
	PlayerAnimationComponent();
	virtual ~PlayerAnimationComponent();
	constexpr static cmpId_type id = ecs::_ANIM;
private:
	enum currentAnimation{IDLE, RUN, JUMP_UP, FALL, PEAK, ATTACK, VANISH, DIE};
};

