#pragma once
#include "../../checkML.h"
#include "PlayState.h"
#include "../../SDLApplication.h"
#include "../../gameobjects/Physics/Ground.h"
#include "../../gameobjects/Ott/Ott.h"
#include "../menus/MainMenuState.h"
#include "../menus/PauseMenuState.h"
#include "../../ui/HealthBar.h"
#include "../../ui/ChargedAttackBar.h"

PlayState::PlayState(SDLApplication* app) : GameState(PLAY_STATE, app) {
	ott = new Ott(Vector2D(0, 0), app->getTexture("ott", PLAY_STATE), this, Scale(0.3f, 0.3f));
	currentMap = new Mapa(app, LEVEL1);
	cout << ott->getRect().w << " " << ott->getRect().h << endl;
	gameObjects.push_back(currentMap);
	gr = new Ground(Vector2D(0, 750), app->getTexture("whiteBox", PLAY_STATE), Scale(2.0f, 0.01f));
	gr1 = new Ground(Vector2D(250, 650), app->getTexture("whiteBox", PLAY_STATE), Scale(0.5f, 0.01f));
	gr2 = new Ground(Vector2D(400, 600), app->getTexture("whiteBox", PLAY_STATE), Scale(0.5f, 0.01f));
	Sanctuary* sct = new Sanctuary(Vector2D(200, 280), app->getTexture("whiteBox", PLAY_STATE), Scale(0.05f, 0.1f));
	gameObjects.push_back(sct);
	Sanctuary* sct2 = new Sanctuary(Vector2D(400, 280), app->getTexture("whiteBox", PLAY_STATE), Scale(0.05f, 0.1f));
	gameObjects.push_back(sct2);
	auto a = currentMap->getObjects();
	for (auto it : a) {

		float x_ = it.getAABB().left;
		float y_ = it.getAABB().top;
		float w_= it.getAABB().width;
		float h_ = it.getAABB().height;

		grT = new Ground(Vector2D(x_, y_), app->getTexture("whiteBox", PLAY_STATE), Scale(w_, h_));
		gameObjects.push_back(grT);
		groundObjects.push_back(grT);
	}
	gameObjects.push_back(gr);
	gameObjects.push_back(gr1);
	gameObjects.push_back(gr2);
	gameObjects.push_back(ott);


	groundObjects.push_back(gr);
	groundObjects.push_back(gr1);
	groundObjects.push_back(gr2);
	physicObjects.push_back(ott);

    HealthBar* healthBar = new HealthBar(Vector2D(30, 100), app->getTexture("hearts", PLAY_STATE), Scale(10.0f, 10.0f));
	gameObjects.push_back(healthBar);
    gameObjects.push_back(new ChargedAttackBar(healthBar->lastHeartPosition() + Vector2D(100, -10), app->getTexture("chargebar", PLAY_STATE), Scale(1.5f, 1.5f)));
	camera = { 0,0,WINDOW_WIDTH, WINDOW_HEIGHT };
}

void PlayState::ottCollide(const SDL_Rect& Ott, const SDL_Rect& onGround, SDL_Rect& colRect, bool& col, bool& ground) {
	/*
		COMPROBACI�N DE COLISIONES CON OBJETOS DE TIPO SUELO
	*/
	for (auto it : groundObjects) {
		ground = it->collide(onGround, colRect);
		if (ground && (colRect.w >= colRect.h)) break;
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
	camera.y = (ottRect.y + ottRect.h / 2) - WINDOW_HEIGHT*0.82;


	// Limites de la camara dependiendo del tama�o de la sala (mapa)
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

void PlayState::render() const {
	//Recorremos la lista para renderizar los objetos,
	// y en caso de que se haya borrado un elemento en la lista, dejamos de recorrerla
	for (auto it = gameObjects.begin(); it != gameObjects.end() && !deleted;) {
		(*it)->render(camera);
		if (!deleted) ++it;
		else return;
	}
}
void PlayState::backToMenu() {
	app->getStateMachine()->changeState(new MainMenuState(app));
}

void PlayState::handleEvents(SDL_Event& e) {
	GameState::handleEvents(e);
	if (e.type == SDL_KEYUP) {
		if (e.key.keysym.sym == SDLK_ESCAPE) app->getStateMachine()->pushState(new PauseMenuState(app));
	}
}
Vector2D PlayState::checkCollisions()
{
	Vector2D resultVector = ( 0,0 );
	auto a = currentMap->getObjects();
	for (auto it : a) {
		SDL_Rect obstRect;
		obstRect.x = it.getAABB().left;
		obstRect.y = it.getAABB().top;
		obstRect.w = it.getAABB().width;
		obstRect.h = it.getAABB().height;
		SDL_Rect ottRect = ott->getRect();
		if (SDL_HasIntersection(&ottRect, &obstRect)) {
			resultVector = collides(ott->getRect(), obstRect);
		}
	}
	cout << resultVector.getX() << " " << resultVector.getY() << endl;
	return resultVector;
}
Vector2D PlayState::collides(SDL_Rect playerRect, SDL_Rect objRect) { //Se comprueba si el bloque colisiona con la bola
	Vector2D cVector (0, 0);
	SDL_Rect areaColision; // area de colision 	
	bool interseccion = SDL_IntersectRect(&playerRect, &objRect, &areaColision);
	if (interseccion)
	{
		if ((areaColision.w < areaColision.h)) { //Colisión lateral
			if (areaColision.x <= objRect.x + (objRect.w / 2)) cVector = ( -1,0 ); //Colisión por la izquierda
			else cVector = ( 1,0 ); //Colisión lado derecho
		}
		else {
			if (areaColision.y < objRect.y + (objRect.h / 2)) cVector = ( 0,-1 ); //Colisión por arriba
			else cVector = ( 0,1 );
		}
	}
	//cout << cVector.getX() << " " << cVector.getY() << endl;
	return cVector;
}