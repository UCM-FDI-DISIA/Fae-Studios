#include "../sdlutils/Texture.h"
#include <vector>
#include "../ecs/Component.h"
#include "CameraComponent.h"
#pragma once

// COLUMNAS DE LA TEXTURA
const int FULL_HEART = 0; // coraz�n lleno
const int WEAK_HEART = 2; // coraz�n d�bil
const int EMPTY_HEART = 1; // coraz�n vac�o

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
	virtual ~HealthImage() {}; // destructora vac�a
	virtual void render(); // guess
	bool setWeak(); // pone el �ltimo coraz�n lleno a d�bil
	void reset(); // resettea la barra de vida
	void die(); // muerte y destrucci�n
	void damage(int num); // da�ar X puntos
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
	const float OFFSET_X = 1.25f; // offset de separaci�n entre corazones
	int numHearts, lastFullHeart; // n�mero de corazones y posici�n del �ltimo coraz�n no vac�o
	std::vector<int> heartState; // vector con el estado de cada coraz�n
	SDL_Rect pos; // posici�n de renderizado recibida en el constructor
};

