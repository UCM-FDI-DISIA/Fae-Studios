#pragma once
#include "../../checkML.h"
#include "PlayState.h"
#include "../../SDLApplication.h"
#include "../../gameobjects/Physics/Ground.h"
#include "../../gameobjects/Ott/Ott.h"
#include "../../gameobjects/InteractuableObject.h"
#include "../../gameflow/menus/PauseMenuState.h"
#include "../../gameflow/menus/MainMenuState.h"
#include "../../ui/HealthBar.h"
#include "../../ui/ChargedAttackBar.h"
#include "../../utils/InputHandler.h"

// funci�n para hacer interpolaci�n lineal. Usada en el movimiento de la c�mara
float lerp(float a, float b, float t)
{
	return a + t * (b - a);
}

void PlayState::handleEvents() {
	GameState::handleEvents();
	if (InputHandler::instance()->isKeyDown(SDLK_ESCAPE)) {
		app->getStateMachine()->pushState(new PauseMenuState(app));
	}
}

PlayState::PlayState(SDLApplication* app) : GameState(PLAY_STATE, app) {
	TP_Lamp* l1 = new TP_Lamp(Vector2D(500, 280), app->getTexture("lamp", PLAY_STATE), this, Scale(2, 2), LAMP);
	TP_Lamp* l2 = new TP_Lamp(Vector2D(1500, 280), app->getTexture("lamp", PLAY_STATE), this, Scale(2, 2), LAMP);
	TP_Lamp* l3 = new TP_Lamp(Vector2D(2000, 280), app->getTexture("lamp", PLAY_STATE), this, Scale(2, 2), LAMP);
	l1->SetLamp(l2);
	l2->SetLamp(l1);
	l3->SetLamp(l2);
	currentMap = new Mapa(app, LEVEL1);
	gameObjects.push_back(currentMap);

	Grass* g1 = new Grass(Vector2D(800,400- app->getTexture("grass", PLAY_STATE)->getH()), app->getTexture("grass", PLAY_STATE), this);
	gameObjects.push_back(g1);
	intObjects.push_back(g1);
	
	ott = new Ott(Vector2D(400, 2000), app->getTexture("ott", PLAY_STATE), this, Scale(0.3f, 0.3f));

	// santuarios
	/*Sanctuary* sct = new Sanctuary(Vector2D(200, 280), app->getTexture("whiteBox", 2), Scale(0.05f, 0.1f));
	gameObjects.push_back(sct);
	Sanctuary* sct2 = new Sanctuary(Vector2D(400, 280), app->getTexture("whiteBox", PLAY_STATE), Scale(0.05f, 0.1f));
	gameObjects.push_back(sct2);
	*/
	auto a = currentMap->getObjects();
	for (auto it : a) {

		float x_ = it.getAABB().left;
		float y_ = it.getAABB().top;
		float w_= it.getAABB().width;
		float h_ = it.getAABB().height;

		auto scale = currentMap->tileScale();

		grT = new Ground(Vector2D(x_ * scale, y_ * scale), app->getTexture("pixel", PLAY_STATE), Scale(w_ * scale, h_ * scale));
		gameObjects.push_back(grT);
		groundObjects.push_back(grT);
	}
	gameObjects.push_back(ott);

	physicObjects.push_back(ott);
    HealthBar* healthBar = new HealthBar(Vector2D(30, 100), app->getTexture("hearts", PLAY_STATE), Scale(10.0f, 10.0f));
	gameObjects.push_back(healthBar);
    gameObjects.push_back(new ChargedAttackBar(healthBar->lastHeartPosition() + Vector2D(100, -10), app->getTexture("chargebar", PLAY_STATE), Scale(1.5f, 1.5f)));
	camera = { 0,0,WINDOW_WIDTH, WINDOW_HEIGHT };
}

void PlayState::moveCamera() {
	SDL_Rect ottRect = ott->getRect(); // conseguir la posici�n de Ott

	// mover camera.x
	// Comprobamos si la c�mara est� suficientemente cerca del jugador. En caso de que lo est�, la posici�n se settea a la 
	// posici�n del jugador. En caso contrario, se hace una interpolaci�n lineal para acercarse "lentalmente". Esto solo se aprecia cuando
	// la c�mara viaja grandes distancias (entre l�mparas, por ejemplo). 
	if (ottRect.x + ottRect.w / 2 - camera.x <= 10 && ottRect.x + ottRect.w / 2 - camera.x >= -10) camera.x = (int)((ottRect.x + ottRect.w / 2) - WINDOW_WIDTH / 2);
	else camera.x = lerp(camera.x, (int)((ottRect.x + ottRect.w / 2) - WINDOW_WIDTH / 2), 0.02);

	// mover camera.y
	// Setteamos un deadzone donde la c�mara no tiene porqu� moverse (CAM_DEAD_ZONE). En caso de que el personaje salga de esta
	// zona, la c�mara se mueve. Tambi�n se mover� si est� por debajo del m�nimo admitido (CAM_OFFSET_HEIGHT * camera.h)
	// Siempre se calcula la posici�n con interpolaci�n lineal
	if (ottRect.y < camera.y + camera.h - CAM_DEAD_ZONE || ottRect.y > camera.y + CAM_OFFSET_HEIGHT * camera.h) {
		camera.y = lerp(camera.y, (ottRect.y + ottRect.h / 2) - CAM_OFFSET_HEIGHT * WINDOW_HEIGHT, 0.1);
	}
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

	// MOVIMIENTO DE LA CÁMARA EN FUNCIÓN DE POSICIÓN DE OTT
	moveCamera();
}


void PlayState::ottCollide(const SDL_Rect& Ott, const SDL_Rect& onGround, SDL_Rect& colRect, bool& col, bool& ground) {
	// COMPROBACI�N DE COLISIONES CON OBJETOS DE TIPO SUELO (PROVISIONAL)
	for (auto it : groundObjects) {
		ground = it->collide(onGround, colRect);
		if (ground) break;
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
	ott->setTpPoint(newPos);
}

void PlayState::addEnredadera(const Vector2D& pos) {

	cout << "hola" << endl;
	Enredaderas* e1 = new Enredaderas(Vector2D(pos.getX()+5, pos.getY() - app->getTexture("enredadera", PLAY_STATE)->getH()*1.25), app->getTexture("enredadera", PLAY_STATE), this);
	gameObjects.push_back(e1);
	eObjects.push_back(e1);

}
void PlayState::backToMenu() {
	app->getStateMachine()->changeState(new MainMenuState(app));
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
