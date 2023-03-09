#pragma once
#include "PlayState.h"
#include "../../SDLApplication.h"
#include "../../componentes/EnemyAnimationController.h"
#include "../../componentes/TestEnemyInput.h"

/*
#include "../../gameobjects/Physics/Ground.h"
#include "../../gameobjects/Ott/Ott.h"
#include "../../gameobjects/InteractuableObject.h"
#include "../../gameflow/menus/PauseMenuState.h"
#include "../../gameflow/menus/MainMenuState.h"
#include "../../ui/ChargedAttackBar.h"
#include "../../utils/InputHandler.h"
#include "../../gameobjects/staticEnemy.h"
#include "../../gameobjects/MeleeEnemy.h"
#include "../../gameobjects/SlimeEnemy.h"
#include "../../utils/Elements.h"
#include <unordered_map>
*/
#include "../../componentes/EnemyMovement.h"
#include "../../componentes/EnemyAttack.h"
#include "../../componentes/SlimeStates.h"
#include "../../componentes/EnemyShootingAttack.h"
#include "../../componentes/PlayerInput.h"
#include "../../componentes/Bullet.h"
#include "../../componentes/EnemyMeleeAttack.h"

PlayState::PlayState(SDLApplication* app) : GameState(PLAY_STATE, app) {
	
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
	Mix_Init(MIX_INIT_FLAC | MIX_INIT_MOD | MIX_INIT_MP3 | MIX_INIT_OGG | MIX_INIT_MID);
	Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 2048);
	music = Mix_LoadMUS("../../sounds/musics/Ambient 4.wav");
	Mix_PlayMusic(music, -1);
	manager_ = new Manager(app);
	manager_->createMap();
	manager_->createPlayer();
	auto player = manager_->getPlayer()->getComponent<Transform>()->getPos();
	auto enemy = manager_->addEntity(ecs::_grp_CHARACTERS);
	enemy->addComponent<Transform>(player.getX(), player.getY(), 100, 100);
	enemy->addComponent<FramedImageEnemy>(app->getTexture("mushroom", PLAY_STATE));
	//enemy->addComponent<EnemyMovement>();
	enemy->addComponent<Health>(5, ecs::Fire);
	auto ph = enemy->addComponent<PhysicsComponent>();
	ph->setVelocity({ 0,0 });
	ph->lookDirection(true);

	enemy->addComponent<EnemyMovement>();
	enemy->addComponent<EnemyAttack>(1000, 1000, 3000, 1000, 100, 100);
	enemy->addComponent<SlimeStates>();
	enemy->addComponent<EnemyMeleeAttack>();
	
	enemy->addComponent<EnemyAnimationComponent>(anims::RANGE_ANIM);
	enemy->addComponent<TestEnemyInput>();
	/*auto ph = player->addComponent<PhysicsComponent>();
	ph->setVelocity({ 1,0 });
	ph->lookDirection(true);*/

}

