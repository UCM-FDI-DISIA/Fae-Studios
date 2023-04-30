#include "MapComponent.h"
#include "../sdlutils/SDLUtils.h"
#include "../ecs/Manager.h"
#include "../ecs/Entity.h"
#include "../components/CameraComponent.h"
#include "../components/LoreRoom.h"
#include "../components/Trigger.h"
#include "../states/PlayState.h"
#include "../states/GameStateMachine.h"
#include "../game/Constructors.h"
#include <algorithm>

MapComponent::MapComponent(Entity* fadeOut, PlayState* game, int currentMap) : fadeOut(fadeOut), game(game), currentMap(currentMap) {
    int n = 20;
    vectorObjects.reserve(n);
    vectorTiles.reserve(6);
    for (int i = 0; i < n; ++i) {
        vectorObjects.push_back({});
        vectorTiles.push_back({});
        interact.push_back({});
    }
    mapKeys.reserve(ecs::LAST_MAP_ID);
    for (int i = 0; i < ecs::LAST_MAP_ID; ++i) {
        mapKeys.push_back({});
    }
    currentMapKey = "earthMap";
    tilemap = &sdlutils().images().at(sdlutils().levels().at(currentMapKey).tileset);
}

std::vector<std::string> strSplit(std::string s, char c) {

    std::vector<std::string> split;
    std::string word = "";

    for (int i = 0; i < s.size(); ++i) {
        if (s[i] == c) {
            split.push_back(word);
            word = "";
        }
        else {
            word += s[i];
        }
    }

    split.push_back(word);
    return split;
}

void MapComponent::generateEnemies() {
    auto scale = tileScale();
    game->initEnemies(vectorObjects[ROOM_VECTOR_POS].size());
    for (auto it : vectorObjects[ENEMIES_VECTOR_POS]) {
        float x_ = it.getAABB().left;
        float y_ = it.getAABB().top;
        float w_ = it.getAABB().width;
        float h_ = it.getAABB().height;

        auto split = strSplit(it.getName(), '_');
        bool lookingRight = true;
        if (split[2] == "left") lookingRight = false;
        auto elem = (ecs::elements)std::stoi(split[1]);
        std::string path;
        if (elem == ecs::Earth) {
            path = "earth";
        }
        else if (elem == ecs::Water) {
            path = "water";
        }
        else if (elem == ecs::Fire) {
            path = "fire";
        }
        int roomNum = std::stoi(split[0]);
        float roomScale = vectorTiles[roomNum].first;

        if (it.getClass() == "Mushroom") {
            Entity* enemie = constructors::eRanged(mngr_, path + "Mushroom", x_ * scale * roomScale, y_ * scale * roomScale, roomScale, elem, lookingRight);
            game->addEnemy(enemie, roomNum);
        }
        else if (it.getClass() == "Melee") {
            Entity* enemie = constructors::eMelee(mngr_, path + "Bug", x_ * scale * roomScale, y_ * scale * roomScale, roomScale, elem, lookingRight);
            game->addEnemy(enemie, roomNum);
        }
        else if (it.getClass() == "Slime") {
            Entity* enemie = constructors::eSlime(mngr_, path + "Slime", x_ * scale * roomScale, y_ * scale * roomScale, roomScale, elem, lookingRight, roomNum);
            game->addEnemy(enemie, roomNum);
        }
        else if (it.getClass() == "WaterBoss" && loadWaterBoss) {
            
            auto waterBoss = constructors::WaterBoss(mngr_, ent_, x_ * scale * roomScale, y_ * scale * roomScale, 300 * scale * roomScale, 300 * scale * roomScale);
            eraseEntities.push_back(waterBoss);

            for (auto it : mngr_->getEntities(ecs::_grp_GROUND)) {
                auto dest = it->getComponent<Destruction>();
                if(dest != nullptr) dest->setBoss(waterBoss);
            }
        }
        else if (it.getClass() == "fireBoss" && loadFireBoss)
        {
            auto fBoss= constructors::FireBoss(mngr_, ent_, x_ * scale * roomScale, y_ * scale * roomScale);
            game->addEnemy(fBoss, roomNum);
            mngr_->setFireBoss(fBoss);
        }
    }

    auto enemies_ = game->getEnemies();
    for (auto it : enemies_) {
        for (auto ot : it) {
            ot->setActive(false);
        }
    }

    for (auto it : enemies_[currentRoom]) {
        it->setActive(true);
    }
}

MapComponent::MapComponent(Entity* fadeOut, PlayState* game, int currentMap, std::ifstream& file) : fadeOut(fadeOut), game(game), currentMap(currentMap) {
    int n = 20;
    vectorObjects.reserve(n);
    vectorTiles.reserve(6);
    for (int i = 0; i < n; ++i) {
        vectorObjects.push_back({});
        vectorTiles.push_back({});
        interact.push_back({});
    }
    mapKeys.reserve(ecs::LAST_MAP_ID);
    for (int i = 0; i < ecs::LAST_MAP_ID; ++i) {
        mapKeys.push_back({ "NULL", {0,0,0,0} });
    }
    loadFromFile(file);
    tilemap = &sdlutils().images().at(sdlutils().levels().at(currentMapKey).tileset);
}

