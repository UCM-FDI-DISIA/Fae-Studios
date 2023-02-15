#pragma once
#include "../../checkML.h"
#include "PlayState.h"
#include "../../gameobjects/Ott/Ott.h"
#include "../../SDLApplication.h"
#include "../../gameobjects/Physics/Ground.h"
#include "../menus/PauseMenuState.h"
#include "../../ui/HealthBar.h"
#include "../../ui/ChargedAttackBar.h"
#include "../../ui/ScreenDarkener.h"

PlayState::PlayState(SDLApplication* app) : GameState(PLAY_STATE, app) {
	//currentMap = new Mapa(app, LEVEL1);
	//gameObjects.push_back(currentMap);
	Ott* ott = new Ott(Vector2D(0, 0), app->getTexture("ott", getStateID()), this, Scale(0.3f, 0.3f));

	gr = new Ground(Vector2D(0, 400), app->getTexture("whiteBox", getStateID()), Scale(0.8f, 0.25f));
	gameObjects.push_back(gr);
	gameObjects.push_back(ott);

	groundObjects.push_back(gr);
	physicObjects.push_back(ott);

    HealthBar* healthBar = new HealthBar(Vector2D(30, 100), app->getTexture("hearts", getStateID()), Scale(10.0f, 10.0f));
	gameObjects.push_back(healthBar);
    gameObjects.push_back(new ChargedAttackBar(healthBar->lastHeartPosition() + Vector2D(100, -10), app->getTexture("chargebar", getStateID()), Scale(1.5f, 1.5f)));
    gameObjects.push_back(new ScreenDarkener(app));
}

void PlayState::ottCollide(const SDL_Rect& Ott, const SDL_Rect& onGround, SDL_Rect& colRect, bool& col, bool& ground) {
	/*
		COMPROBACI�N DE COLISIONES CON OBJETOS DE TIPO SUELO
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
}

void PlayState::handleEvents(SDL_Event& e) {
	GameState::handleEvents(e);
	if (e.type == SDL_KEYUP) {
		if (e.key.keysym.sym == SDLK_ESCAPE) app->getStateMachine()->pushState(new PauseMenuState(app));
	}
}