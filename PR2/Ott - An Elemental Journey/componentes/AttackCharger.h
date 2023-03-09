#pragma once
#include "Component.h"
class AttackCharger : public Component
{
private:
	int maxCharge, currentCharge;
public:
	AttackCharger(int max) : Component(), maxCharge(max), currentCharge(0) {};
	inline int getCharge() { return currentCharge; }
	inline void addCharge(int n) {
		if (currentCharge + n >= maxCharge)
			currentCharge = maxCharge;
		else
			currentCharge += n;
	}
};

