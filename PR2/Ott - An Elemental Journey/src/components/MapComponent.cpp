#include "MapComponent.h"
#include "../sdlutils/SDLUtils.h"
#include "../ecs/Manager.h"
#include "../ecs/Entity.h"
#include "../components/CameraComponent.h"
#include "../states/PlayState.h"
#include "../states/GameStateMachine.h"
#include "../game/Constructors.h"

const std::string currentLevel = "level1";

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
        std::cout << roomNum << std::endl;

        if (it.getClass() == "Mushroom") {
            Entity* enemie = constructors::eRanged(mngr_, path + "Mushroom", x_ * scale * roomScale, y_ * scale * roomScale, roomScale, elem);
            game->addEnemy(enemie, roomNum);
        }
        else if (it.getClass() == "Melee") {
            Entity* enemie = constructors::eMelee(mngr_, path + "Bug", x_ * scale * roomScale, y_ * scale * roomScale, roomScale, elem);
            game->addEnemy(enemie, roomNum);
        }
        else if (it.getClass() == "Slime") {
            Entity* enemie = constructors::eSlime(mngr_, path + "Slime", x_ * scale * roomScale, y_ * scale * roomScale, roomScale, elem);
            game->addEnemy(enemie, roomNum);
        }
        else if (it.getClass() == "WaterBoss") {
            
            auto waterBoss = constructors::WaterBoss(mngr_, x_ * scale * roomScale, y_ * scale * roomScale, 300 * scale * roomScale, 300 * scale * roomScale);

            for (auto it : mngr_->getEntities(ecs::_grp_GROUND)) {
                it->getComponent<Destruction>()->setBoss(waterBoss);
            }
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

MapComponent::MapComponent(Entity* fadeOut, PlayState* game) : fadeOut(fadeOut), game(game) {
    int n = 20;
    vectorObjects.reserve(n);
    vectorTiles.reserve(6);
    for (int i = 0; i < n; ++i) {
        vectorObjects.push_back({});
        vectorTiles.push_back({});
        interact.push_back({});
    }


    tilemap = &sdlutils().images().at(sdlutils().levels().at(currentLevel).tileset);
}

void MapComponent::initComponent() {
    cam = mngr_->getCamera()->getComponent<CameraComponent>();
    player_ = mngr_->getPlayer();
    anim_ = fadeOut->getComponent<FadeOutAnimationComponent>();
    anim_->setMap(ent_);
    loadMap(sdlutils().levels().at(currentLevel).route);
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
                changeRoom(trigger.first, newPos, verticalTrigger);
                break;
            }
        }
    }
}

void MapComponent::changeRoom(std::string newRoom, Vector2D newPos, bool verticalTrigger) {
    // std::stoi -> String TO Int
    anim_->startFadeOut(newPos, std::stoi(newRoom), verticalTrigger);
    std::cout << "ANIM ACTIVO? " << fadeOut->isActive() << std::endl;
    game->setVisited(std::stoi(newRoom));
}

