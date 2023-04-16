#include "../sdlutils/Texture.h"
#include <vector>
#include "../ecs/Component.h"
#include "CameraComponent.h"
#pragma once

// COLUMNAS DE LA TEXTURA
const int FULL_HEART = 0; // corazón lleno
const int WEAK_HEART = 2; // corazón débil
const int EMPTY_HEART = 1; // corazón vacío

class HealthImage : public Component
{
public:
	HealthImage(Texture* health_text, int numHearts, SDL_Rect pos) : // constructora uwu
		tex_(health_text), numHearts(numHearts), lastFullHeart(numHearts-1), pos(pos)
	{ 
		heartState.reserve(numHearts); // settear los valores de todos los corazones a LLENO
		for (int i = 0; i < numHearts; ++i) {
			heartState.push_back(FULL_HEART);
		}
	};
	virtual ~HealthImage() {}; // destructora vacía
	virtual void render(); // guess
	bool setWeak(); // pone el último corazón lleno a débil
	void reset(); // resettea la barra de vida
	void die(); // muerte y destrucción
	void damage(int num); // dañar X puntos
	inline void increaseLife() { numHearts++; heartState.push_back(FULL_HEART); reset(); }
	constexpr static ecs::cmpId_type id = ecs::_HEALTH_IMAGE; // ID
	inline SDL_Rect getLastHeartPos() const {
		SDL_Rect tmp = pos;
		tmp.x += (numHearts - 1) * OFFSET_X * pos.w;
		return tmp;
	}
	void changeElement(ecs::elements newElem) {
		if (newElem == ecs::Light) row = 0;
		else if (newElem == ecs::Earth) row = 1;
		else if (newElem == ecs::Water) row = 2;
		else if (newElem == ecs::Fire) row = 3;
	};
private:
	Texture* tex_; // textura usada
	int col = 0; // columna
	int row = 0; 
	const float OFFSET_X = 1.25f; // offset de separación entre corazones
	int numHearts, lastFullHeart; // número de corazones y posición del último corazón no vacío
	std::vector<int> heartState; // vector con el estado de cada corazón
	SDL_Rect pos; // posición de renderizado recibida en el constructor
};

