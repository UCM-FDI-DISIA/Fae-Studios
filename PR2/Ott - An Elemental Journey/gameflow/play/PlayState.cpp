#pragma once
#include "PlayState.h"
#include "../../SDLApplication.h"
#include "../../gameobjects/Physics/Ground.h"
#include "../../gameobjects/Ott/Ott.h"

PlayState::PlayState(SDLApplication* app) : GameState(2, app) {
	ott = new Ott(Vector2D(0, 0), app->getTexture("ott", 2), this, Scale(0.3f, 0.3f));

	gr = new Ground(Vector2D(0, 400), app->getTexture("whiteBox", 2), Scale(0.8f, 0.25f));
	gameObjects.push_back(gr);
	gameObjects.push_back(ott);

	groundObjects.push_back(gr);
	physicObjects.push_back(ott);
	camera = { 0,0,LEVEL_WIDTH, LEVEL_HEIGHT };
}

void PlayState::ottCollide(const SDL_Rect& Ott, const SDL_Rect& onGround, SDL_Rect& colRect, bool& col, bool& ground) {
	/*
		COMPROBACIÓN DE COLISIONES CON OBJETOS DE TIPO SUELO
	*/
	for (auto it : groundObjects) {
		ground = it->collide(onGround, colRect);
	}

	//for(auto it : )
}
void PlayState::update() {
	GameState::update();

	for (auto it : physicObjects) {
		if (!static_cast<Ott*>(it)->isGrounded()) {
			static_cast<Ott*>(it)->useGravity();
		}
	}

	// Centro la camara para qu
	SDL_Rect ottRect = ott->getRect();
	camera.x = (ottRect.x + ottRect.w / 2) - WINDOW_WIDTH / 2;
	camera.y = (ottRect.y + ottRect.h / 2) - WINDOW_HEIGHT / 2;


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