void MapComponent::loadMap(std::string path) {
    if (map.load(path))
    {
        tmx::Object playerPos;
        const auto& layers2 = map.getLayers();
        std::unordered_map<std::string, std::pair<Vector2D,int>> lamps;
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
                    numRooms = objects.size();
                    game->initEnemies(numRooms);
                    std::vector<std::string> aux(numRooms);
                    mapKeys = aux;
                    game->initVisitedRooms(numRooms);
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
                int cols = sdlutils().levels().at(currentLevel).cols;
                int offsetX = camPos.x;
                int offsetY = camPos.y;
                int i = 0;
                for (auto salas : vectorObjects[ROOM_VECTOR_POS]) {
                    int o = 0;
                    mapKeys[i] = salas.getName();
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
                constructors::DestructibleTile(mngr_, rect.x, rect.y, rect.w, obj.getName(), index, this);
            }
            else ground[obj.getName()].push_back(rect);
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
                interact[std::stoi(ot.getName())].push_back(constructors::grass(mngr_,
                    Vector2D((x_ * scale) * roomScale , ((y_ * scale - sdlutils().images().at("grass").height()) + h_ * scale)* roomScale),
                    w_ * scale* roomScale, 
                    h_ * scale* roomScale, 
                    Vector2D(x_ * scale * roomScale, ((y_ * scale - sdlutils().images().at("grass").height()) + h_ * scale + 100) * roomScale),
                    Vector2D(x_ * scale * roomScale, (y_ * scale - sdlutils().images().at("grass").height()) * roomScale)));
            }
            else if (classSplit[0] == "Element") {
                auto roomScale = vectorTiles[std::stoi(classSplit[1])].first;
                auto elem = constructors::ElementEntity(mngr_, (x_* scale)* roomScale, (y_* scale)* roomScale, (w_* scale)* roomScale, (h_* scale)* roomScale, (ecs::elements)std::stoi(ot.getName()));
                interact[std::stoi(classSplit[1])].push_back(elem);
            }
            else if (classSplit[0] == "Lamp") {
                //createLamp(Vector2D(x_ * scale, y_ * scale - game->getTexture("lamp", PLAY_STATE)->getH() * 2));

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
                        x_* scale* roomScale2, y_* scale* roomScale2 + hOffset * roomScale2, w2, h2, roomNum);

                    interact[roomNum].push_back(lampPair.second);
                    interact[(*at).second.second].push_back(lampPair.first);
                }
                else {
                    lamps.insert({ lampName, std::make_pair(Vector2D(x_*scale*roomScale2,y_*scale*roomScale2), roomNum)});
                }
            }
            else if (ot.getClass() == "Sanctuary") {
                auto roomScale = vectorTiles[std::stoi(ot.getName())].first;
                Vector2D pos = Vector2D(x_ * scale * roomScale, (y_ * scale) * roomScale);
                interact[std::stoi(ot.getName())].push_back(constructors::sanctuary(mngr_, pos - Vector2D(0, 250 * roomScale), 250 * roomScale, 250 * roomScale));
                std::cout << pos << std::endl;
            }
            else if (ot.getClass() == "BossRoom") {
                auto roomScale = vectorTiles[std::stoi(ot.getName())].first;
                SDL_Rect roomDimensions;
                roomDimensions.x = x_ * scale * roomScale;
                roomDimensions.y = y_ * scale * roomScale;
                roomDimensions.w = w_ * scale * roomScale;
                roomDimensions.h = h_ * scale * roomScale;
                Entity* earthBoss = mngr_->addEntity(ecs::_grp_GENERAL);
                earthBoss->addComponent<EarthBossManager>(roomDimensions);
                mngr_->setEarthBoss(earthBoss);
                //earthBoss->getComponent<EarthBossManager>()->initializeEntities();
            }
            else if (ot.getClass() == "DoorTrigger") {
                auto roomScale = vectorTiles[std::stoi(ot.getName())].first;
                Entity* trigger = mngr_->addEntity(ecs::_grp_TRIGGER);
                trigger->addComponent<Transform>(Vector2D(x_* scale * roomScale, y_* scale* roomScale), w_* scale* roomScale, h_* scale* roomScale);
                trigger->addComponent<VineManager>(EVIL, 
                    Vector2D(((x_ * scale) - 260)* roomScale, (((y_ * scale) + h_ * scale) - 100) * roomScale) ,
                    Vector2D((x_ * scale* roomScale) - 170 * roomScale, (y_ * scale - 100)* roomScale),
                    -1, 0, w_ * scale* roomScale, h_ * scale* roomScale, 3);
                trigger->getComponent<VineManager>()->createVine();
                trigger->addComponent<EnterBossRoom>(&sdlutils().images().at("animationWorm"));
                trigger->addComponent<Trigger>();
                interact[std::stoi(ot.getName())].push_back(trigger);
            }
            else if (ot.getClass() == "Life") {
                auto roomScale = vectorTiles[std::stoi(ot.getName())].first;
                auto life = constructors::LifeShard(mngr_, x_*scale*roomScale,y_* scale* roomScale, w_* scale* roomScale, h_*scale*roomScale);
                interact[std::stoi(ot.getName())].push_back(life);

            }
        }

        SDL_Rect playerRect = getSDLRect(playerPos.getAABB());
        auto playerRoom = std::stoi(playerPos.getClass());
        float playerRoomScale = vectorTiles[playerRoom].first;
        auto playerTr_ = player_->getComponent<Transform>();
        playerRect.x *= playerRoomScale;
        playerRect.y = playerRect.y * playerRoomScale - playerTr_->getHeight();
        playerTr_->setPosition(Vector2D(playerRect.x, playerRect.y));
        playerTr_->setScale(playerRoomScale);
        currentRoom = playerRoom;
        cam->setBounds(getCamBounds());
        generateEnemies();

    }
    else
    {
        std::cout << "Failed loading map" << std::endl;
    }
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
    int cols = sdlutils().levels().at(currentLevel).cols;
    int offsetX = camPos.x;
    int offsetY = camPos.y;
    int room = currentRoom;
    auto roomScale = vectorTiles[room].first;
    for (int i = 0; i < vectorTiles[room].second.size(); i++) {
        auto it = vectorTiles[room].second[i].first;
        if (it == 0) continue;
        auto ot = vectorTiles[room].second[i].second;
        ot.x *= roomScale;
        ot.y *= roomScale;
        ot.w *= roomScale;
        ot.h *= roomScale;
        ot.x -= offsetX;
        ot.y -= offsetY;
        tilemap->renderFrame(ot, (it - (it % 20)) / 20, it % 20 - 1);
    }

    for (auto it : ground[std::to_string(room)]) {
        it.x -= cam->camera.x;
        it.y -= cam->camera.y;
        sdlutils().images().at("pixelWhite").render(it);
    }
}