#pragma once
#include "Manager.h"
#include "Entity.h"
#include "../Src/anims.h"
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
	case 6: return game->getTexture("earthShield", PLAY_STATE);
	case 7: return game->getTexture("waterShield", PLAY_STATE);
	case 8: return game->getTexture("fireShield", PLAY_STATE);
		//case 4: return game->getTexture("ott_light", PLAY_STATE);
	default:
		break;
	}
}

void Manager::Teleport(Manager* m)
{
	int cAnim = m->player->getComponent<PlayerAnimationComponent>()->getState();
	if (cAnim != IDLE && cAnim != RUN) return;
	Entity* aux = *m->interactionIt;
	if (aux->getComponent<LampComponent>()->getConnectedLamp() != nullptr) {
		Entity* tpLamp = aux->getComponent<LampComponent>()->getConnectedLamp();
		Vector2D newPos = tpLamp->getComponent<Transform>()->getPos();
		m->player->getComponent<PlayerAnimationComponent>()->startTP(newPos);
	}
	// m->player->getComponent<Transform>()->setPos(newPos);
}

void Manager::Save(Manager* m)
{
	m->player->getComponent<Health>()->saveSactuary();
}
void Manager::checkInteraction()
{
	bool interact = false;
	interactionIt = entsByGroup_[ecs::_grp_INTERACTION].begin();
	while (!interact && interactionIt != entsByGroup_[ecs::_grp_INTERACTION].end()) {
		Entity* ents = *interactionIt;
		SDL_Rect r1 = player->getComponent<Transform>()->getRect();
		SDL_Rect r2 = ents->getComponent<Transform>()->getRect();
		if (SDL_HasIntersection(&r1, &r2)) {
			ents->getComponent<InteractionComponent>()->interact();
			interact = true;
		}
		interactionIt++;
	}
}
pair<bool,bool> Manager::checkCollisionWithVine() {
	bool interact = false;
	bool canGoUp = false;
	interactionIt = entsByGroup_[ecs::_grp_VINE].begin();
	while (!interact && interactionIt != entsByGroup_[ecs::_grp_VINE].end()) {
		Entity* ents = *interactionIt;
		if (ents->hasComponent<ColliderVine>()) {
			SDL_Rect r1;
			SDL_Rect tr_ = player->getComponent<Transform>()->getRect();
			r1.x= tr_.x + tr_.w / 3;
			r1.y= tr_.y + tr_.h - 30;
			r1.w= tr_.w/3;
			r1.h= 1;
			SDL_Rect r2 = ents->getComponent<ColliderVine>()->getRect();
			
			if (SDL_HasIntersection(&r1, &r2)) {
				if (tr_.y + tr_.h*0.6 <= r2.y) {
					canGoUp = false;
					// no dejar que se mueva hacia arriba
				}
				else canGoUp = true;
				interact = true;
			}
		}
		interactionIt++;
	}
	return make_pair(interact,canGoUp);
}
void Manager::createPlayer()
{
	player = addEntity(ecs::_grp_CHARACTERS);
	setHandler(ecs::PLAYER, player);
	player->addComponent<Transform>(500, 2000, 100, 120);
	player->addComponent<PhysicsComponent>();
	SDL_Rect rect = { 20,20,50,50 };
	player->addComponent<HealthImage>(game->getTexture("hearts", PLAY_STATE), 5, rect);
	player->addComponent<Health>(5, ecs::Light);
	player->addComponent<PlayerInput>();
	camera = addEntity(ecs::_grp_GENERAL);
	setHandler(ecs::CAMERA, camera);
	camera->addComponent<Transform>(200, 700, 100, 120);
	camera->addComponent<CameraComponent>();
	player->addComponent<FramedImageOtt>();
	auto pAnim = player->addComponent<PlayerAnimationComponent>(anims::OTT_ANIM);
	auto health = player->addComponent<Health>(5, ecs::Light);
	player->addComponent<PlayerAttack>(game);
	player->addComponent<PlayerInput>();
	pAnim->initComponent();
	health->initComponent();
}

void Manager::createLamp(Vector2D position, string name,  int width, int height)
{
	Entity* lamp1 = addEntity(ecs::_grp_INTERACTION);
	lamp1->addComponent<Transform>(position, 50, 130);
	lamp1->addComponent<Image>(game->getTexture("lamp", PLAY_STATE));
	lamp1->addComponent<LampComponent>(name);
	lamp1->addComponent<InteractionComponent>(Teleport);
	bool interact = false;
	interactionIt = entsByGroup_[ecs::_grp_INTERACTION].begin();
	while (!interact && interactionIt != entsByGroup_[ecs::_grp_INTERACTION].end()) {
		Entity* lamp2 = *interactionIt;
		if (lamp2 != lamp1) {
			if (lamp2->getComponent<LampComponent>() != nullptr) {
				if (lamp2->getComponent<LampComponent>()->GetName() == name) {
					lamp2->getComponent<LampComponent>()->setConnectedLamp(lamp1);
					lamp1->getComponent<LampComponent>()->setConnectedLamp(lamp2);
					interact = true;
				
				}
			}
		}
		interactionIt++;
	}
}

