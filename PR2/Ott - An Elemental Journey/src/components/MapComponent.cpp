#include "MapComponent.h"
#include "../sdlutils/SDLUtils.h"
#include "../ecs/Manager.h"
#include "../ecs/Entity.h"
#include "../components/CameraComponent.h"
#include "../states/PlayState.h"
#include "../states/GameStateMachine.h"
#include "../game/Constructors.h"


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

MapComponent::MapComponent(Entity* fadeOut, PlayState* game) : fadeOut(fadeOut), game(game) {
    //textures = std::vector<Texture*>(NUMBER_OF_TYPES);
    //auto it = infoLevel.find(l);
    //if (it != infoLevel.end()) {
    //    auto ot = it->second.begin();
    //    for (ot; ot != it->second.end(); ++ot) {
    //        tilemap = &sdlutils().images().at(ot->name);

    //    }
    //    auto ut = levelPath.find(l);
    //    if (ut != levelPath.end()) {
    //        mapSize = ut->second.size;
    //        loadMap(ut->second.route);
    //    }
    //}
    //else
    //{
    //    //cout << "Failed loading map" << std::endl;
    //}
    vectorObjects.reserve(5);
    vectorObjects.push_back({});
    vectorObjects.push_back({});
    vectorObjects.push_back({});
    vectorObjects.push_back({});
    vectorObjects.push_back({});

    vectorTiles.reserve(6);
    vectorTiles.push_back({});
    vectorTiles.push_back({});
    vectorTiles.push_back({});
    vectorTiles.push_back({});
    vectorTiles.push_back({});
    vectorTiles.push_back({});
    vectorTiles.push_back({});

    tilemap = &sdlutils().images().at(sdlutils().levels().at("level1").tileset);
}

void MapComponent::initComponent() {
    cam = mngr_->getCamera()->getComponent<CameraComponent>();
    player_ = mngr_->getPlayer();
    anim_ = fadeOut->getComponent<FadeOutAnimationComponent>();
    anim_->setMap(ent_);
    loadMap(sdlutils().levels().at("level1").route);
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
                if (newRect.w > newRect.h) { // TRIGGER VERTICAL
                    if (result.y < newRect.y) { // por arriba
                        newPos = Vector2D(playerRect.x,
                            newRect.y + newRect.h - playerRect.h);
                    }
                    else { // por abajo
                        newPos = Vector2D(newRect.x + newRect.w + playerRect.w,
                            newRect.y - newRect.h - playerRect.h*1.5);
                    }
                }
                else { // TRIGGER HORIZONTAL
                    if (result.x > newRect.x + newRect.w / 2) {
                        newPos = Vector2D(newRect.x - newRect.w - playerRect.w,
                            newRect.y + newRect.h - playerRect.h);
                    }
                    else {
                        newPos = Vector2D(newRect.x + newRect.w + playerRect.w,
                            newRect.y + newRect.h - playerRect.h);
                    }
                }
                changeRoom(trigger.first, newPos);
            }
        }
    }
}

void MapComponent::changeRoom(std::string newRoom, Vector2D newPos) {
    // std::stoi -> String TO Int
    anim_->startFadeOut(newPos, std::stoi(newRoom));
}

