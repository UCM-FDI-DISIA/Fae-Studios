#include "HealthImage.h"
#include "../ecs/Entity.h"

void HealthImage::die() {
	for (int o = 0; o <= lastFullHeart; ++o) {
		heartState[o] = EMPTY_HEART; // settear todos los corazones a vac�o
	}
}

void HealthImage::damage(int num) { // da�ar X puntos
	int i = lastFullHeart; 
	if (i - num < 0) { // si se queda a menos que 0, eso significa que ott ha muerto
		die();
	}
	else if (heartState[i] == WEAK_HEART) { // settear a WEAK el nuevo �ltimo coraz�n no da�ado
		heartState[i - num] = WEAK_HEART;
	}
	
	for (int o = i - num + 1; o <= i; ++o) { // vaciar los corazones da�ados
		heartState[o] = EMPTY_HEART;
	}
	lastFullHeart = i - num; // actualizar �ltimo coraz�n lleno
}

bool HealthImage::setWeak() { // poner a d�bil �ltimo coraz�n
	if (heartState[lastFullHeart] == WEAK_HEART) 
	{ 
		heartState[lastFullHeart] = EMPTY_HEART; // da�ar coraz�n ya d�bil
		if (lastFullHeart == 0) {
			die(); // morir si se ha quitado la �ltima vida
		}
		return true; // booleano que indica si se ha hecho da�o o no
	}
	else heartState[lastFullHeart] = WEAK_HEART; // cambiar a d�bil
	return false; // booleano para saber si se ha hecho da�o o no
}

void HealthImage::reset() { // resetteo de los corazones
	for (int o = 0; o < numHearts; ++o) {
		heartState[o] = FULL_HEART;
	}
	lastFullHeart = numHearts - 1;
}

void HealthImage::render() { // try and guess :)
	auto cam = mngr_->getCamera()->getComponent<CameraComponent>()->camera;
	for (int i = 0; i < numHearts; ++i) {
		SDL_Rect finalPos = pos;
		finalPos.x += i * OFFSET_X * pos.w;
		tex_->renderFrame(finalPos, row, heartState[i]);
	}
}