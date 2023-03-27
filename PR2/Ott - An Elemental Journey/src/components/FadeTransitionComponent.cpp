#include "FadeTransitionComponent.h"

void FadeTransitionComponent::render() {
	SDL_Rect scr = { 0,0, (int)sdlutils().getWindowDimensions().getX(), (int)sdlutils().getWindowDimensions().getY() };
	sdlutils().images().at("blackbackground").setAlpha(alpha);
	sdlutils().images().at("blackbackground").render(scr);
}

void FadeTransitionComponent::update() {
	if (active) {
		inProgress = true;
		if (opaqueToTransparent && alpha >= (0 + speed)) alpha -= speed;
		else if (!opaqueToTransparent && alpha <= (255 - speed)) alpha += speed;
	}

	if (hasEndedAnimation() && inProgress) {
		inProgress = false;
		if (execute && !executed) {
			executed = true;
			callback();
		}
	}

}