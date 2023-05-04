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
#include <unordered_map>
#include "CameraComponent.h"
#include "FadeOutAnimationComponent.h"
#include "../components/ActiveWater.h"
#include "../components/BossDoor.h"

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

	std::vector<std::list<Entity*>> interact;
	struct sanctuaries_info {
		Entity* sanct;
		std::string mapKey;
	};
	std::vector<sanctuaries_info> sanctuaries;

	// Vector con las keys de la imagen asociada a cada habitacion
	std::vector<std::vector<std::string>> mapKeys;

	std::vector<Entity*> eraseEntities;
	std::vector<Entity*> backgrounds;
	//agua
	std::vector<std::vector<Entity*>> waterObjects;
	std::vector<std::vector<Entity*>> platforms;

	// Pos burbujas sala boss final
	std::vector< SDL_Rect> bubblesPos;

	// Pos agujeros negros sala boss final
	std::vector< SDL_Rect> blackHolesPos;

	// Pos enredaderas sala boss final
	std::vector< SDL_Rect> bossSpikePos;

	// Pos colliders (pts debiles) sala boss final
	std::vector< SDL_Rect> bossWeakSpotsPos;

	// En este mapa se guarda:
	// string -> n�mero de sala
	// vector -> todos los triggers que hay en esa sala
	// pair<string, SDL_Rect> -> 
		// string: la sala a la que lleva ese trigger; 
		// SDL_Rect: su colisi�n
	std::unordered_map<std::string, std::vector<std::pair<std::string, std::pair<SDL_Rect, SDL_Rect>>>> triggers;


	struct positionsInfo {
		SDL_Rect rect;
		int room;
	};
	// Posiciones de cambio de mapa
	std::unordered_map<int, positionsInfo> positions;


	struct changeMapTriggerInfo {
		int map;
		std::string key;
		int nextPos;
		SDL_Rect triggerRect;
	};
	// sala, vector de key de nuevo mapa y rectangulo del trigger
	std::unordered_map<int, std::vector<changeMapTriggerInfo>> changeMapTriggers;


	Texture* tilemap = nullptr;
	CameraComponent* cam;
	FadeOutMapComponent* anim_;
	Entity* player_;
	Entity* earthBoss;
	Entity* fadeOut;
	PlayState* game;

	// std::vector<Texture*> textures;

	const int ROOM_VECTOR_POS = 0;
	const int I_OBJECTS_VECTOR_POS = 1;
	const int COLLISIONS_VECTOR_POS = 2;
	const int TRIGGERS_VECTOR_POS = 3;
	const int ENEMIES_VECTOR_POS = 4;
	const int CHANGE_MAP_VECTOR_POS = 5;
	const int POSITIONS_VECTOR_POS = 6;
	const int WATER_VECTOR_POS = 7;
	const int BACKGROUNDS_VECTOR_POS = 8;
	const int CARTELES_VECTOR_POS = 9;
	const int PLATFORMS_VECTOR_POS = 10;
	const int BLACKHOLE_VECTOR_POS = 11;
	const int BUBBLE_VECTOR_POS = 12;
	const int FINALBOSS_VECTOR_POS = 13;
	const int SPIKE_VECTOR_POS = 14;
	const int WEAK_SPOT_VECTOR_POS = 15;

	const int maxRooms = 20;

	std::string currentMapKey = "earthMap";

	int realTileSize = 32;
	int usedTileSize = 50;
	int currentRoom = 0;
	int numRooms = 0;
	int currentMap = 0;

	void initSanctuaries();
	void loadMap(std::string path, int nextPos = -1);
	std::string pickedLifeShards = "";
	bool loadEarthBoss = true, loadWaterBoss = true, loadFireBoss = true;
	bool loadEarthElem = true, loadWaterElem = true, loadFireElem = true;
	bool generateDarkEnemies = false;

public:
	constexpr static ecs::cmpId_type id = ecs::_MAP;

	MapComponent(Entity* fadeOut, PlayState* game, int currentMap, std::ifstream& file);
	MapComponent(Entity* fadeOut, PlayState* game, int currentMap);
	void initComponent();
	virtual void render();

	virtual void update();

	void activateObjectsInRoom(int room, bool activate = true);
	// cambio de mapa
	void changeMap(int newMap, std::string key, int nextPos = -1);
	void WaterSetActive(bool c);

	void setPlayerInRoom(Vector2D newPlayerPos, int newRoom);

	void addCollision(std::string sala, SDL_Rect newCol);

	void deleteCollision(std::string sala);

	void playFadeOutAnimation() { anim_->startFadeOut(); }

	inline std::string getCurrentLevel() { return currentMapKey; }

	void generateEnemies();
	inline void changeMap(int map) { currentMap = map; };
	inline int getCurrentMap() { return currentMap; }
	inline void changeVisualMap(int map) { currentMap = map; };

	inline sanctuaries_info getSanctuary(int ID) { return sanctuaries[ID]; }

	std::vector<std::pair<SDL_Rect, SDL_Rect>> checkCollisions(const SDL_Rect& playerRect);
	
	inline std::vector<std::list<Entity*>> getInteract() { return interact; };
	inline std::vector<std::vector<Entity*>> getWater() { return waterObjects; };
	inline int getCurrentRoom() { return currentRoom; }
	inline void setCurrentRoom(int newRoom) {
		bool null = backgrounds[currentRoom] == NULL;
		if (!null) {
			backgrounds[currentRoom]->setActive(false); 
		}
		currentRoom = newRoom; 
		if (!null) {
			backgrounds[currentRoom]->setActive(true); }
		}
	inline float getCurrentRoomScale() { return vectorTiles[currentRoom].first; }
	inline std::string getMapKey(int map, int i) { if (i < mapKeys[map].size()) return mapKeys[map][i]; else return " "; }

	inline void destroyTile(std::string room, int index) { destructible[room][index].first = false; }

	inline int bubblesNum() { return bubblesPos.size(); }
	inline int blackHolesNum() { return blackHolesPos.size(); }
	inline int bossSpikesNum() { return bossSpikePos.size(); }
	inline int bossWeakSpotsNum() { return bossWeakSpotsPos.size(); }

	inline SDL_Rect getBubblePos(int index){ return bubblesPos[index]; }
	inline SDL_Rect getBlackHolePos(int index) { return blackHolesPos[index]; }
	inline SDL_Rect getBossSpikesPos(int index) { return bossSpikePos[index]; }
	inline SDL_Rect getBossWeakSpotsPos(int index){ return bossWeakSpotsPos[index]; }

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
	inline void addShard(int id) { pickedLifeShards += std::to_string(id) + " "; };
	inline void unlockElement(ecs::elements e) {
		if (e == ecs::Fire) loadFireElem = false;
		else if (e == ecs::Water) loadWaterElem = false;
		else if (e == ecs::Earth) loadEarthElem = false;
	};
	virtual void loadFromFile(std::ifstream& file);

	void setBossCompleted(ecs::elements e) {
		switch (e) {
			case ecs::Earth:
				loadEarthBoss = false;
				mngr_->getBossDoor()->getComponent<BossDoor>()->unlockElem(ecs::Earth);
				break;
			case ecs::Water:
				loadWaterBoss = false;
				mngr_->getBossDoor()->getComponent<BossDoor>()->unlockElem(ecs::Water);
				break;
			case ecs::Fire:
				loadFireBoss = false;
				mngr_->getBossDoor()->getComponent<BossDoor>()->unlockElem(ecs::Fire);
				break;
		}
	}
};

