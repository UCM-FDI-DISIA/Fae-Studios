#include "InteractuableObject.h"

void TP_Lamp::interact() {
	SDL_Rect pairedRect = pairedLamp->getRect();
	cout << pairedRect.x  << endl;
	pairedRect.y = pairedRect.y + pairedRect.h - game->ottPos().h;
	Vector2D newPos = Vector2D(pairedRect.x, pairedRect.y);
	game->setOttPos(newPos);
	PlayState::Interacting = false;
}

bool InteractuableObject::collide(const SDL_Rect& obj, SDL_Rect& result) {
	const SDL_Rect rect = getRect();
	return PlayState::IsInteracting() && SDL_IntersectRect(&obj, &rect, &result);
}