#pragma once
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

using namespace std;
using namespace tmx;
class EarthKMap
{
public:
	Map map;
	vector<TileLayer::Tile> vectorTiles;
	vector<Object> vectorObjects;

	void loadMap(string p);
};

