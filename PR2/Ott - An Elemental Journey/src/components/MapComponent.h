#pragma once
#include "Component.h"
#include "../dependencies/Texture.h"
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

using namespace std;
using namespace tmx;

enum ListaNiveles {
	LEVEL1 = 0,
	LEVEL2 = 1,
	LEVEL3 = 2,
	DEMO = 3
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
class SDLApplication;
class MapComponent : public Component
{
private:
	SDLApplication* app;
	unordered_map<ListaNiveles, list<infoTexture>> infoLevel;
	unordered_map<ListaNiveles, infoMap> levelPath;
	Map map;
	int mapSize;
	vector<TileLayer::Tile> vectorTiles;
	vector<vector<Object>> vectorObjects;
	ListaNiveles currentLevel;
	Texture* tilemap = nullptr;
	//std::vector<Texture*> textures;

	int realTileSize = 32;
	int usedTileSize = 50;

	void loadMap(string path);
	void initializeSources();

public:
	MapComponent(SDLApplication* app, ListaNiveles l);
	virtual void render();
	void changeMap();
	vector<vector<Object>> getObjects() { return vectorObjects; }
	inline float tileScale() { return (float)usedTileSize / (float)realTileSize; }
	constexpr static cmpId_type id = ecs::_MAP;
};

