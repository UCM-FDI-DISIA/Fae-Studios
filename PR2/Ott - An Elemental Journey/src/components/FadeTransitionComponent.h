#pragma once
#include "../ecs/Component.h"
#include <SDL.h>
#include "../sdlutils/SDLUtils.h"
#include <functional>

class FadeTransitionComponent : public Component {
private:
	bool opaqueToTransparent;
	int alpha;
	bool active;
	bool inProgress;
	bool execute;
	bool executed;
	std::function<void()> callback;
	int speed;

public:
	constexpr static ecs::cmpId_type id = ecs::_FADEOUTANIM;
	FadeTransitionComponent(bool opaqueToTransparent, int speed = 5) : opaqueToTransparent(opaqueToTransparent), active(false), inProgress(false), execute(true), executed(false), callback(nullptr), speed(speed) {
		sdlutils().images().at("blackbackground").setAlpha(255);
		
		if (this->opaqueToTransparent) alpha = 255;
		else alpha = 0;
	}
	void render() override;
	void update() override;
	inline void revert() {inProgress = true; opaqueToTransparent = !opaqueToTransparent; execute = true; executed = false;}
	inline void revertWithoutExecute() { inProgress = true; opaqueToTransparent = !opaqueToTransparent; execute = false; };
	inline void activate() { active = true; execute = true; }
	inline void deactivate() { active = false; }
	inline void activateWithoutExecute() { active = true; execute = false; };
	inline void setFunction(std::function<void()> const& c) { callback = c; }
	inline bool hasEndedAnimation() { return (alpha == 0 || alpha == 255); }
	inline void changeSpeed(int speed) { this->speed = speed; }
};