void PlayState::checkCollisions()
{
	/*vector<Entity*> characters = manager_->getEntitiesByGroup(ecs::_grp_CHARACTERS);
	vector<Entity*> ground = manager_->getEntitiesByGroup(ecs::_grp_GROUND);
	for (Entity* e : characters) {
		for (Entity* g : ground) {
			SDL_Rect r1 = e->getComponent<Transform>()->getRect();
			SDL_Rect r2 = g->getComponent<Transform>()->getRect();
			if (SDL_HasIntersection(&r1, &r2)) {
				e->getComponent<PhysicsComponent>()->collideGround();
			}
		}
	}*/
	vector<Entity*> characters = manager_->getEntitiesByGroup(ecs::_grp_CHARACTERS);
	vector<Entity*> ground = manager_->getEntitiesByGroup(ecs::_grp_GROUND);
	vector<Entity*> bullets = manager_->getEntitiesByGroup(ecs::_grp_PROYECTILES);
	for (Entity* e : characters) {
		auto eTr = e->getComponent<Transform>();
		SDL_Rect r1 = eTr->getRect();
		auto physics = e->getComponent<PhysicsComponent>();
		Vector2D& colVector = physics->getVelocity();

		auto mov = e->getComponent<EnemyMovement>();
		for (Entity* g : ground) { // WALL COLLISION

			SDL_Rect r2 = g->getComponent<Transform>()->getRect();
			SDL_Rect areaColision; // area de colision 	
			bool interseccion = SDL_IntersectRect(&r1, &r2, &areaColision);
			if (interseccion && (areaColision.w < areaColision.h) && ((areaColision.x <= r2.x + (r2.w / 2) && physics->getLookDirection()) ||
				(areaColision.x > r2.x + (r2.w / 2) && !physics->getLookDirection()))) {
				colVector = Vector2D(0, colVector.getY());
				if (mov != nullptr) {
					mov->ChangeDirection(false, areaColision);
				}
			}
		}

		int i = 0;
		for (Entity* g : ground) { // GROUND COLLISION
			SDL_Rect r2 = g->getComponent<Transform>()->getRect();
			SDL_Rect areaColision; // area de colision 	
			bool interseccion = SDL_IntersectRect(&r1, &r2, &areaColision);
			if (interseccion)
			{
				if (areaColision.w >= areaColision.h) {
					
					if (!physics->isGrounded() && areaColision.y > r1.y + r1.w / 2) {
						colVector = Vector2D(colVector.getX(), 0);
						physics->setGrounded(true);
					}
					else if (!physics->isGrounded()) {
						colVector = Vector2D(colVector.getX(), 1);
						physics->setVerticalSpeed(1);
					}
					if (mov != nullptr) mov->ChangeDirection(true, areaColision);

					break;
				}
			}
			else if (i == ground.size() - 1) physics->setGrounded(false);
			++i;
		}
	}

	/*for (Entity* b : bullets) {
		Entity* p = manager_->getPlayer();
		SDL_Rect r1 = p->getComponent<Transform>()->getRect();
		SDL_Rect r2 = b->getComponent<Transform>()->getRect();
		if (SDL_HasIntersection(&r1, &r2)) {
			p->getComponent<Health>()->recieveDamage(b->getComponent<Bullet>()->getElem());
			b->setAlive(false);	
		}

		for (Entity* g : ground) { // WALL COLLISION
			SDL_Rect r3 = g->getComponent<Transform>()->getRect();
			if (SDL_HasIntersection(&r2, &r3)) {
				b->setAlive(false);
			}
		}
	}*/
}
void PlayState::update() {
	checkCollisions();
	manager_->update();
	refresh();
}
void PlayState::render() const {
	manager_->render();
}