void MapComponent::initComponent() {
    cam = mngr_->getCamera()->getComponent<CameraComponent>();
    player_ = mngr_->getPlayer();
    anim_ = fadeOut->getComponent<FadeOutMapComponent>();
    anim_->setMap(ent_);
    initSanctuaries();
    loadMap(sdlutils().levels().at(currentMapKey).route);
}

void MapComponent::initSanctuaries() {
    std::ifstream file;
    std::string route;
#ifdef __WINDOWS__
    file.open("../resources/txt_info/sanctuaryInfo.txt");
#endif
#ifdef __APPLE__
    file.open("../Ott - An Elemental Journey/resources/txt_info/sanctuaryInfo.txt");
#endif

    int n;
    file >> n;
    for (int i = 0; i < n; ++i) {
        std::string mapKey;
        int numSancts;
        file >> mapKey >> numSancts;
        switch (i) {
            case 0: mapKey = "earthMap"; break;
            case 1: mapKey = "waterMap"; break;
            case 2: mapKey = "waterBossMap"; break;
            case 3: mapKey = "fireMap"; break;
        }
        for (int o = 0; o < numSancts; ++o) {
            sanctuaries.push_back({ nullptr, mapKey });
        }
    }
}

void MapComponent::update() {
    if (!anim_->onAnim()) {
        Transform* playerTr_ = player_->getComponent<Transform>();
        SDL_Rect playerRect = playerTr_->getRect();
        for (auto trigger : triggers[std::to_string(currentRoom)]) {
            SDL_Rect result;
            SDL_Rect rect = trigger.second.first;
            if (SDL_IntersectRect(&playerRect, &rect, &result)) {

                Vector2D newPos;
                SDL_Rect newRect = trigger.second.second;
                float oldScale = playerTr_->getScale();
                float newScale = vectorTiles[std::stoi(trigger.first)].first;
                playerRect.w = (playerRect.w / oldScale) * newScale;
                playerRect.h = (playerRect.h / oldScale) * newScale;
                bool verticalTrigger = false;
                if (rect.w > rect.h) { // TRIGGER VERTICAL
                    if (result.y < rect.y) { // por arriba
                        newPos = Vector2D(playerRect.x,
                            newRect.y + newRect.h - playerRect.h);
                    }
                    else { // por abajo
                        newPos = Vector2D(newRect.x,
                            newRect.y - newRect.h - playerRect.h);
                    }
                    verticalTrigger = true;
                }
                else { // TRIGGER HORIZONTAL
                    if (result.x > rect.x + rect.w / 2) { // CHOCAS DESDE LA DERECHA
                        newPos = Vector2D(newRect.x - newRect.w - playerRect.w,
                            newRect.y + newRect.h - playerRect.h);
                    }
                    else { // CHOCAS DESDE LA IZQUIERDA
                        newPos = Vector2D(newRect.x + newRect.w + playerRect.w,
                            newRect.y + newRect.h - playerRect.h);
                    }
                }
                changeRoom(trigger.first, newPos, true);
                break;
            }
        }
        int i = 0;
        for (auto trigger : changeMapTriggers[currentRoom]) {
            SDL_Rect result;
            SDL_Rect rect = trigger.triggerRect;
            if (SDL_IntersectRect(&playerRect, &rect, &result)) {
                anim_->startFadeOut(trigger.map, trigger.key, trigger.nextPos);
                break;
            }
            ++i;
        }
    }
}

void MapComponent::setPlayerInRoom(Vector2D newPlayerPos, int newRoom) {
    cam->setPos(newPlayerPos); // settear la nueva posición de la cámara
    activateObjectsInRoom(currentRoom, false); // desactivar los objetos de la sala actual
    setCurrentRoom(newRoom); // settear la nueva sala
    cam->setBounds(getCamBounds()); // cambiar los bounds de la cámara
    mngr_->getPlayer()->getComponent<Transform>()->setPosition(newPlayerPos); // settear la posición del jugador
    mngr_->getPlayer()->getComponent<Transform>()->setScale(getCurrentRoomScale()); // settear su escala
    mngr_->getPlayer()->getComponent<Health>()->setDead(false); // decirle al jugador que no está muerto
    activateObjectsInRoom(currentRoom, true); // activar los objetos de la nueva sala
}

void MapComponent::WaterSetActive(bool c)
{
    for (auto ent : waterObjects[currentRoom]) {
        ent->setActive(true);
    }
}

