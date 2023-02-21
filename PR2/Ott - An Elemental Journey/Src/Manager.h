#pragma once
#include <vector>
#include <array>
#include "../dependencies/Vector2D.h"
#include "../componentes/Transform.h"
#include "../componentes/Image.h"
#include "../componentes/FramedImage.h"

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
	const vector<Entity*>& getEntitiesByGroup(grpId_type gId);
	void addToGroupList(grpId_type gId, Entity* e);
private:
	SDLApplication* game;
	std::array<std::vector<Entity*>, ecs::maxGroupId> entsByGroup_;
};
