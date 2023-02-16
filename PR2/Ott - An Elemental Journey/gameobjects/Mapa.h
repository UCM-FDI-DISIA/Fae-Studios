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
#include <vector>
#include<unordered_map>
#include "../SDLApplication.h"
using namespace std;
using namespace tmx;

enum ListaNiveles {
	LEVEL1 = 0,
    LEVEL2 = 1,
    LEVEL3 = 2
};
enum TypeTexture {
	BACKGROUND = 0,
    TILESET = 1,


    NUMBER_OF_TYPES
};
struct infoTexture {
	string name;
	TypeTexture typeT;
    infoTexture(string name, TypeTexture t) : name(name), typeT(t) {}
	
};
struct infoMap {
    string route;
    int size;
    infoMap(string route, int size) : route(route), size(size) {}
};


class Mapa: public GameObject {
private:
	SDLApplication* app;
	unordered_map<ListaNiveles, list<infoTexture>> infoLevel;
	unordered_map<ListaNiveles, infoMap> levelPath;
	Map map;
    int mapSize;
	vector<TileLayer::Tile> vectorTiles;
	vector<Object> vectorObjects;
	ListaNiveles currentLevel;
	Texture* tilemap = nullptr;
    //std::vector<Texture*> textures;

	void loadMap(string path);
	void initializeSources();

public:
	Mapa(SDLApplication* app, ListaNiveles l);
	virtual void render(const SDL_Rect& Camera = {0,0,0,0}) const;
	void changeMap();
	vector<Object> getObjects() { return vectorObjects; }
};

