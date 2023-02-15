#pragma once
#include "PlayState.h"
#include "../../SDLApplication.h"
#include "../../gameobjects/Physics/Ground.h"
#include "../../gameobjects/Ott/Ott.h"
#include "../../gameobjects/InteractuableObject.h"

bool PlayState::Interacting = false;

void PlayState::handleEvents(SDL_Event& e) {
	GameState::handleEvents(e);
	if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_e && !PlayState::Interacting) { PlayState::Interacting = true; }
	else if (e.type == SDL_KEYUP && e.key.keysym.sym == SDLK_e) PlayState::Interacting = false;
}

PlayState::PlayState(SDLApplication* app) : GameState(2, app) {
	TP_Lamp* l1 = new TP_Lamp(Vector2D(200, 280), app->getTexture("lamp", 2), this, Scale(2, 2));
	TP_Lamp* l2 = new TP_Lamp(Vector2D(400, 280), app->getTexture("lamp", 2), this, Scale(2, 2));
	TP_Lamp* l3 = new TP_Lamp(Vector2D(600, 280), app->getTexture("lamp", 2), this, Scale(2, 2));
	l1->SetLamp(l2);
	l2->SetLamp(l1);
	l3->SetLamp(l2);

	Grass* g1 = new Grass(Vector2D(800, 399), app->getTexture("whiteBox", 2), this, Scale(0.1f, 0.01f), 0.50f);
	gameObjects.push_back(g1);
	intObjects.push_back(g1);
	

	ott = new Ott(Vector2D(0, 0), app->getTexture("ott", 2), this, Scale(0.3f, 0.3f));

	gr = new Ground(Vector2D(0, 400), app->getTexture("whiteBox", 2), Scale(3.0f, 0.25f));
	Sanctuary* sct = new Sanctuary(Vector2D(200, 280), app->getTexture("whiteBox", 2), Scale(0.05f, 0.1f));
	gameObjects.push_back(sct);
	Sanctuary* sct2 = new Sanctuary(Vector2D(400, 280), app->getTexture("whiteBox", 2), Scale(0.05f, 0.1f));
	gameObjects.push_back(sct2);
	
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

	camera = { 0,0,WINDOW_WIDTH, WINDOW_HEIGHT };
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

	for (auto it : intObjects) {
		SDL_Rect result;
		if (it->collide(ott->getRect(), result))
		{ 
			it->interact(); 
		}
	}
	
	for (auto it : eObjects) {
		SDL_Rect result;
		if (it->collide(ott->getRect(), result))
		{ 
			cout << "Climbing" << endl;
			ott->canClimb();
		}
		else {
			cout << "Not climbing" << endl;
			ott->cannotClimb();
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
	ott->setPos(newPos);
}

void PlayState::addEnredadera(const Vector2D& pos) {

	cout << "hola" << endl;
	Enredaderas* e1 = new Enredaderas(Vector2D(pos.getX(), pos.getY() - app->getTexture("enredadera", 2)->getH()), app->getTexture("enredadera", 2), this);
	gameObjects.push_back(e1);
	eObjects.push_back(e1);

}
