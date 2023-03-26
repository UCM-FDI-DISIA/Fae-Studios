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

class PlayState;

class MapComponent : public Component {
private:
	//unordered_map<ListaNiveles, list<infoTexture>> infoLevel;
	//unordered_map<ListaNiveles, infoMap> levelPath;
	Map map;
	int mapSize;

	// Se guarda un vector por cada habitaci�n que hay. En este vector se guarda su ID y su posici�n
	// El float indica la escala del mapa
	std::vector<std::pair<float, std::vector<std::pair<int, SDL_Rect>>>> vectorTiles;

	// Se guarda un vector con cada tipo de objetos que tiene el mapa (Colisiones, Objetos Interactuables, Salas, Triggers
	std::vector<std::vector<Object>> vectorObjects;

	std::unordered_map<std::string, std::vector<SDL_Rect>> ground;
	std::unordered_map<std::string, std::vector<std::pair<bool, SDL_Rect>>> destructible;

	std::vector<std::vector<Entity*>> interact;

	// Vector con las keys de la imagen asociada a cada habitacion
	std::vector<std::vector<std::string>> mapKeys;

	// En este mapa se guarda:
	// string -> n�mero de sala
	// vector -> todos los triggers que hay en esa sala
	// pair<string, SDL_Rect> -> 
		// string: la sala a la que lleva ese trigger; 
		// SDL_Rect: su colisi�n
	std::unordered_map<std::string, std::vector<std::pair<std::string, std::pair<SDL_Rect,SDL_Rect>>>> triggers;

	Texture* tilemap = nullptr;
	CameraComponent* cam;
	FadeOutAnimationComponent* anim_;
	Entity* player_;
	Entity* fadeOut;
	PlayState* game;
	
	// std::vector<Texture*> textures;

	const int ROOM_VECTOR_POS = 0;
	const int I_OBJECTS_VECTOR_POS = 1;
	const int COLLISIONS_VECTOR_POS = 2;
	const int TRIGGERS_VECTOR_POS = 3;
	const int ENEMIES_VECTOR_POS = 4;
	
	std::string currentMapKey = "level1_0";

	int realTileSize = 32;
	int usedTileSize = 50;
	int currentRoom = 0;
	int numRooms = 0;
	int currentMap = 0;

	void loadMap(std::string path);
	std::string pickedLifeShards;
	bool loadEarthBoss = true, loadWaterBoss = true, loadFireBoss = true;
	bool loadEarthElem = true, loadWaterElem = true, loadFireElem = true;

public:
	constexpr static ecs::cmpId_type id = ecs::_MAP;
	
	MapComponent(Entity* fadeOut, PlayState* game, int currentMap, std::ifstream & file);
	MapComponent(Entity* fadeOut, PlayState* game, int currentMap);
	void initComponent();
	virtual void render();

	virtual void update();

	// cambio de mapa
	void changeMap();

	void playFadeOutAnimation() { anim_->startFadeOut(); }
	
	inline std::string getCurrentLevel() { return currentMapKey; }

	void generateEnemies();
	inline void changeMap(int map) { currentMap = map; };
	inline int getCurrentMap() { return currentMap; }

	std::vector<std::pair<SDL_Rect, SDL_Rect>> checkCollisions(const SDL_Rect& playerRect);
	
	inline std::vector<std::vector<Entity*>> getInteract() { return interact; };
	inline int getCurrentRoom() { return currentRoom; }
	inline void setCurrentRoom(int newRoom) { currentRoom = newRoom; }
	inline float getCurrentRoomScale() { return vectorTiles[currentRoom].first; }
	inline std::string getMapKey(int map, int i) { if (i < mapKeys[currentMap].size()) return mapKeys[map][i]; else return " "; }

	inline void destroyTile(std::string room, int index) { destructible[room][index].first = false; }

	void changeRoom(std::string newRoom, Vector2D newPos, bool verticalTrigger = false);

	std::vector<std::vector<Object>> getObjects() { return vectorObjects; }
	inline float tileScale() { return (float)usedTileSize / (float)realTileSize; }

	// L�mites de la c�mara en X sala
	inline SDL_Rect getCamBounds() { 
		SDL_Rect rect = getSDLRect(vectorObjects[ROOM_VECTOR_POS][currentRoom].getAABB());
		auto scale = vectorTiles[currentRoom].first;
		rect.x *= scale;
		rect.y *= scale;
		rect.w *= scale;
		rect.h *= scale;
		return rect;
	}

	// recibe un FloatRecy se convierte a SDL_Rect, multiplic�ndolo tambi�n por la escala de las Tiles
	inline SDL_Rect getSDLRect(FloatRect rect) {
		SDL_Rect sdlRect = { (int)(rect.left * tileScale()), (int)(rect.top * tileScale()),
                             (int)(rect.width * tileScale()), (int)(rect.height * tileScale()) };
		return sdlRect;
	}

	virtual void saveToFile(std::ofstream& file);
	virtual void loadFromFile(std::ifstream& file);
};