void MapComponent::loadMap(std::string path) {
    if (map.load(path))
    {
        tmx::Object playerPos;
        std::vector<std::vector<Entity*>> enemies;
        const auto& layers2 = map.getLayers();
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
                    for (auto it : objects) {
                        enemies.push_back({});
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
                int cols = sdlutils().levels().at("level1").cols;
                int offsetX = camPos.x;
                int offsetY = camPos.y;
                int i = 0;
                for (auto salas : vectorObjects[ROOM_VECTOR_POS]) {
                    int o = 0;
                    auto rect = salas.getAABB();
                    SDL_Rect sala = { rect.left * tileScale(), rect.top* tileScale(), rect.width * tileScale(), rect.height * tileScale() };
                    for (auto tile : tiles) {
                        SDL_Rect tileRect = { (float)(o % cols) * usedTileSize, ((float)(o / cols) * usedTileSize), usedTileSize, usedTileSize };
                        /*std::cout << tileRect.x << " "
                            << tileRect.y << " "
                            << tileRect.w << " "
                            << tileRect.h << " "
                            << std::endl;
                            

                        std::cout << sala.x << " "
                            << sala.y << " "
                            << sala.w << " "
                            << sala.h << " "
                            << std::endl;*/

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

        for (auto obj : vectorObjects[COLLISIONS_VECTOR_POS]) {
            SDL_Rect rect = getSDLRect(obj.getAABB());

            auto roomScale = vectorTiles[std::stoi(obj.getName())].first;

            rect.x *= roomScale;
            rect.y *= roomScale;
            rect.w *= roomScale;
            rect.h *= roomScale;
            ground[obj.getName()].push_back(rect);
        }

        for (auto trigger : vectorObjects[TRIGGERS_VECTOR_POS]) {
            SDL_Rect rect1 = getSDLRect(trigger.getAABB());
            SDL_Rect rect2 = getSDLRect(trigger.getAABB());

            auto roomScale = vectorTiles[std::stoi(trigger.getName())].first;

            rect1.x *= roomScale;
            rect1.y *= roomScale;
            rect1.w *= roomScale;
            rect1.h *= roomScale;

            roomScale = vectorTiles[std::stoi(trigger.getClass())].first;

            rect2.x *= roomScale;
            rect2.y *= roomScale;
            rect2.w *= roomScale;
            rect2.h *= roomScale;

            // guardamos los triggers en las dos salas, ya que son bidireccionales
            triggers[trigger.getName()].push_back(std::make_pair(trigger.getClass(),std::make_pair(rect1,rect2)));
            triggers[trigger.getClass()].push_back(std::make_pair(trigger.getName(),std::make_pair(rect2,rect1)));
        }

        float scale = tileScale();
        for (auto ot : vectorObjects[I_OBJECTS_VECTOR_POS]) {
            //unordered_map<string, TP_Lamp*> lamps;
            float x_ = ot.getAABB().left;
            float y_ = ot.getAABB().top;
            float w_ = ot.getAABB().width;
            float h_ = ot.getAABB().height;
            /*
            elementsInfo::elements elem;
            std::string path = "";
            if (ot.getName() == "1") { elem = elementsInfo::Earth; path = "earth"; }
            else if (ot.getName() == "2") { elem = elementsInfo::Water; path = "water"; }
            else if (ot.getName() == "3") { elem = elementsInfo::Fire; path = "fire"; }
            else if (ot.getName() == "4") { elem = elementsInfo::Dark; path = "dark"; }
            */
            if (ot.getClass() == "Grass") {
                constructors::grass(mngr_, Vector2D(x_ * scale, (y_ * scale - sdlutils().images().at("grass").height()) + h_ * scale),
                    w_ * scale, h_ * scale, Vector2D(x_ * scale,
                        (y_ * scale - sdlutils().images().at("grass").height()) + h_ * scale + 100),
                    Vector2D(x_ * scale, (y_ * scale - sdlutils().images().at("grass").height())));
            }
            else if (ot.getClass() == "Lamp") {
                //createLamp(Vector2D(x_ * scale, y_ * scale - game->getTexture("lamp", PLAY_STATE)->getH() * 2));
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
                constructors::sanctuary(mngr_, Vector2D(x_ * scale - (&sdlutils().images().at("sanctuary"))->width() * 1.5, y_ * scale - (&sdlutils().images().at("sanctuary"))->height() * 3.5));
            }
            else if (ot.getClass() == "Ott") {

            }

        }
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
                Entity* enemie = constructors::eRanged(mngr_, path + "Mushroom", x_* scale * roomScale, y_* scale * roomScale, roomScale, elem);
                enemies[roomNum].push_back(enemie);
            }
            else if (it.getClass() == "Melee") {
                Entity* enemie = constructors::eMelee(mngr_, path + "Bug", x_ * scale * roomScale, y_ * scale * roomScale, roomScale, elem);
                enemies[roomNum].push_back(enemie);
            }
            else if (it.getClass() == "Slime") {
                Entity* enemie = constructors::eSlime(mngr_, path + "Slime", x_ * scale * roomScale, y_ * scale * roomScale, roomScale, elem);
                enemies[roomNum].push_back(enemie);
            }
        }

        SDL_Rect playerRect = getSDLRect(playerPos.getAABB());
        auto playerRoom = std::stoi(playerPos.getClass());
        float playerRoomScale = vectorTiles[playerRoom].first;
        playerRect.x *= playerRoomScale;
        playerRect.y *= playerRoomScale;
        player_->getComponent<Transform>()->setPosition(Vector2D(playerRect.x, playerRect.y));
        player_->getComponent<Transform>()->setScale(playerRoomScale);
        game->setEnemies(enemies);
        currentRoom = playerRoom;
        cam->setBounds(getCamBounds());
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

    return rects;
}


void MapComponent::render() {
    SDL_Rect camPos = cam->camera;
    int cols = sdlutils().levels().at("level1").cols;
    int offsetX = camPos.x;
    int offsetY = camPos.y;
    int room = currentRoom;
    for (int i = 0; i < vectorTiles[room].second.size(); i++) {
        auto it = vectorTiles[room].second[i].first;
        auto ot = vectorTiles[room].second[i].second;
        if (it == 0) continue;
        ot.x *= vectorTiles[room].first;
        ot.y *= vectorTiles[room].first;
        ot.x -= offsetX;
        ot.y -= offsetY;
        ot.w *= vectorTiles[room].first;
        ot.h *= vectorTiles[room].first;
        tilemap->renderFrame(ot, (it - (it % 20)) / 20, it % 20 - 1);
    }
}