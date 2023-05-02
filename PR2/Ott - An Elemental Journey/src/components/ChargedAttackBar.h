#pragma once
#include "../ecs/Component.h"
#include "../sdlutils/Texture.h"
#include "HealthImage.h"
#include <iostream>

const int MAX_CHARGES = 8;
const int FRAME_TIME = 200;

class ChargedAttackBar : public Component {
private:
	HealthImage* hImage_;
	Texture* texture_;
	int charges_;
	int frame_;
	int count_;
	bool glowing_;
	int ticks_;
	bool anim_;
	int ticksCount_;

public:
	constexpr static ecs::cmpId_type id = ecs::_CHARGED_ATTACK_BAR;
	ChargedAttackBar(Texture* texture, HealthImage* image) : Component(), hImage_(image), texture_(texture), charges_(0), frame_(0), glowing_(false), count_(1), ticks_(SDL_GetTicks()), anim_(false), ticksCount_(6) {}
	void render() override;
	void update() override;

	inline void addCharge(int charges) { 
		charges_ += charges; 
		if (charges_ > MAX_CHARGES) charges_ = MAX_CHARGES;
	}
	inline void animChargeBar() { anim_ = true; }
	inline bool animDone() const { return !anim_; }
	inline void resetCharges() { charges_ = 0; ticksCount_ = 6; anim_ = false; }
	inline int numCharges() const { return charges_; }
};

