#include "../sdlutils/Texture.h"
#include <vector>
#include "../ecs/Component.h"
#include "CameraComponent.h"
#pragma once

// COLUMNAS DE LA TEXTURA
const int FULL_HEART = 1; // corazón lleno
const int WEAK_HEART = 12; // corazón débil
const int EMPTY_HEART = 4; // corazón vacío

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
	constexpr static ecs::cmpId_type id = ecs::_HEALTH_IMAGE; // ID
private:
	Texture* tex_; // textura usada
	int col = 0; // columna
	const int row = 0; // fila constante porque nunca será distinta de 0 (al menos con esta texture)
	const float OFFSET_X = 1.25f; // offset de separación entre corazones
	int numHearts, lastFullHeart; // número de corazones y posición del último corazón no vacío
	std::vector<int> heartState; // vector con el estado de cada corazón
	SDL_Rect pos; // posición de renderizado recibida en el constructor
};

