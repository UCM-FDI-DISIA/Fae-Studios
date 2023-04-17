#pragma once
#include "../ecs/Component.h"
#include "ChargedAttackBar.h"
class AttackCharger : public Component {
private:
	int maxCharge, currentCharge;
    ChargedAttackBar* chargedBar_;

public:
	AttackCharger(int max) : Component(), maxCharge(max), currentCharge(0) {};
	inline int& getCharge() { return currentCharge; }
	inline void addCharge(int n) {
		if (currentCharge + n >= maxCharge) {
			currentCharge = maxCharge;
		}
		else currentCharge += n;

        chargedBar_->addCharge(n);
	}
    inline void resetCharges() {
        currentCharge = 0;
        chargedBar_->resetCharges();
    }
	inline bool hasChargedAttack() { return currentCharge >= maxCharge; }
    inline void initComponent() override {
        chargedBar_ = ent_->getComponent<ChargedAttackBar>();
    }
	constexpr static ecs::cmpId_type id = ecs::_CHARGED_ATTACK;
};

