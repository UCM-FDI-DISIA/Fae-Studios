
#pragma once
#include <vector>
#include <array>
#include <string>
#include "../componentes/AddVine.h"
#include "../dependencies/Vector2D.h"
#include "../componentes/Transform.h"
#include "../componentes/Image.h"
#include "../componentes/ImageVine.h"
#include "../componentes/FramedImage.h"
#include "../componentes/MapComponent.h"
#include "../componentes/BackgroundImage.h"
#include "../componentes/PhysicsComponent.h"
#include "../componentes/PlayerInput.h"
#include "../componentes/CameraComponent.h"
#include "../componentes/PlayerAnimationComponent.h"
#include "../componentes/Health.h"
#include "../componentes/InteractionComponent.h"
#include "../componentes/LampComponent.h"
#include "../componentes/ColliderVine.h"
#include "../componentes//GrowVine.h"
#include "../checkML.h"


using namespace std;
using grpId_type = uint8_t;
class Entity;
class SDLApplication;

const uint LEVEL_WIDTH = 8000;
const uint LEVEL_HEIGHT = 8000;
const auto CAM_OFFSET_HEIGHT = 0.6;
const int CAM_DEAD_ZONE = 250;
class Manager
{

public:
	Manager(SDLApplication* g);
	virtual ~Manager();
	Entity* addEntity(grpId_type gId);
	void refresh();
	void update();
	void render();
	void createPlayer();
	void createMap();
	const vector<Entity*>& getEntitiesByGroup(grpId_type gId);
	void addToGroupList(grpId_type gId, Entity* e);
	inline float getGravityValue() { return gravityValue; }
	inline void desactivateGravity() { gravityValue = 0; }
	inline void activateGravity() {
		gravityValue = 0.2;
	}
	inline Entity* getPlayer() { return player; }
	inline Entity* getCamera() { return camera; }
	int getLvlW();
	int getLvlH();
	int getCamDZ();
	float getCamOH();
	int getWinW();
	int getWinH();
	Texture* getTexture(int elem);
	static void Test(Manager* m) { cout << "interaccion" << endl; }
	static void Teleport(Manager* m);
	static void Save(Manager* m);
	static void AddEnredadera(Manager* m);
	void checkInteraction();
	bool checkCollisionWithVine();
	inline Entity* getCurrentInteraction() { return *interactionIt; }
	//void showVine(Vector2D position, int width = 60, int height = 120);
	//void createVine(Vector2D position, int width, int height);
private:
	void createLamp(int x1, int y1, int x2, int y2);
	void createSanctuary(Vector2D position, int width = 100, int height = 130);
	void createGrass(Vector2D position, int widthVine, int heightVine, Vector2D posiniVine, Vector2D posfinVine, int width = 60, int height = 60);
	Entity* player;
	Entity* camera;
	float gravityValue = 0.2;
	SDLApplication* game;
	std::array<std::vector<Entity*>, ecs::maxGroupId> entsByGroup_;
	vector<Entity*>::iterator interactionIt;
};
