#include "Manager.h"
#include "Entity.h"
#include "../SDLApplication.h"
Manager::Manager(SDLApplication* g) : entsByGroup_(), game(g)
{
    
    for (auto& groupEntities : entsByGroup_) {
        groupEntities.reserve(100);
    }
}

Entity* Manager::addEntity(ecs::grpId_type gId = ecs::_grp_GENERAL)
{
    Entity* e = new Entity();
    e->setAlive(true);
    e->setContext(this);
    entsByGroup_[gId].push_back(e);
    return e;
}

void Manager::refresh()
{
    for (ecs::grpId_type gId = 0; gId < ecs::maxGroupId; gId++) {
        auto& grpEnts = entsByGroup_[gId];
        grpEnts.erase(
            std::remove_if(grpEnts.begin(), grpEnts.end(), [](Entity* e) {
                    if (e->isAlive()) {
                        return false;
                    }
                    else {
                        delete e;
                        return true;
                    }
            }),
            grpEnts.end());
    }
}

void Manager::update()
{
    for (auto& ents : entsByGroup_) {
        auto n = ents.size();
        for (auto i = 0u; i < n; i++)
            ents[i]->update();
    }
}

void Manager::render()
{
    for (auto& ents : entsByGroup_) {
        auto n = ents.size();
        for (auto i = 0u; i < n; i++)
            ents[i]->render();
    }
}
Texture* Manager::getTexture(int elem)
{
	switch (elem)
	{
	case 0: return game->getTexture("ott_luz", PLAY_STATE); 
	case 1: return game->getTexture("ott_tree", PLAY_STATE);
	case 2: return game->getTexture("ott_water", PLAY_STATE);
	case 3: return game->getTexture("ott_fire", PLAY_STATE);
	case 4: return game->getTexture("shield", PLAY_STATE);
	case 5: return game->getTexture("spores", PLAY_STATE);
	//case 4: return game->getTexture("ott_light", PLAY_STATE);
	default:
		break;
	}
}
void Manager::Save(Manager* m)
{
	m->player->getComponent<Health>()->saveSactuary();
}
void Manager::checkInteraction()
{
	interactionIt = entsByGroup_[ecs::_grp_INTERACTION].begin();
	for (interactionIt; interactionIt != entsByGroup_[ecs::_grp_INTERACTION].end(); interactionIt++) {
		Entity* ents = *interactionIt;
		SDL_Rect r1 = player->getComponent<Transform>()->getRect();
		SDL_Rect r2 = ents->getComponent<Transform>()->getRect();
		if (SDL_HasIntersection(&r1, &r2)) ents->getComponent<InteractionComponent>()->interact();
	}
}
void Manager::createPlayer()
{
    player = addEntity(ecs::_grp_CHARACTERS);
	player->addComponent<Transform>(200, 1300, 100, 120);
	player->addComponent<FramedImage>();
	player->addComponent<PhysicsComponent>();
	player->addComponent<PlayerAnimationComponent>();
	player->addComponent<PlayerInput>();
	player->addComponent<Health>(5, ecs::Light);
	camera = addEntity(ecs::_grp_GENERAL);
	camera->addComponent<Transform>(200, 700, 100, 120);
	camera->addComponent<CameraComponent>();
}

void Manager::createLamp()
{
	Entity* lamp = addEntity(ecs::_grp_INTERACTION);
	lamp->addComponent<Transform>(550, 670, 50, 130);
	lamp->addComponent<Image>(game->getTexture("lamp", PLAY_STATE));
	lamp->addComponent<InteractionComponent>(Test);
}

void Manager::createSanctuary()
{
	Entity* sanc = addEntity(ecs::_grp_INTERACTION);
	sanc->addComponent<Transform>(700, 600, 230, 200);
	sanc->addComponent<Image>(game->getTexture("sanctuary", PLAY_STATE));
	sanc->addComponent<InteractionComponent>(Save);
}

