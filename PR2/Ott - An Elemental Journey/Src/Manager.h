#pragma once
#include <vector>
#include <array>
#include "../dependencies/Vector2D.h"
#include "../componentes/Transform.h"
#include "../componentes/Image.h"
#include "../componentes/FramedImage.h"
#include "../componentes/MapComponent.h"
#include "../componentes/BackgroundImage.h"
#include "../componentes/PhysicsComponent.h"
#include "../componentes/PlayerInput.h"
#include "../componentes/CameraComponent.h"
#include "../componentes/PlayerAnimationComponent.h"
#include "../componentes/Health.h"
#include "../checkML.h"

using namespace std;
using grpId_type = uint8_t;
class Entity;
class SDLApplication;

const uint LEVEL_WIDTH = 8000;
const uint LEVEL_HEIGHT = 8000;
const auto CAM_OFFSET_HEIGHT = 0.73;
const int CAM_DEAD_ZONE = 350;
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
	inline Entity* getPlayer() { return player; }
	inline Entity* getCamera() { return camera; }
	int getLvlW();
	int getLvlH();
	int getCamDZ();
	float getCamOH();
	int getWinW();
	int getWinH();
private:
	Entity* player;
	Entity* camera;
	float gravityValue = 0.2;
	SDLApplication* game;
	std::array<std::vector<Entity*>, ecs::maxGroupId> entsByGroup_;
};
