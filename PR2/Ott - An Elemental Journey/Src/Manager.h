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
#include "../checkML.h"

using namespace std;
using grpId_type = uint8_t;
class Entity;
class SDLApplication;
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
private:
	float gravityValue = 0.2;
	SDLApplication* game;
	std::array<std::vector<Entity*>, ecs::maxGroupId> entsByGroup_;
};