void MapComponent::changeRoom(std::string newRoom, Vector2D newPos, bool verticalTrigger) {
    // std::stoi -> String TO Int
    anim_->startFadeOut(newPos, std::stoi(newRoom), verticalTrigger);
    game->setVisited(std::stoi(newRoom));
}

void MapComponent::changeMap(int newMap, std::string key, int nextPos) {
    changeVisualMap(newMap);
    PlayState* ps = static_cast<PlayState*> (GameStateMachine::instance()->getPlayState());
    auto enemies = ps->getEnemies();
    for (int i = 0; i < enemies.size(); ++i) {
        for (auto it : enemies[i]) {
            it->setAlive(false);
        }
    }
    for (auto it : interact) {
        for (auto ot : it) {
            if (!ot->hasComponent<InteractionComponent>()) ot->setAlive(false);
            else if(ot->getComponent<InteractionComponent>()->getType() != SANCTUARY_IT)
                ot->setAlive(false);
        }
    }
    for (auto it : waterObjects) {
        for (auto ot : it) {
            ot->setAlive(false);
        }
    }
    for (auto it : platforms) {
        for (auto ot : it) {
            ot->setAlive(false);
        }
    }
    for (int i = 0; i < eraseEntities.size(); ++i) {
        eraseEntities[i]->setAlive(false);
    }
    for (auto it : mngr_->getEntities(ecs::_grp_TRIGGER)) {
        it->setAlive(false);
    }
    interact.clear();
    eraseEntities.clear();
    mngr_->refresh();
    ps->changeMap(newMap);

    currentMapKey = key;
    ground = {};
    destructible = {};
   
    eraseEntities = {};
    waterObjects = {};
    platforms = {};
    changeMapTriggers = {};
    triggers = {};
    positions = {};

    game->eraseCarteles(numRooms);

    vectorObjects = {};
    vectorTiles = {};
    
    int n = 20;
    vectorObjects.reserve(n);
    vectorTiles.reserve(6);
    for (int i = 0; i < n; ++i) {
        vectorObjects.push_back({});
        vectorTiles.push_back({});
        interact.push_back({});
    }

    tilemap = &sdlutils().images().at(sdlutils().levels().at(currentMapKey).tileset);

    loadMap(sdlutils().levels().at(currentMapKey).route, nextPos);
}

