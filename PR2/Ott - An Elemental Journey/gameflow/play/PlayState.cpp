#pragma once
#include "PlayState.h"
#include "../../SDLApplication.h"
#include "../../gameobjects/Physics/Ground.h"
#include "../../gameobjects/Ott/Ott.h"
#include "../../gameobjects/InteractuableObject.h"

// función para hacer interpolación lineal. Usada en el movimiento de la cámara
float lerp(float a, float b, float t)
{
	return a + t * (b - a);
}

void PlayState::handleEvents(SDL_Event& e) {
	GameState::handleEvents();
}

PlayState::PlayState(SDLApplication* app) : GameState(2, app) {
	TP_Lamp* l1 = new TP_Lamp(Vector2D(500, 280), app->getTexture("lamp", 2), this, Scale(2, 2), LAMP);
	TP_Lamp* l2 = new TP_Lamp(Vector2D(1500, 280), app->getTexture("lamp", 2), this, Scale(2, 2), LAMP);
	TP_Lamp* l3 = new TP_Lamp(Vector2D(2000, 280), app->getTexture("lamp", 2), this, Scale(2, 2), LAMP);
	l1->SetLamp(l2);
	l2->SetLamp(l1);
	l3->SetLamp(l2);

	Grass* g1 = new Grass(Vector2D(800, 399), app->getTexture("whiteBox", 2), this, Scale(0.1f, 0.01f), 0.50f);
	gameObjects.push_back(g1);
	intObjects.push_back(g1);
	
	ott = new Ott(Vector2D(0, 0), app->getTexture("ott", 2), this, Scale(0.3f, 0.3f));

	gr = new Ground(Vector2D(0, 400), app->getTexture("whiteBox", 2), Scale(3.0f, 0.25f));
	// santuarios
	/*Sanctuary* sct = new Sanctuary(Vector2D(200, 280), app->getTexture("whiteBox", 2), Scale(0.05f, 0.1f));
	gameObjects.push_back(sct);
	Sanctuary* sct2 = new Sanctuary(Vector2D(400, 280), app->getTexture("whiteBox", 2), Scale(0.05f, 0.1f));
	gameObjects.push_back(sct2);
	*/
	gameObjects.push_back(gr);

	gameObjects.push_back(l1);
	gameObjects.push_back(l2);
	gameObjects.push_back(l3);

	intObjects.push_back(l1);
	intObjects.push_back(l2);
	intObjects.push_back(l3);

	gameObjects.push_back(ott);
	groundObjects.push_back(gr);
	physicObjects.push_back(ott);

	// Rect de la cámara
	camera = { 0,0,WINDOW_WIDTH, WINDOW_HEIGHT };
}

void PlayState::moveCamera() {
	SDL_Rect ottRect = ott->getRect(); // conseguir la posición de Ott

	// mover camera.x
	// Comprobamos si la cámara está suficientemente cerca del jugador. En caso de que lo esté, la posición se settea a la 
	// posición del jugador. En caso contrario, se hace una interpolación lineal para acercarse "lentalmente". Esto solo se aprecia cuando
	// la cámara viaja grandes distancias (entre lámparas, por ejemplo). 
	if (ottRect.x + ottRect.w / 2 - camera.x <= 10 && ottRect.x + ottRect.w / 2 - camera.x >= -10) camera.x = (int)((ottRect.x + ottRect.w / 2) - WINDOW_WIDTH / 2);
	else camera.x = lerp(camera.x, (int)((ottRect.x + ottRect.w / 2) - WINDOW_WIDTH / 2), 0.02);

	// mover camera.y
	// Setteamos un deadzone donde la cámara no tiene porqué moverse (CAM_DEAD_ZONE). En caso de que el personaje salga de esta
	// zona, la cámara se mueve. También se moverá si está por debajo del mínimo admitido (CAM_OFFSET_HEIGHT * camera.h)
	// Siempre se calcula la posición con interpolación lineal
	if (ottRect.y < camera.y + camera.h - CAM_DEAD_ZONE || ottRect.y > camera.y + CAM_OFFSET_HEIGHT * camera.h) {
		camera.y = lerp(camera.y, (ottRect.y + ottRect.h / 2) - CAM_OFFSET_HEIGHT * WINDOW_HEIGHT, 0.1);
	}

	// Limites de la camara dependiendo del tamaño de la sala (mapa)
	if (camera.x < 0)
	{
		camera.x = 0;
	}
	if (camera.y < 0)
	{
		camera.y = 0;
	}
	if (camera.x > LEVEL_WIDTH - camera.w)
	{
		camera.x = LEVEL_WIDTH - camera.w;
	}
	if (camera.y > LEVEL_HEIGHT - camera.h)
	{
		camera.y = LEVEL_HEIGHT - camera.h;
	}
}

void PlayState::ottCollide(const SDL_Rect& Ott, const SDL_Rect& onGround, SDL_Rect& colRect, bool& col, bool& ground) {
	// COMPROBACIÓN DE COLISIONES CON OBJETOS DE TIPO SUELO (PROVISIONAL)
	for (auto it : groundObjects) {
		ground = it->collide(onGround, colRect);
	}
}

void PlayState::update() {
	GameState::update(); // llamada a todos los updates de la lista de gameObjects

	// ACTIVAR GRAVEDAD PARA TODOS LOS OBJETOS FÍSICOS
	for (auto it : physicObjects) {
		if (!it->isGrounded()) {
			it->useGravity();
		}
	}

	// COMPROBACIÓN PARA ACTIVAR OBJETOS INTERACTUABLES
	for (auto it : intObjects) {
		SDL_Rect result;
		if (it->collide(ott->getRect(), result)) // SI SE HA DETECTADO INTERACCIÓN CON EL OBJETO, SE ACTIVA
		{ 
			it->interact(); // ACTIVACIÓN DEL OBJETO

			if (it->getType() == LAMP) { // Si el objeto es de tipo LÁMPARA debe cambiar una animación de Ott
				ott->setAnimState(TP_IN);
			}
		}
	}

	// MOVIMIENTO DE LA CÁMARA EN FUNCIÓN DE POSICIÓN DE OTT
	moveCamera();
}

void PlayState::render() const {
	//Recorremos la lista para renderizar los objetos,
	// y en caso de que se haya borrado un elemento en la lista, dejamos de recorrerla
	for (auto it = gameObjects.begin(); it != gameObjects.end() && !deleted;) {
		(*it)->render(camera);
		if (!deleted) ++it;
		else return;
	}
}

SDL_Rect PlayState::ottPos() const {
	return ott->getRect();
}

void PlayState::setOttPos(const Vector2D& newPos) {
	ott->setTpPoint(newPos);
}

void PlayState::addEnredadera(const Vector2D& pos, const Scale& scale) {

	// añadir una enredadera al mapa y las listas de objetos
	Enredaderas* e1 = new Enredaderas(pos, app->getTexture("whiteBox", 2), this, scale);
	gameObjects.push_back(e1);
	intObjects.push_back(e1);

}

void PlayState::climb() {
	ott->canClimb();
}