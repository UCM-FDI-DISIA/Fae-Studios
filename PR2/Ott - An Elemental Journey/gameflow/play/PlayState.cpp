#pragma once
#include "PlayState.h"
#include "../../SDLApplication.h"
#include "../../gameobjects/Physics/Ground.h"
#include "../../gameobjects/Ott/Ott.h"
#include "../menus/MainMenuState.h"


PlayState::PlayState(SDLApplication* app) : GameState(2, app) {
	ott = new Ott(Vector2D(0, 0), app->getTexture("ott_luz", 2), app->getTexture("ott_tree", 3),
		app->getTexture("ott_water", 4),app->getTexture("ott_fire",5), this, Scale(0.3f, 0.3f));

	gr = new Ground(Vector2D(0, 400), app->getTexture("whiteBox", 2), Scale(0.8f, 0.25f));
	Sanctuary* sct = new Sanctuary(Vector2D(200, 280), app->getTexture("whiteBox", 2), Scale(0.05f, 0.1f));
	gameObjects.push_back(sct);
	Sanctuary* sct2 = new Sanctuary(Vector2D(400, 280), app->getTexture("whiteBox", 2), Scale(0.05f, 0.1f));
	gameObjects.push_back(sct2);
	
	gameObjects.push_back(gr);
	gameObjects.push_back(ott);


	groundObjects.push_back(gr);
	physicObjects.push_back(ott);
	camera = { 0,0,WINDOW_WIDTH, WINDOW_HEIGHT };

	Mix_Init(MIX_INIT_FLAC | MIX_INIT_MOD | MIX_INIT_MP3 | MIX_INIT_OGG | MIX_INIT_MID);
	Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 2048);
	music = Mix_LoadMUS("../../sounds/musics/Ambient 4.wav");
	Mix_PlayMusic(music, -1);
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

PlayState::~PlayState()
{
	Mix_HaltMusic();
	Mix_FreeMusic(music);
	Mix_Quit();
}