void MapComponent::loadMap(std::string path, int nextPos) {
    if (map.load(path))
    {
        tmx::Object playerPos;
        Entity* playerSanctuary = nullptr;
        int playerSanctuaryID = -1;
        int playerSanctuaryRoom;
        const auto& layers2 = map.getLayers();
        std::unordered_map<std::string, std::pair<Vector2D,int>> lamps;
        std::vector<Entity*> platformEarthBoss;
        //cout << "Map has " << layers2.size() << " layers" << endl;
        for (const auto& layer : layers2)
        {
            #pragma region Objects
            if (layer->getType() == Layer::Type::Object)
            {
                auto name = layer->getName();
                const auto& objects = layer->getLayerAs<ObjectGroup>().getObjects();
                if (name == "Salas") {
                    vectorObjects[ROOM_VECTOR_POS] = objects;
                    std::sort(vectorObjects[ROOM_VECTOR_POS].begin(), vectorObjects[ROOM_VECTOR_POS].end(), 
                        [](tmx::Object a, tmx::Object b) {
                            return std::stoi(a.getName()) < std::stoi(b.getName());
                        });
                    numRooms = objects.size();
                    game->initEnemies(numRooms);
                    for (int i = 0; i < numRooms; ++i) {
                        backgrounds.push_back({});
                    }

                    // INICIALIZAR AGUA, PLATAFORMAS y BACKGROUNDS
                    waterObjects.reserve(numRooms);
                    for (int i = 0; i < numRooms; ++i) {
                        waterObjects.push_back(std::vector<Entity*>());
                        waterObjects[i].reserve(5);
                    }

                    platforms.reserve(numRooms);
                    for (int i = 0; i < numRooms; ++i) {
                        platforms.push_back(std::vector<Entity*>());
                        platforms[i].reserve(5);
                    }

                    if (mapKeys[currentMap].size() != numRooms) {
                        mapKeys[currentMap].reserve(numRooms);
                        for (int i = 0; i < numRooms; ++i) {
                            mapKeys[currentMap].push_back({});
                        }
                        game->initVisitedRooms(numRooms);
                    }
                }
                else if (name == "Objetos interactuables") {
                    vectorObjects[I_OBJECTS_VECTOR_POS] = objects;
                }
                else if (name == "Colisiones") {
                    vectorObjects[COLLISIONS_VECTOR_POS] = objects;
                }
                else if (name == "Triggers") {
                    vectorObjects[TRIGGERS_VECTOR_POS] = objects;
                }
                else if (name == "Enemigos") {
                    vectorObjects[ENEMIES_VECTOR_POS] = objects;
                }
                else if (name == "Ott") {
                    playerPos = objects[0];
                }
                else if (name == "Trigger de cambio de mapa") {
                    vectorObjects[CHANGE_MAP_VECTOR_POS] = objects;
                }
                else if (name == "Posiciones") {
                    vectorObjects[POSITIONS_VECTOR_POS] = objects;
                }
                else if (name == "Agua") {
                    vectorObjects[WATER_VECTOR_POS] = objects;
                }
                else if (name == "Backgrounds") {
                    vectorObjects[BACKGROUNDS_VECTOR_POS] = objects;
                }
                else if (name == "Carteles") {
                    vectorObjects[CARTELES_VECTOR_POS] = objects;
                    game->initCarteles(numRooms);
                }
                else if (name == "Plataformas") {
                    vectorObjects[PLATFORMS_VECTOR_POS] = objects;
                }
            }
            #pragma endregion
        }
        for (const auto& layer : layers2)
        {
            #pragma region Tiles
            if (layer->getType() == tmx::Layer::Type::Tile)
            {
                const auto& tiles = layer->getLayerAs<tmx::TileLayer>().getTiles();
                //Guardamos tiles en un vector
                SDL_Rect camPos = cam->camera;
                int cols = sdlutils().levels().at(currentMapKey).cols;
                int offsetX = camPos.x;
                int offsetY = camPos.y;
                int i = 0;
                for (auto salas : vectorObjects[ROOM_VECTOR_POS]) {
                    int o = 0;
                    mapKeys[currentMap][i] = salas.getName();
                    auto rect = salas.getAABB();
                    SDL_Rect sala = { (int)(rect.left * tileScale()), (int)(rect.top* tileScale()), (int)(rect.width * tileScale()), (int)(rect.height * tileScale()) };
                    for (auto tile : tiles) {
                        SDL_Rect tileRect = { (int)(o % cols) * usedTileSize, ((int)(o / cols) * usedTileSize), usedTileSize, usedTileSize };
                        if (SDL_HasIntersection(&sala, &tileRect)) {
                            vectorTiles[i].first = std::stof(salas.getClass());
                            vectorTiles[i].second.push_back(std::make_pair(tile.ID, tileRect));
                        }
                        o++;
                    }
                    ++i;
                }
                // vectorTiles = tiles;
            }
            #pragma endregion
        }

        // COLISIONES
        for (auto obj : vectorObjects[COLLISIONS_VECTOR_POS]) {
            SDL_Rect rect = getSDLRect(obj.getAABB());

            auto roomScale = vectorTiles[std::stoi(obj.getName())].first;
            rect.x *= roomScale;
            rect.y *= roomScale;
            rect.w *= roomScale;
            rect.h *= roomScale;
            if (obj.getClass() == "Destructible") {
                destructible[obj.getName()].push_back(std::make_pair(true, rect));
                int index = destructible[obj.getName()].size() - 1;
                eraseEntities.push_back(constructors::DestructibleTile(mngr_, rect.x, rect.y, rect.w, rect.h, obj.getName(), index, this));
            }
            else ground[obj.getName()].push_back(rect);
        }

        for (auto obj : vectorObjects[WATER_VECTOR_POS]) {
            SDL_Rect rect = getSDLRect(obj.getAABB());
            auto roomScale = vectorTiles[std::stoi(obj.getName())].first;
            rect.x *= roomScale;
            rect.y *= roomScale;
            rect.w *= roomScale;
            rect.h *= roomScale;
            Entity* waterW = constructors::Water(mngr_, rect.x, rect.y, rect.w, rect.h, obj.getClass());
            std::cout << obj.getUID() << std::endl;
            waterObjects[std::stoi(obj.getName())].push_back(waterW);
            //WaterSetActive(true);

            waterW->setActive(false);
        }

        std::unordered_map<std::string, std::pair<SDL_Rect, std::string>> triggerInfo;
        for (auto trigger : vectorObjects[TRIGGERS_VECTOR_POS]) {

            auto nameSplit = strSplit(trigger.getName(), '_');
            std::string roomNum = nameSplit[0];
            float roomScale = vectorTiles[std::stoi(roomNum)].first;
            SDL_Rect trRect = getSDLRect(trigger.getAABB());
            trRect.x *= roomScale;
            trRect.y *= roomScale;
            trRect.w *= roomScale;
            trRect.h *= roomScale;
            std::string triggerClass = trigger.getClass();
            auto at = triggerInfo.find(triggerClass);

            if (at != triggerInfo.end()) {
                std::string room1 = (*at).second.second;
                std::string room2 = roomNum;
                triggers[room1].push_back(std::make_pair(room2, std::make_pair((*at).second.first, trRect)));
                triggers[room2].push_back(std::make_pair(room1, std::make_pair(trRect, (*at).second.first)));
            }
            else {
                triggerInfo.insert({triggerClass, std::make_pair(trRect, roomNum)});
            }

        }

        for (auto trigger : vectorObjects[CHANGE_MAP_VECTOR_POS]) {
            std::string roomNum = trigger.getName();
            float roomScale = vectorTiles[std::stoi(roomNum)].first;
            SDL_Rect trRect = getSDLRect(trigger.getAABB());
            auto nameSplit = strSplit(trigger.getClass(), '_');
            trRect.x *= roomScale;
            trRect.y *= roomScale;
            trRect.w *= roomScale;
            trRect.h *= roomScale;

            changeMapTriggers[std::stoi(roomNum)].push_back({ std::stoi(nameSplit[1]), nameSplit[0], std::stoi(nameSplit[2]), trRect});
        }

        for (auto trigger : vectorObjects[POSITIONS_VECTOR_POS]) {
            std::string roomNum = trigger.getName();
            float roomScale = vectorTiles[std::stoi(roomNum)].first;
            SDL_Rect trRect = getSDLRect(trigger.getAABB());
            int numPos = std::stoi(trigger.getClass());
            trRect.x *= roomScale;
            trRect.y *= roomScale;
            trRect.w *= roomScale;
            trRect.h *= roomScale;

            positions[numPos] = { trRect, std::stoi(roomNum) };
        }

        for (auto pl : vectorObjects[PLATFORMS_VECTOR_POS]) {
            auto nameSplit = strSplit(pl.getName(), '_');
            std::string roomNum = nameSplit[3];
            SDL_Rect rect = getSDLRect(pl.getAABB());
            float roomScale = vectorTiles[std::stoi(roomNum)].first;
            rect.x *= roomScale;
            rect.y *= roomScale;
            rect.w *= roomScale;
            rect.h *= roomScale;
            Entity* plat = constructors::Platform(mngr_, rect.x, rect.y, rect.w, rect.h, std::stoi(nameSplit[1]) * roomScale, std::stoi(nameSplit[2]) * roomScale, nameSplit[0], roomScale);

            platforms[std::stoi(nameSplit[3])].push_back(plat);

            //plat->setActive(false);
        }

        for (auto ot : vectorObjects[BACKGROUNDS_VECTOR_POS]) {
            int roomNum = std::stoi(ot.getName());
            auto bg = mngr_->addEntity(ecs::_grp_BACKGROUNDS);
            auto bgRect = getSDLRect(ot.getAABB());
            auto roomScale = vectorTiles[roomNum].first;
            bg->addComponent<Transform>(Vector2D(bgRect.x, bgRect.y) * roomScale, bgRect.w* roomScale, bgRect.h* roomScale);
            bg->addComponent<Image>(&sdlutils().images().at(ot.getClass()));
            bg->setActive(false);
            backgrounds[roomNum] = bg;
        }

        for (auto cartel : vectorObjects[CARTELES_VECTOR_POS]) {
            auto name = strSplit(cartel.getName(), '_');
            std::string roomNum = name[0];
            float roomScale = vectorTiles[std::stoi(roomNum)].first;
            SDL_Rect trRect = getSDLRect(cartel.getAABB());
           
            trRect.x *= roomScale;
            if (name[1] != "0") {
                trRect.y -= sdlutils().images().at(cartel.getClass()).height() / sdlutils().images().at(cartel.getClass()).getNumRows();
            }
            trRect.y *= roomScale;
            trRect.w = sdlutils().images().at(cartel.getClass()).width()/ sdlutils().images().at(cartel.getClass()).getNumCols();
            trRect.w *= roomScale;
            trRect.h = sdlutils().images().at(cartel.getClass()).height() / sdlutils().images().at(cartel.getClass()).getNumRows();
            trRect.h *= roomScale;

            game->addCarteles(constructors::Cartel(mngr_, trRect.x, trRect.y, trRect.w, trRect.h, cartel.getClass()), std::stoi(roomNum));
           
        }

        float scale = tileScale();
        for (auto ot : vectorObjects[I_OBJECTS_VECTOR_POS]) {
            //unordered_map<string, TP_Lamp*> lamps;
            float x_ = ot.getAABB().left;
            float y_ = ot.getAABB().top;
            float w_ = ot.getAABB().width;
            float h_ = ot.getAABB().height;
            
            auto classSplit = strSplit(ot.getClass(), '_');
            if (ot.getClass() == "Grass") {
                auto roomScale = vectorTiles[std::stoi(ot.getName())].first;
                auto newGrass = constructors::grass(mngr_,
                    Vector2D((x_* scale)* roomScale, ((y_* scale - sdlutils().images().at("grass").height()) + h_ * scale)* roomScale),
                    w_* scale* roomScale,
                    h_* scale* roomScale,
                    Vector2D(x_* scale* roomScale, ((y_* scale - sdlutils().images().at("grass").height()) + h_ * scale + 100)* roomScale),
                    Vector2D(x_* scale* roomScale, (y_* scale - sdlutils().images().at("grass").height())* roomScale), 0, std::stoi(ot.getName()));
                interact[std::stoi(ot.getName())].push_back(newGrass);
                auto v = &interact[std::stoi(ot.getName())];
                auto it = (--v->end());
                newGrass->getComponent<InteractionComponent>()->setIt(it, v);
                newGrass->setActive(false);
            }
            else if (classSplit[0] == "Element") {
                if (loadEarthElem && (ecs::elements)std::stoi(ot.getName()) == ecs::Earth ||
                    loadWaterElem && (ecs::elements)std::stoi(ot.getName()) == ecs::Water ||
                    loadFireElem && (ecs::elements)std::stoi(ot.getName()) == ecs::Fire) {
                    auto room = std::stoi(classSplit[1]);
                    auto roomScale = vectorTiles[room].first;
                    auto elem = constructors::ElementEntity(mngr_, (x_* scale)* roomScale, (y_* scale)* roomScale, (w_* scale)* roomScale, (h_* scale)* roomScale, (ecs::elements)std::stoi(ot.getName()), room);
                    interact[std::stoi(classSplit[1])].push_back(elem);
                    auto v = &interact[std::stoi(classSplit[1])];
                    auto it = (--v->end());
                    elem->getComponent<InteractionComponent>()->setIt(it, v);
                    elem->setActive(false);
                }
            }
            else if (classSplit[0] == "Lamp") {
                std::string lampName = ot.getName();
                int roomNum = std::stoi(classSplit[1]);
                float roomScale2 = vectorTiles[roomNum].first;

                auto at = lamps.find(lampName);
                if (at != lamps.end()) {
                    auto pos = (*at).second.first;
                    auto t_ = &sdlutils().images().at("lamp");
                    auto fw = t_->getFrameWidth() * 2.5;
                    auto fh = t_->getFrameHeight() * 2.5;
                    float roomScale1 = vectorTiles[(*at).second.second].first;
                    auto hOffset = 15;
                    int w1 = fw * roomScale1;
                    int h1 = fh * roomScale1;
                    int w2 = fw * roomScale2;
                    int h2 = fh * roomScale2;
                    auto lampPair = constructors::lamp(mngr_, pos.getX(), pos.getY() + hOffset * roomScale1, w1, h1, (*at).second.second,
                        x_* scale* roomScale2, y_* scale* roomScale2 + hOffset * roomScale2, w2, h2, roomNum, 0, 0);

                    interact[roomNum].push_back(lampPair.second);
                    auto v = &interact[roomNum];
                    auto it = (--v->end());
                    lampPair.second->getComponent<InteractionComponent>()->setIt(it, v);
                    interact[(*at).second.second].push_back(lampPair.first);
                    auto v2 = &interact[(*at).second.second];
                    auto it2 = (--v->end());
                    lampPair.first->getComponent<InteractionComponent>()->setIt(it2, v2);
                    lampPair.first->setActive(false);
                    lampPair.second->setActive(false);
                }
                else {
                    lamps.insert({ lampName, std::make_pair(Vector2D(x_*scale*roomScale2,y_*scale*roomScale2), roomNum)});
                }
            }
            else if (classSplit[0] == "Sanctuary") {
                auto roomScale = vectorTiles[std::stoi(ot.getName())].first;
                int ID = std::stoi(classSplit[1]);
                Vector2D pos = Vector2D(x_ * scale * roomScale, (y_ * scale) * roomScale);
                auto sanct = constructors::sanctuary(mngr_, pos - Vector2D(0, 250 * roomScale), ID, std::stoi(ot.getName()), 250 * roomScale, 250 * roomScale);
                sanctuaries[ID].sanct = sanct;
                interact[std::stoi(ot.getName())].push_back(sanct);
                auto v = &interact[std::stoi(ot.getName())];
                auto it = (--v->end());
                sanct->getComponent<InteractionComponent>()->setIt(it, v);
                if (std::stoi(classSplit[1]) == player_->getComponent<Health>()->getSanctuaryID()) {
                    playerSanctuary = sanct;
                    playerSanctuaryID = ID;
                    playerSanctuaryRoom = std::stoi(ot.getName());
                }
                sanct->setActive(false);
            }
            else if ((ot.getClass() == "BossRoom") && loadEarthBoss) {
                int roomNum = std::stoi(ot.getName());
                auto roomScale = vectorTiles[roomNum].first;
                SDL_Rect roomDimensions;
                roomDimensions.x = x_ * scale * roomScale;
                roomDimensions.y = y_ * scale * roomScale;
                roomDimensions.w = w_ * scale * roomScale;
                roomDimensions.h = h_ * scale * roomScale;
                Entity* earthBoss = mngr_->addEntity(ecs::_grp_GENERAL);
                earthBoss->addComponent<EarthBossManager>(roomDimensions, this);
                mngr_->setEarthBoss(earthBoss);
                interact[roomNum].push_back(earthBoss);
                earthBoss->setActive(false);
                eraseEntities.push_back(earthBoss);
            }
            else if (ot.getClass() == "EarthBossPlatforms") {
                int roomNum = std::stoi(ot.getName());
                auto roomScale = vectorTiles[roomNum].first;
                SDL_Rect platformDimensions;
                platformDimensions.x = x_ * scale * roomScale;
                platformDimensions.y = y_ * scale * roomScale;
                platformDimensions.w = w_ * scale * roomScale;
                platformDimensions.h = h_ * scale * roomScale;
                Entity* earthBossPlatforms = mngr_->addEntity(ecs::_grp_GENERAL);
                earthBossPlatforms->addComponent<Transform>(platformDimensions);
                platformEarthBoss.push_back(earthBossPlatforms);
                earthBossPlatforms->setActive(false);
                eraseEntities.push_back(earthBossPlatforms);
            }
            else if (ot.getClass() == "lore_Trigger") {
                int roomNum = std::stoi(ot.getName());
                auto roomScale = vectorTiles[roomNum].first;
                SDL_Rect trigger;
                trigger.x = x_ * scale * roomScale;
                trigger.y = y_ * scale * roomScale;
                trigger.w = w_ * scale * roomScale;
                trigger.h = h_ * scale * roomScale;
                Entity* triggerLore = mngr_->addEntity(ecs::_grp_GENERAL);
                triggerLore->addComponent<Transform>(trigger);
                triggerLore->addComponent<LoreRoom>(player_);
                triggerLore->addComponent<Trigger>();
            
                interact[roomNum].push_back(triggerLore);
                auto v = &interact[roomNum];
                auto it = (--v->end());
                triggerLore->getComponent<InteractionComponent>()->setIt(it, v);
                triggerLore->setActive(false);
            }
            else if (classSplit[0] == "Life") {
                auto lifeSharIDSplit = strSplit(pickedLifeShards, ' ');
                bool dontCreate = false;
                for (int i = 0; i < lifeSharIDSplit.size() && !dontCreate; ++i) {
                    dontCreate = lifeSharIDSplit[i] == classSplit[1];
                }
                if (!dontCreate) {
                    auto roomScale = vectorTiles[std::stoi(ot.getName())].first;
                    auto life = constructors::LifeShard(mngr_, x_*scale*roomScale,y_* scale* roomScale, w_* scale* roomScale, h_*scale*roomScale, std::stoi(classSplit[1]), std::stoi(ot.getName()));
                    interact[std::stoi(ot.getName())].push_back(life);
                    auto v = &interact[std::stoi(ot.getName())];
                    auto it = (--v->end());
                    life->getComponent<InteractionComponent>()->setIt(it, v);
                    life->setActive(false);
                }
            }
            else if (classSplit[0] == "WaterTank" && loadFireBoss) {
                auto roomScale = vectorTiles[std::stoi(ot.getName())].first;
                auto wTank = constructors::waterContainer(mngr_, x_ * scale * roomScale, y_ * scale * roomScale, w_ * scale * roomScale, h_ * scale * roomScale, roomScale);
                interact[std::stoi(ot.getName())].push_back(wTank.first);
                eraseEntities.push_back(wTank.first);
                eraseEntities.push_back(wTank.second);
                wTank.first->setActive(false);
            }
            else if (classSplit[0] == "FireBossRoom" && loadFireBoss) {
                auto roomScale = vectorTiles[std::stoi(ot.getName())].first;
                auto fireRoom = constructors::fireBossRoom(mngr_, x_ * scale * roomScale, y_ * scale * roomScale, w_ * scale * roomScale, h_ * scale * roomScale);
                interact[std::stoi(ot.getName())].push_back(fireRoom);
                eraseEntities.push_back(fireRoom);
                fireRoom->setActive(false);
            }
        }

        SDL_Rect playerRect = getSDLRect(playerPos.getAABB());
        
        auto playerTr_ = player_->getComponent<Transform>();
        int playerRoom;
        float playerRoomScale;
        if (playerSanctuary == nullptr || nextPos != -1) {
            if (nextPos != -1) {
                playerRect.x = positions[nextPos].rect.x;
                playerRect.y = positions[nextPos].rect.y;
                playerRoom = positions[nextPos].room;
                playerRoomScale = vectorTiles[playerRoom].first;
                currentRoom = vectorTiles[playerRoom].first;
            }
            else {
                playerRoom = std::stoi(playerPos.getClass());
                playerRoomScale = vectorTiles[playerRoom].first;
                playerRect.x *= playerRoomScale;
                playerRect.y = playerRect.y * playerRoomScale - playerTr_->getHeight();
            }
            playerTr_->setPosition(Vector2D(playerRect.x, playerRect.y));
            playerTr_->setInitialPosition(Vector2D(playerRect.x, playerRect.y));
        }
        else {
            auto newPos = playerSanctuary->getComponent<Transform>()->getPosition() + Vector2D(0, playerSanctuary->getComponent<Transform>()->getHeight() - playerTr_->getHeight());
            playerTr_->setPosition(newPos);
            playerRoom = playerSanctuaryRoom;
            playerRoomScale = vectorTiles[playerRoom].first;
            player_->getComponent<Health>()->setSanctuaryID(playerSanctuaryID);
        }
        playerTr_->setScale(playerRoomScale);
        currentRoom = playerRoom;
        if(backgrounds[currentRoom] != NULL) backgrounds[currentRoom]->setActive(true);
        cam->setBounds(getCamBounds());
        cam->setPos(playerTr_->getPosition());

        if(currentMapKey == "earthMap" && loadEarthBoss) mngr_->getEarthBoss()->getComponent<EarthBossManager>()->addPlatforms(platformEarthBoss);
        generateEnemies();
        activateObjectsInRoom(currentRoom);
        for (auto pl : platforms[currentRoom]) {
            pl->setActive(true);
        }
    }
    else
    {
        std::cout << "Failed loading map" << std::endl;
    }
}

