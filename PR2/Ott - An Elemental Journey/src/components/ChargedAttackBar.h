#pragma once
#include "../ecs/Component.h"
#include "../sdlutils/Texture.h"
#include "HealthImage.h"
#include <iostream>

const int MAX_CHARGES = 8;

class ChargedAttackBar : public Component {
private:
	HealthImage* hImage_;
	Texture* texture_;
	int charges_;

public:
	constexpr static ecs::cmpId_type id = ecs::_CHARGED_ATTACK_BAR;
	ChargedAttackBar(Texture* texture, HealthImage* image) : Component(), hImage_(image), texture_(texture), charges_(0) {}
	void render() override;

	inline void addCharge(int charges) { 
		charges_ += charges; 
		if (charges_ > MAX_CHARGES) charges_ = MAX_CHARGES;
	}
	inline void resetCharges() { charges_ = 0; }
	inline int numCharges() const { return charges_; }
};

