#pragma once
#include "../ecs/Component.h"
#include <SDL.h>
#include "../sdlutils/SDLUtils.h"

class FadeTransitionComponent : public Component {
private:
	bool opaqueToTransparent;
	int alpha;
	bool active;

public:
	constexpr static ecs::cmpId_type id = ecs::_FADEOUTANIM;
	FadeTransitionComponent(bool opaqueToTransparent) : opaqueToTransparent(opaqueToTransparent), active(false) {
		sdlutils().images().at("blackbackground").setAlpha(255);
		
		if (this->opaqueToTransparent) alpha = 255;
		else alpha = 0;
	}
	void render() override;
	void update() override;
	inline void revert() { opaqueToTransparent = !opaqueToTransparent; }
	inline void activate() { active = true; }
	inline void deactivate() { active = false; }
	inline bool hasEndedAnimation() { return (alpha == 0 || alpha == 255); }
};