void MapComponent::activateObjectsInRoom(int room, bool activate) {
    auto enemies_ = game->getEnemies();
    auto carteles_ = game->getCarteles();
    for (auto it : interact[room]) {
        it->setActive(activate);
    }
    for (auto it : waterObjects[room]) {
        it->setActive(activate);
    }

    if (enemies_.size() != 0) {
        for (auto it : enemies_[room]) {
            it->setActive(activate);
        }
    }

    if (carteles_.size() != 0) {
        if (carteles_.size() > 0) {
            for (auto it : carteles_[room]) {
                it->setActive(activate);
            }
        }
    }
}

void MapComponent::addCollision(std::string sala, SDL_Rect newCol) {
    ground[sala].push_back(newCol);
}

void MapComponent::deleteCollision(std::string sala) {
    auto pos = ground.find(sala);
    if (pos != ground.end()) (*pos).second.erase(--(*pos).second.end());
}

std::vector<std::pair<SDL_Rect, SDL_Rect>> MapComponent::checkCollisions(const SDL_Rect& playerRect) {
    std::vector<std::pair<SDL_Rect, SDL_Rect>> rects;
    for (SDL_Rect it : ground[std::to_string(currentRoom)]) {
        SDL_Rect result;
        if (SDL_IntersectRect(&playerRect, &it, &result)) {
            rects.push_back(std::make_pair(result, it));
        }
    }
    for (auto it : destructible[std::to_string(currentRoom)]) {
        if (it.first) {
            SDL_Rect result;
            if (SDL_IntersectRect(&playerRect, &it.second, &result)) {
                rects.push_back(std::make_pair(result, it.second));
            }
        }
    }
    return rects;
}