void PlayState::refresh()
{
	manager_->refresh();
}
PlayState::~PlayState()
{
	Mix_HaltMusic();
	Mix_FreeMusic(music);
	Mix_Quit();
}
/*
PlayState::PlayState(SDLApplication* app) : GameState(PLAY_STATE, app) {
	currentMap = new Mapa(app, LEVEL1);
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
				groundObjects.push_back(grT);
				gameObjects.push_back(grT);
			}
			else if (ot.getClass() == "Grass") {
				Grass* g1 = new Grass(Vector2D(x_ *scale, y_ * scale - app->getTexture("grass", PLAY_STATE)->getH()), app->getTexture("grass", PLAY_STATE), this);
				gameObjects.push_back(g1);
				intObjects.push_back(g1);
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
				intObjects.push_back(l1);
			}
			else if (ot.getClass() == "Sanctuary") {
				Sanctuary* s1 = new Sanctuary(Vector2D(x_ * scale - app->getTexture("sanctuary", PLAY_STATE)->getW() * 1.5, y_ * scale - app->getTexture("sanctuary", PLAY_STATE)->getH() * 3.5), app->getTexture("sanctuary", PLAY_STATE), Scale(3.5, 3.5));
				gameObjects.push_back(s1);
			}
			else if (ot.getClass() == "Ott") {
				ott = new Ott(Vector2D(x_ * scale, y_ * scale - app->getTexture("sanctuary", PLAY_STATE)->getH() * 3), app->getTexture("ott_luz", PLAY_STATE),
					app->getTexture("ott_tree", PLAY_STATE), app->getTexture("ott_water", PLAY_STATE),
					app->getTexture("ott_fire", PLAY_STATE), app->getTexture("shield", PLAY_STATE),
					app->getTexture("fireShield", PLAY_STATE), app->getTexture("waterShield", PLAY_STATE)
					, app->getTexture("earthShield", PLAY_STATE), app->getTexture("whip", PLAY_STATE)
					, this, Scale(3.0f, 3.0f));
				gameObjects.push_back(ott);
				physicObjects.push_back(ott);
			}
			else if (ot.getClass() == "Mushroom") {
				addEntity(new staticEnemy(Vector2D(x_ * scale, y_ * scale - app->getTexture(path + "Mushroom", PLAY_STATE)->getH() * 1.5), app->getTexture(path + "Mushroom", PLAY_STATE), ott, 2000, 5, elem,
					400, 100, Scale(3.0f, 3.0f), this));
			}
			else if (ot.getClass() == "Melee") {
				addEntity(new MeleeEnemy(Vector2D(x_ * scale, y_ * scale - app->getTexture(path + "Bug", PLAY_STATE)->getH() * 1.5), app->getTexture(path + "Bug", PLAY_STATE), 5, elem, ott, true, Vector2D(1, 0), Scale(3, 3), 110, 100, this));
			}
			else if (ot.getClass() == "Slime") {
				// crear enemigo slime
				addEntity(new SlimeEnemy(3, Vector2D(x_ * scale, y_ * scale - app->getTexture("slime", PLAY_STATE)->getH() * 3), app->getTexture("slime", PLAY_STATE),10, elementsInfo::Earth, ott, true, Vector2D(1, 0), Scale(3.0f, 3.0f), 110, 100, this));
			}
		}
	}

	healthBar = new HealthBar(Vector2D(30, 100), app->getTexture("hearts", PLAY_STATE), Scale(10.0f, 10.0f));
	gameObjects.push_back(healthBar);
	//ChargedAttackBar* bar = new ChargedAttackBar(healthBar->lastHeartPosition() + Vector2D(100, -10), app->getTexture("chargebar", getStateID()), Scale(1.5f, 1.5f));
	//screenDarkener = new ScreenDarkener(app);
	//gameObjects.push_back(screenDarkener);
	camera = { 0,0,WINDOW_WIDTH, WINDOW_HEIGHT };

	Mix_Init(MIX_INIT_FLAC | MIX_INIT_MOD | MIX_INIT_MP3 | MIX_INIT_OGG | MIX_INIT_MID);
	Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 2048);
	music = Mix_LoadMUS("../../sounds/musics/Ambient 4.wav");
	Mix_PlayMusic(music, -1);
}
void PlayState::update() {
	GameState::update(); // llamada a todos los updates de la lista de gameObjects

	// ACTIVAR GRAVEDAD PARA TODOS LOS OBJETOS FÍSICOS
	if (!ott->isGrounded()) {
		ott->useGravity();
	}
	/*if (ott->getLife() == 1) screenDarkener->show();
	else screenDarkener->hide();

	// COMPROBACIÓN PARA ACTIVAR OBJETOS INTERACTUABLES
for (auto it : intObjects) {
	SDL_Rect result;
	if (it->collide(ott->getRect(), result)) // SI SE HA DETECTADO INTERACCIÓN CON EL OBJETO, SE ACTIVA
	{
		it->interact(); // ACTIVACIÓN DEL OBJETO

		if (it->getType() == LAMP) { // Si el objeto es de tipo LÁMPARA debe cambiar una animación de Ott
			ott->setAnimState(TP_IN);
		}
	}
}

for (auto it : eObjects) {
	SDL_Rect result;
	if (it->collide(ott->getRect(), result))
	{
		ott->canClimb();
	}
	else {
		ott->cannotClimb();
	}
}

// MOVIMIENTO DE LA CÁMARA EN FUNCIÓN DE POSICIÓN DE OTT
moveCamera();

if (ott->isDead()) {
	app->getStateMachine()->changeState(new MainMenuState(app));
}
}
void PlayState::render() const {
	//Recorremos la lista para renderizar los objetos,
	// y en caso de que se haya borrado un elemento en la lista, dejamos de recorrerla
	for (auto it = gameObjects.begin(); it != gameObjects.end() && !deleted;) {
		(*it)->render(camera);
		if (!deleted) ++it;
		else return;
	}
}
// funci�n para hacer interpolaci�n lineal. Usada en el movimiento de la c�mara
float lerp(float a, float b, float t)
{
	return a + t * (b - a);
}

void PlayState::handleEvents() {
	GameState::handleEvents();
	if (InputHandler::instance()->isKeyJustDown(SDLK_ESCAPE)) {
		app->getStateMachine()->pushState(new PauseMenuState(app));
	}
}
void PlayState::moveCamera() {
	SDL_Rect ottRect = ott->getRect(); // conseguir la posici�n de Ott

	// mover camera.x
	// Comprobamos si la c�mara est� suficientemente cerca del jugador. En caso de que lo est�, la posici�n se settea a la 
	// posici�n del jugador. En caso contrario, se hace una interpolaci�n lineal para acercarse "lentalmente". Esto solo se aprecia cuando
	// la c�mara viaja grandes distancias (entre l�mparas, por ejemplo). 
	camera.x = lerp(camera.x, (int)((ottRect.x + ottRect.w / 2) - WINDOW_WIDTH / 2), 0.02);

	// mover camera.y
	// Setteamos un deadzone donde la c�mara no tiene porqu� moverse (CAM_DEAD_ZONE). En caso de que el personaje salga de esta
	// zona, la c�mara se mueve. Tambi�n se mover� si est� por debajo del m�nimo admitido (CAM_OFFSET_HEIGHT * camera.h)
	// Siempre se calcula la posici�n con interpolaci�n lineal
	if (ottRect.y < camera.y + camera.h - CAM_DEAD_ZONE || ottRect.y > camera.y + CAM_OFFSET_HEIGHT * camera.h) {
		camera.y = lerp(camera.y, (ottRect.y + ottRect.h / 2) - CAM_OFFSET_HEIGHT * WINDOW_HEIGHT, 0.03);
	}

	// Limites de la camara dependiendo del tama�o de la sala (mapa)
	if (camera.x < 0)
	{
		camera.x = 0;
	}
	if (camera.y < 0)
	{
		camera.y = 0;
	}
	if (camera.x > LEVEL_WIDTH - camera.w)
	{
		camera.x = LEVEL_WIDTH - camera.w;
	}
	if (camera.y > LEVEL_HEIGHT - camera.h)
	{
		camera.y = LEVEL_HEIGHT - camera.h;
	}
}

void PlayState::deleteObject(Entity* obj) {
	GameState::deleteObject(obj);
}


void PlayState::ottCollide(const SDL_Rect& ottRect, const SDL_Rect& onGround, SDL_Rect& groundRect, SDL_Rect& colRect, bool& ground, Vector2D& speed) {
	// COMPROBACI�N DE COLISIONES CON OBJETOS DE TIPO SUELO (PROVISIONAL)
	for (auto it : groundObjects) {
		ground = it->collide(onGround, groundRect);
		if (ground) break;
	}

	for (auto it : groundObjects) {
		it->collide(ottRect, colRect);
		if (colRect.h > 0 && colRect.w > 16) { // si el rectángulo merece la pena
			if (speed.getX() > 0 && colRect.x >= ottRect.x + ottRect.w / 2) { // chocar pared por la izquierda
				ott->setPos(Vector2D(ottRect.x - speed.getX(), ottRect.y));
			}
			else if (speed.getX() < 0 && colRect.x <= ottRect.x) { // chocar pared por la derecha
				ott->setPos(Vector2D(ottRect.x - speed.getX(), ottRect.y));
			}

			// chocar techo
			if (speed.getY() < 0 && colRect.y <= ottRect.y && colRect.w >= colRect.h &&
				colRect.w >= ottRect.w / 4) {
				ott->setPos(Vector2D(ott->getRect().x, ott->getRect().y - speed.getY()));
				if (speed.getX() != 0) speed = Vector2D(speed.getX(), 1);
				else speed = Vector2D(0, 0);
			}
		}
	}
}

void PlayState::enemyCollide(const SDL_Rect& enemyRect, const SDL_Rect& onGround, SDL_Rect& groundRect, SDL_Rect& colRect, bool& ground, bool& walled, Vector2D& speed) {
	// COMPROBACI�N DE COLISIONES CON OBJETOS DE TIPO SUELO (PROVISIONAL)
	for (auto it : groundObjects) {
		ground = it->collide(onGround, groundRect);
		if (ground) break;
	}

	for (auto it : groundObjects) {
		walled = it->collide(enemyRect, colRect);
		if (walled) break;
	}
}

bool PlayState::bulletCollide(const SDL_Rect& bulletRect) {
	// COMPROBACI�N DE COLISIONES CON OBJETOS DE TIPO SUELO (PROVISIONAL)
	for (auto it : groundObjects) {
		SDL_Rect result;
		bool ground = it->collide(bulletRect, result);
		if (ground) return ground;
	}
}



SDL_Rect PlayState::ottPos() const {
	return ott->getRect();
}

void PlayState::setOttPos(const Vector2D& newPos) {
	ott->setTpPoint(newPos);
}

void PlayState::addEnredadera(const Vector2D& pos) {

	Enredaderas* e1 = new Enredaderas(Vector2D(pos.getX()+5, pos.getY() - app->getTexture("enredadera", PLAY_STATE)->getH()*1.25), app->getTexture("enredadera", PLAY_STATE), this);
	gameObjects.push_back(e1);
	eObjects.push_back(e1);
}

void PlayState::backToMenu() {
	app->getStateMachine()->changeState(new MainMenuState(app));
}

Vector2D PlayState::checkCollisions()
{
	Vector2D resultVector = ( 0,0 );
	auto a = currentMap->getObjects();
	for (auto it : a) {
		for (auto ot : it) {
			SDL_Rect obstRect;
			obstRect.x = ot.getAABB().left;
			obstRect.y = ot.getAABB().top;
			obstRect.w = ot.getAABB().width;
			obstRect.h = ot.getAABB().height;
			SDL_Rect ottRect = ott->getRect();
			if (SDL_HasIntersection(&ottRect, &obstRect)) {
				resultVector = collides(ott->getRect(), obstRect);
			}
		}
	}
	return resultVector;
}

Vector2D PlayState::collides(SDL_Rect playerRect, SDL_Rect objRect) { //Se comprueba si el bloque colisiona con la bola
	Vector2D cVector (0, 0);
	SDL_Rect areaColision; // area de colision 	
	bool interseccion = SDL_IntersectRect(&playerRect, &objRect, &areaColision);
	if (interseccion)
	{
		if ((areaColision.w < areaColision.h)) { //Colisión lateral
			if (areaColision.x <= objRect.x + (objRect.w / 2)) cVector = ( -1,0 ); //Colisión por la izquierda
			else cVector = ( 1,0 ); //Colisión lado derecho
		}
		else {
			if (areaColision.y < objRect.y + (objRect.h / 2)) cVector = ( 0,-1 ); //Colisión por arriba
			else cVector = ( 0,1 );
		}
	}
	//cout << cVector.getX() << " " << cVector.getY() << endl;
	return cVector;
}


void PlayState::deleteObjects() {
	deleteEntities();
}

void PlayState::deleteEntities() {
	while (!deletedObjects.empty()) {
		GameObject* obj = deletedObjects.top();
		Entity* ent = dynamic_cast<Entity*>(obj);
		if (ent != nullptr) {
			if(ent->hasPhysicsIteraror)
				ent->getState()->getPhysicsObjects()->erase(ent->physicsIterator);
			ent->getState()->gameObjects.erase(ent->it);
			delete obj;
		}
		deletedObjects.pop();
	}
}*/