void Manager::AddEnredadera(Manager* m) {

	Entity* aux = (*m->interactionIt);
	aux->getComponent<VineManager>()->addVine();
};
void Manager::createSanctuary(Vector2D position, int width, int height)
{
	Entity* sanc = addEntity(ecs::_grp_INTERACTION);
	sanc->addComponent<Transform>(position.getX(), position.getY(), width, height);
	sanc->addComponent<Image>(game->getTexture("sanctuary", PLAY_STATE));
	sanc->addComponent<InteractionComponent>(Save);
}

void Manager::createGrass(Vector2D position, int widthVine, int heightVine, Vector2D posiniVine, Vector2D posfinVine, int width, int height) {
	Entity* grass = addEntity(ecs::_grp_INTERACTION);
	grass->addComponent<Transform>(position, width, height);
	grass->addComponent<Image>(game->getTexture("grass", PLAY_STATE));
	grass->addComponent<VineManager>(game->getTexture("enredadera", PLAY_STATE), posiniVine, posfinVine, -1, 0, widthVine, heightVine,2);
	grass->getComponent<VineManager>()->createVine();
	grass->addComponent<InteractionComponent>(AddEnredadera);

}

void Manager::createMap()
{
	Entity* bgrd = addEntity(ecs::_grp_BACKGROUND);
	Entity* e = addEntity(ecs::_grp_MAP);
	e->addComponent<MapComponent>(game, LEVEL1);
	auto scale = e->getComponent<MapComponent>()->tileScale();
	bgrd->addComponent<BackgroundImage>(Vector2D(0, 0), game->getTexture("level1bg", PLAY_STATE), scale, scale);
	//bgrd->addComponent<BackgroundImage>(Vector2D(0, 0), game->getTexture("level1bg", PLAY_STATE), scale, scale);
	//createGrass(Vector2D(200, 1450));

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
				e->addComponent<Transform>(Vector2D(x_ * scale, y_ * scale), game->getTexture("pixel", PLAY_STATE), Vector2D(w_ * scale, h_ * scale));
				e->addComponent<Image>(game->getTexture("pixel", PLAY_STATE));
			}
			else if (ot.getClass() == "Grass") {
				createGrass(Vector2D(x_ * scale, (y_ * scale - game->getTexture("grass", PLAY_STATE)->getH()) + h_*scale), w_*scale, h_*scale, Vector2D(x_ * scale, (y_ * scale - game->getTexture("grass", PLAY_STATE)->getH()) + h_ * scale + 100), Vector2D(x_ * scale, (y_ * scale - game->getTexture("grass", PLAY_STATE)->getH())));
			}
			else if (ot.getClass() == "Lamp") {
				createLamp(Vector2D(x_ * scale, y_ * scale - game->getTexture("lamp", PLAY_STATE)->getH() * 2), ot.getName());
			}
			else if (ot.getClass() == "Sanctuary") {
				createSanctuary(Vector2D(x_ * scale - game->getTexture("sanctuary", PLAY_STATE)->getW() * 1.5, y_ * scale - game->getTexture("sanctuary", PLAY_STATE)->getH() * 3.5));
			}
			else if (ot.getClass() == "DoorTrigger") {
				Entity* trigger = addEntity(ecs::_grp_TRIGGER);
				trigger->addComponent<Transform>(Vector2D(x_ * scale, y_ * scale), w_ * scale,h_ * scale);
				trigger->addComponent<VineManager>(game->getTexture("vine", PLAY_STATE), Vector2D((x_ * scale) - 260, ((y_ * scale) + h_ * scale) - 100), Vector2D((x_ * scale) - 170, y_ * scale - 100), -1, 0, w_ * scale, h_ * scale, 3);
				trigger->getComponent<VineManager>()->createVine();
				trigger->addComponent<EnterBossRoom>(game->getTexture("animationWorm", PLAY_STATE));
				trigger->addComponent<Trigger>();
			}
			else if (ot.getClass() == "Ott") {
			}
			else if (ot.getClass() == "EarthBoss") {
				cout << "X: " << x_ * scale << " Y: " << y_ * scale << endl;
				cout << w_ * scale << " " << h_*scale << endl;
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
void Manager::addBossEarth() {
	if (!added) {
		auto enemy4 = addEntity(ecs::_grp_CHARACTERS);
		enemy4->addComponent<Transform>(Vector2D(7319, 1230), 1069, 1144);
		auto ph4 = enemy4->addComponent<PhysicsComponent>();
		enemy4->addComponent<FramedImageEnemy>(game->getTexture("animationWorm", PLAY_STATE), anims::EARTH_ANIM);
		enemy4->addComponent<Health>(5, ecs::Earth, false);
		enemy4->addComponent<EarthBossAnimationController>(anims::EARTH_ANIM);
		ph4->setVelocity({ 1,0 });
		ph4->lookDirection(true);
		added = true;

	}
}