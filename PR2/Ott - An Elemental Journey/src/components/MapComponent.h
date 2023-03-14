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
#include "FadeOutAnimationComponent.h"

using namespace tmx;

class MapComponent : public Component {
private:
	//unordered_map<ListaNiveles, list<infoTexture>> infoLevel;
	//unordered_map<ListaNiveles, infoMap> levelPath;
	Map map;
	int mapSize;

	// Se guarda un vector por cada tileset que hay. En estas tiles se guarda su ID y su posición
	std::vector<std::vector<std::pair<int, SDL_Rect>>> vectorTiles;

	// Se guarda un vector con cada tipo de objetos que tiene el mapa (Colisiones, Objetos Interactuables, Salas, Triggers
	std::vector<std::vector<Object>> vectorObjects;

	// En este mapa se guarda:
	// string -> número de sala
	// vector -> todos los triggers que hay en esa sala
	// pair<string, SDL_Rect> -> 
		// string: la sala a la que lleva ese trigger; 
		// SDL_Rect: su colisión
	std::unordered_map<std::string, std::vector<std::pair<std::string, SDL_Rect>>> triggers;

	Texture* tilemap = nullptr;
	CameraComponent* cam;
	FadeOutAnimationComponent* anim_;
	Entity* player_;
	Entity* fadeOut;
	
	// std::vector<Texture*> textures;

	const int ROOM_VECTOR_POS = 0;
	const int I_OBJECTS_VECTOR_POS = 1;
	const int COLLISIONS_VECTOR_POS = 2;
	const int TRIGGERS_VECTOR_POS = 3;

	int realTileSize = 32;
	int usedTileSize = 50;
	int currentRoom = 0;

	void loadMap(std::string path);

public:
	constexpr static ecs::cmpId_type id = ecs::_MAP;
	
	MapComponent(Entity* fadeOut);
	void initComponent();
	virtual void render();

	virtual void update();

	// cambio de mapa
	void changeMap();

	inline void setCurrentRoom(int newRoom) { currentRoom = newRoom; }

	void changeRoom(std::string newRoom, Vector2D newPos);

	std::vector<std::vector<Object>> getObjects() { return vectorObjects; }
	inline float tileScale() { return (float)usedTileSize / (float)realTileSize; }

	// Límites de la cámara en X sala
	inline SDL_Rect getCamBounds() { 
		return getSDLRect(vectorObjects[ROOM_VECTOR_POS][currentRoom].getAABB());
	}

	// recibe un FloatRecy se convierte a SDL_Rect, multiplicándolo también por la escala de las Tiles
	inline SDL_Rect getSDLRect(FloatRect rect) {
		SDL_Rect sdlRect = { rect.left * tileScale(), rect.top * tileScale(),
		rect.width * tileScale(), rect.height * tileScale() };
		return sdlRect;
	}
};

