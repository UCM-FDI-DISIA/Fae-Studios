#pragma once
#include <vector>
#include <array>
#include "../dependencies/Vector2D.h"
#include "../componentes/Transform.h"
#include "../componentes/Image.h"
#include "../componentes/FramedImage.h"
//#include "../SDLApplication.h"
#include "../checkML.h"
using namespace std;
using grpId_type = uint8_t;
class Entity;
class Manager
{

public:
	Manager();
	virtual ~Manager();
	Entity* addEntity(grpId_type gId);
	void refresh();
	void update();
	void render();
	void createPlayer();
	const vector<Entity*>& getEntitiesByGroup(grpId_type gId);
	void addToGroupList(grpId_type gId, Entity* e);
private:
	//SDLApplication* game;
	enum ValoresArray { GrayAsteroid, GoldAsteroid, Fighter1, Fire, Heart };
	std::array<std::vector<Entity*>, ecs::maxGroupId> entsByGroup_;
};
