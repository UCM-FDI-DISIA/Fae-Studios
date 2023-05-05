#include "CameraComponent.h"
#include "../sdlutils/SDLUtils.h"
#include "../utils/checkML.h"
#include "../states/PlayState.h"
#include "../states/GameStateMachine.h"
#include "PlayerInput.h"
#include "PhysicsComponent.h"
inline float lerp(float a, float b, float t) {
	return a + t * (b - a);
}
void CameraComponent::initComponent() {
	playerTrnf_ = mngr_->getPlayer()->getComponent<Transform>();
	tr_ = ent_->getComponent<Transform>();
}

void CameraComponent::update() {
	if (camerashake) {
		int timeInBetween = SDL_GetTicks() - timer;
		if (left && timeInBetween <= 50) {
			camera.x += 10;

		}
		else if (left && timeInBetween > 50) {
			left = false;
			right = true;
			timer = SDL_GetTicks();
		}
		timeInBetween = SDL_GetTicks() - timer;

		if (right && timeInBetween <= 50) {
			camera.x -= 10;
		}
		else if (right && timeInBetween > 50) {
			left = true;
			right = false;
			timer = SDL_GetTicks();
		}
	}
	else if(lookingDown) {
		camera.y = lerp(camera.y, posFin + (posFin - posIni), 0.002);
		if ((posFin - camera.y)*0.002 <= 0.1) {
			lookingUp = true;
			lookingDown = false;
			timer = SDL_GetTicks();
		}
	}
	else if (lookingUp) {
		int aux = SDL_GetTicks() - timer;
		if (aux >= 2000) {
			lookingUp = false;
			mngr_->getPlayer()->getComponent<PlayerInput>()->finishedLookingDown();
		}
	}
	
	else {
		SDL_Rect ottRect = playerTrnf_->getRect(); // conseguir la posici�n de Ott
		// mover camera.x
		// Comprobamos si la c�mara est� suficientemente cerca del jugador. En caso de que lo est�, la posici�n se settea a la 
		// posici�n del jugador. En caso contrario, se hace una interpolaci�n lineal para acercarse "lentalmente". Esto solo se aprecia cuando
		// la c�mara viaja grandes distancias (entre l�mparas, por ejemplo). 
		camera.x = lerp(camera.x, ((ottRect.x + ottRect.w / 2) - sdlutils().width() / 2), 0.03);

		// mover camera.y
		// Setteamos un deadzone donde la c�mara no tiene porqu� moverse (CAM_DEAD_ZONE). En caso de que el personaje salga de esta
		// zona, la c�mara se mueve. Tambi�n se mover� si est� por debajo del m�nimo admitido (CAM_OFFSET_HEIGHT * camera.h)
		// Siempre se calcula la posici�n con interpolaci�n lineal

		// RETOCAR ESTAS COSAS
		if (ottRect.y > camera.y + camera.h - CAM_DEAD_ZONE || ottRect.y < camera.y + CAM_DEAD_ZONE) {
			camera.y = lerp(camera.y, (ottRect.y + ottRect.h / 2) - CAM_OFFSET_HEIGHT * sdlutils().height(), 0.01);
		}

		// Limites de la camara dependiendo del tama�o de la sala (mapa)

		if (camera.x > bounds.x + bounds.w - tr_->getWidth()) {
			camera.x = bounds.x + bounds.w - tr_->getWidth();
		}
		if (camera.x < bounds.x) {
			camera.x = bounds.x;
		}
		if (camera.y > bounds.y + bounds.h - tr_->getHeight()) {
			camera.y = bounds.y + bounds.h - tr_->getHeight();
		}
		if (camera.y < bounds.y) {
			camera.y = bounds.y;
		}

		camera = { camera.x,camera.y,sdlutils().width(), sdlutils().height() };

	}
}

bool CameraComponent::canLookDown() {
	return (camera.y + camera.h / 2) <= bounds.y + bounds.h - tr_->getHeight();
}
void CameraComponent::startLookingDown() {
	posFin = camera.y + (camera.h / 2);
	posIni = camera.y;
}