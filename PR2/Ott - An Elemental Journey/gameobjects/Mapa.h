#pragma once
#include "GameObject.h"
#include <tmxlite/Map.hpp>
#include <tmxlite/Layer.hpp>
#include <tmxlite/TileLayer.hpp>
#include <tmxlite/LayerGroup.hpp>
#include <tmxlite/ObjectGroup.hpp>
#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>
#include <tmxlite/Types.hpp>
#include <string>
#include <list>
#include<unordered_map>
#include "../SDLApplication.h"
using namespace std;
using namespace tmx;

enum ListaNiveles {
	LEVEL_1, LEVEL_2, LEVEL3
};
enum TypeTexture {
	BACKGROUND, TILESET
};
struct infoTexture {
	string name;
	TypeTexture typeT;
	
};
struct infoMap {

};


class Mapa: public GameObject
{
private:
	SDLApplication* app;
	unordered_map<ListaNiveles, list<infoTexture>> infoLevel;
	unordered_map<ListaNiveles, string> levelPath;
	Map map;
	vector<TileLayer::Tile> vectorTiles;
	vector<Object> vectorObjects;
	ListaNiveles currentLevel;
	Texture* background = nullptr;
	Texture* tileset = nullptr;

	void loadMap(string path);

public:
	Mapa(SDLApplication* app, ListaNiveles l, unordered_map<ListaNiveles, string> lP, unordered_map<ListaNiveles, list<infoTexture>> iL);
	void render()const override;
};

