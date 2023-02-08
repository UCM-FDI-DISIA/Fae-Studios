#include "Trigger.h"
Trigger::Trigger(float x, float y, float w, float h, GameObject* g, Enter* en) {
	gameObject = g;
	enter = en;
}

void Trigger::OnEnter() {
	if(enter != nullptr)
		enter(gameObject);
}