void Manager::createMap()
{
	Entity* bgrd = addEntity(ecs::_grp_MAP);
	Entity* e = addEntity(ecs::_grp_MAP);
	e->addComponent<MapComponent>(game,LEVEL1);
	auto scale = e->getComponent<MapComponent>()->tileScale();
	bgrd->addComponent<BackgroundImage>(Vector2D(0, 0), game->getTexture("level1bg", PLAY_STATE), scale, scale);
	createLamp();
	createSanctuary();
	auto a = e->getComponent<MapComponent>()->getObjects();
	for (auto it : a) {
		//unordered_map<string, TP_Lamp*> lamps;
		for (auto ot : it) {
			float x_ = ot.getAABB().left;
			float y_ = ot.getAABB().top;
			float w_ = ot.getAABB().width;
			float h_ = ot.getAABB().height;
			elementsInfo::elements elem;
			string path = "";
			if (ot.getName() == "1") { elem = elementsInfo::Earth; path = "earth"; }
			if (ot.getName() == "2") { elem = elementsInfo::Water; path = "water"; }
			if (ot.getName() == "3") { elem = elementsInfo::Fire; path = "fire"; }
			if (ot.getName() == "4") { elem = elementsInfo::Dark; path = "dark"; }
			if (ot.getClass() == "Ground") {
				//Ground* grT = new Ground(Vector2D(x_ * scale, y_ * scale), app->getTexture("pixel", PLAY_STATE), Scale(w_ * scale, h_ * scale));
				//gameObjects.push_back(grT);
				Entity* e = addEntity(ecs::_grp_GROUND);
				//int width = game->getTexture("pixel", PLAY_STATE)->getW() / game->getTexture("pixel", PLAY_STATE)->getNumCols() * (w_*scale);
				//int height = game->getTexture("pixel", PLAY_STATE)->getH() / game->getTexture("pixel", PLAY_STATE)->getNumRows() * (h_*scale);
				cout << "Ground detected " << x_*scale << " " << y_*scale << endl;
				e->addComponent<Transform>(Vector2D(x_ * scale, y_ * scale), game->getTexture("pixel", PLAY_STATE), Vector2D(w_ * scale, h_ * scale));
				e->addComponent<Image>(game->getTexture("pixelWhite", PLAY_STATE));
			}
			else if (ot.getClass() == "Grass") {
				//Grass* g1 = new Grass(Vector2D(x_ * scale, y_ * scale - app->getTexture("grass", PLAY_STATE)->getH()), app->getTexture("grass", PLAY_STATE), this);
				//gameObjects.push_back(g1);

			}
			else if (ot.getClass() == "Lamp") {
				/*TP_Lamp* l1 = new TP_Lamp(Vector2D(x_ * scale, y_ * scale - app->getTexture("lamp", PLAY_STATE)->getH() * 2), app->getTexture("lamp", PLAY_STATE), this, Scale(2, 2), LAMP);

				string lampName = ot.getName();
				auto at = lamps.find(lampName);
				if (at != lamps.end()) {
					l1->SetLamp((*at).second);
					(*at).second->SetLamp(l1);
				}
				else {
					lamps.insert({ ot.getName(), l1 });
				}

				gameObjects.push_back(l1);*/
			}
			else if (ot.getClass() == "Sanctuary") {
				//Sanctuary* s1 = new Sanctuary(Vector2D(x_ * scale - app->getTexture("sanctuary", PLAY_STATE)->getW() * 1.5, y_ * scale - app->getTexture("sanctuary", PLAY_STATE)->getH() * 3.5), app->getTexture("sanctuary", PLAY_STATE), Scale(3.5, 3.5));
				//gameObjects.push_back(s1);
			}
			else if (ot.getClass() == "Ott") {

			}
			else if (ot.getClass() == "Mushroom") {

			}
			else if (ot.getClass() == "Melee") {
			}
			else if (ot.getClass() == "Slime") {

			}
		}
	}

	//bgrd->addComponent<Image>(game->getTexture("level1bg", PLAY_STATE));
	/*currentMap = new Mapa(app, LEVEL1);
	auto scale = currentMap->tileScale();
	gameObjects.push_back(new CollisionObject(Vector2D(0, 300), app->getTexture("level1bg", PLAY_STATE), Scale(scale, scale)));
	gameObjects.push_back(currentMap);

	auto a = currentMap->getObjects();
	for (auto it : a) {
		unordered_map<string, TP_Lamp*> lamps;
		for (auto ot : it) {
			float x_ = ot.getAABB().left;
			float y_ = ot.getAABB().top;
			float w_= ot.getAABB().width;
			float h_ = ot.getAABB().height;
			elementsInfo::elements elem;
			string path = "";
			if (ot.getName() == "1") { elem = elementsInfo::Earth; path = "earth"; }
			if (ot.getName() == "2") { elem = elementsInfo::Water; path = "water";}
			if (ot.getName() == "3") { elem = elementsInfo::Fire; path = "fire";}
			if (ot.getName() == "4") { elem = elementsInfo::Dark; path = "dark";}
			if (ot.getClass() == "Ground") {
				Ground* grT = new Ground(Vector2D(x_ * scale, y_ * scale), app->getTexture("pixel", PLAY_STATE), Scale(w_ * scale, h_ * scale));

				gameObjects.push_back(grT);
			}
			else if (ot.getClass() == "Grass") {
				Grass* g1 = new Grass(Vector2D(x_ *scale, y_ * scale - app->getTexture("grass", PLAY_STATE)->getH()), app->getTexture("grass", PLAY_STATE), this);
				gameObjects.push_back(g1);

			}
			else if (ot.getClass() == "Lamp") {
				TP_Lamp* l1 = new TP_Lamp(Vector2D(x_ * scale, y_ * scale - app->getTexture("lamp", PLAY_STATE)->getH()*2), app->getTexture("lamp", PLAY_STATE), this, Scale(2, 2), LAMP);

				string lampName = ot.getName();
				auto at = lamps.find(lampName);
				if (at != lamps.end()) {
					l1->SetLamp((*at).second);
					(*at).second->SetLamp(l1);
				}
				else {
					lamps.insert({ ot.getName(), l1 });
				}

				gameObjects.push_back(l1);
			}
			else if (ot.getClass() == "Sanctuary") {
				Sanctuary* s1 = new Sanctuary(Vector2D(x_ * scale - app->getTexture("sanctuary", PLAY_STATE)->getW() * 1.5, y_ * scale - app->getTexture("sanctuary", PLAY_STATE)->getH() * 3.5), app->getTexture("sanctuary", PLAY_STATE), Scale(3.5, 3.5));
				gameObjects.push_back(s1);
			}
			else if (ot.getClass() == "Ott") {

			}
			else if (ot.getClass() == "Mushroom") {

			}
			else if (ot.getClass() == "Melee") {
			}
			else if (ot.getClass() == "Slime") {

			}
		}
	}

	//healthBar = new HealthBar(Vector2D(30, 100), app->getTexture("hearts", PLAY_STATE), Scale(10.0f, 10.0f));
	//gameObjects.push_back(healthBar);
	//ChargedAttackBar* bar = new ChargedAttackBar(healthBar->lastHeartPosition() + Vector2D(100, -10), app->getTexture("chargebar", getStateID()), Scale(1.5f, 1.5f));
	//screenDarkener = new ScreenDarkener(app);
	//gameObjects.push_back(screenDarkener);
	camera = { 0,0,WINDOW_WIDTH, WINDOW_HEIGHT };
	*/
}


const vector<Entity*>& Manager::getEntitiesByGroup(grpId_type gId = ecs::_grp_GENERAL)
{
    return entsByGroup_[gId];
}

void Manager::addToGroupList(grpId_type gId, Entity* e)
{
    entsByGroup_[gId].push_back(e);
}

int Manager::getLvlW()
{
	return LEVEL_WIDTH;
}

int Manager::getLvlH()
{
	return LEVEL_HEIGHT;
}

int Manager::getCamDZ()
{
	return CAM_DEAD_ZONE;
}

float Manager::getCamOH()
{
	return CAM_OFFSET_HEIGHT;
}

int Manager::getWinW()
{
	return game->getWindowRect().w;
}

int Manager::getWinH()
{
	return game->getWindowRect().h;
}



Manager::~Manager()
{
    for (auto& ents : entsByGroup_) {
        for (auto e : ents)
            delete e;
    }
}
