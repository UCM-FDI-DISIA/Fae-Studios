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
	ChargedAttackBar(Texture* texture) : Component(), hImage_(nullptr), texture_(texture), charges_(0) {}
	void render() override;
	void initComponent() override;

	inline void addCharge(int charges) { 
		charges_ += charges; 
		if (charges_ > MAX_CHARGES) charges_ = MAX_CHARGES;
        std::cout << charges_ << std::endl;
	}
	inline void resetCharges() { charges_ = 0; }
	inline int numCharges() const { return charges_; }
};

