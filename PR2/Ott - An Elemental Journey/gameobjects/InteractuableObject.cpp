#include "InteractuableObject.h"
#include "../utils/InputHandler.h"

void TP_Lamp::interact() {
	if (canTP) {
		SDL_Rect pairedRect = pairedLamp->getRect();
		cout << "INTERACTION" << endl;
		pairedRect.y = pairedRect.y + pairedRect.h - game->ottPos().h;
		Vector2D newPos = Vector2D(pairedRect.x, pairedRect.y);
		game->setOttPos(newPos);
		canTP = false;
		pairedLamp->canTP = false;
		pairedLamp->timer = 0;
	}
}

void TP_Lamp::update() {
	timer++;
	if (!canTP && timer > MAX_TIME) {
		timer = 0;
		canTP = true;
	}
}

bool TP_Lamp::collide(const SDL_Rect& obj, SDL_Rect& result) {
	const SDL_Rect rect = getRect();
	return canTP && InputHandler::instance()->isKeyJustDown(SDLK_f) && SDL_IntersectRect(&obj, &rect, &result);
}

bool InteractuableObject::collide(const SDL_Rect& obj, SDL_Rect& result) {
	const SDL_Rect rect = getRect();
	return InputHandler::instance()->isKeyJustDown(SDLK_f) && SDL_IntersectRect(&obj, &rect, &result);
}