void MapComponent::render() {
    SDL_Rect camPos = cam->camera;
    int cols = sdlutils().levels().at(currentMapKey).cols;
    int offsetX = camPos.x;
    int offsetY = camPos.y;
    int room = currentRoom;
    auto roomScale = vectorTiles[room].first;

    for (int i = 0; i < vectorTiles[room].second.size(); i++) {
        auto it = vectorTiles[room].second[i].first;
        auto ot = vectorTiles[room].second[i].second;
        if (it == 0) continue;
        ot.x *= roomScale;
        ot.y *= roomScale;
        ot.w *= roomScale;
        ot.h *= roomScale;
        ot.x -= offsetX;
        ot.y -= offsetY;
        it--;
        int row = (it - (it % tilemap->getNumCols())) / tilemap->getNumCols();
        int col = it % tilemap->getNumCols();

        tilemap->renderFrame(ot, row, col);
    }

    for (auto it : ground[std::to_string(room)]) {
        it.x -= cam->camera.x;
        it.y -= cam->camera.y;
        sdlutils().images().at("pixel").render(it);
    }
}

void MapComponent::saveToFile(std::ofstream& file) {
    file << "map_key " << currentMapKey << " " << currentMap << std::endl
        << "earth_boss " << loadEarthBoss << std::endl 
        << "water_boss " << loadWaterBoss << std::endl
        << "fire_boss " << loadFireBoss << std::endl;
}

void MapComponent::loadFromFile(std::ifstream& file) {
    std::string aux;
    file >> aux >> currentMapKey >> currentMap >> aux >> loadEarthBoss >> aux >> loadWaterBoss >> aux >> loadFireBoss;
    auto pInput = game->getPlayer()->getComponent<PlayerInput>();
    loadEarthElem = !pInput->hasElement(ecs::Earth);
    loadWaterElem = !pInput->hasElement(ecs::Water);
    loadFireElem = !pInput->hasElement(ecs::Fire);
    pickedLifeShards = game->getPlayer()->getComponent<Health>()->getLifeShardIDs();
}