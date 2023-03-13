#pragma once
#include "../ecs/Component.h"
#include "../sdlutils/Texture.h"
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
#include "CameraComponent.h"

using namespace tmx;


class MapComponent : public Component {
private:
	//unordered_map<ListaNiveles, list<infoTexture>> infoLevel;
	//unordered_map<ListaNiveles, infoMap> levelPath;
	Map map;
	int mapSize;
	std::vector<std::vector<std::pair<int, SDL_Rect>>> vectorTiles;
	std::vector<std::vector<Object>> vectorObjects;
	Texture* tilemap = nullptr;
	CameraComponent* cam;
	
	//std::vector<Texture*> textures;

	int realTileSize = 32;
	int usedTileSize = 50;

	void loadMap(std::string path);

public:
	constexpr static ecs::cmpId_type id = ecs::_MAP;
	
	MapComponent();
	void initComponent();
	virtual void render();
	void changeMap();
	std::vector<std::vector<Object>> getObjects() { return vectorObjects; }
	inline float tileScale() { return (float)usedTileSize / (float)realTileSize; }
};

