#include "MapComponent.h"
//#include "../dependencies/Parser.h"
#include "../sdlutils/SDLUtils.h"
#include "../ecs/Manager.h"
#include "../ecs/Entity.h"
#include "../components/CameraComponent.h"
#include "../states/PlayState.h"
#include "../states/GameStateMachine.h"


MapComponent::MapComponent(Entity* fadeOut) : fadeOut(fadeOut) {
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

    vectorObjects.reserve(4);
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
            if (SDL_IntersectRect(&playerRect, &trigger.second, &result)) {

                Vector2D newPos;
                if (trigger.second.w > trigger.second.h) { // TRIGGER VERTICAL
                    if (result.y < trigger.second.y) { // por arriba
                        newPos = Vector2D(playerRect.x,
                            trigger.second.y + trigger.second.h - playerRect.h);
                    }
                    else { // por abajo
                        newPos = Vector2D(trigger.second.x + trigger.second.w + playerRect.w,
                            trigger.second.y - trigger.second.h - playerRect.h*1.5);
                    }
                }
                else { // TRIGGER HORIZONTAL
                    if (result.x > trigger.second.x + trigger.second.w / 2) {
                        newPos = Vector2D(trigger.second.x - trigger.second.w - playerRect.w,
                            trigger.second.y + trigger.second.h - playerRect.h);
                    }
                    else {
                        newPos = Vector2D(trigger.second.x + trigger.second.w + playerRect.w,
                            trigger.second.y + trigger.second.h - playerRect.h);
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
                //Guardamos objetos en un vector

                /*
                //Ejemplo de propiedades de un objeto (posicion, tama�o, ID y nombre)
                //cout << "Found " << objects.size() << " objects in layer" << endl;
                for (const auto& object : objects)
                {
                    Vector2f holi = object.getPosition();
                    //cout << "Object " << object.getUID() << ", " << object.getName() << " " << object.getClass() << endl;
                }
                */
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
                            std::cout << "intersection" << std::endl;
                            vectorTiles[i].push_back(std::make_pair(tile.ID, tileRect));
                        }
                        o++;
                    }
                    ++i;
                }

                // vectorTiles = tiles;
            }
            #pragma endregion
        }

        for (auto trigger : vectorObjects[TRIGGERS_VECTOR_POS]) {
            SDL_Rect rect = getSDLRect(trigger.getAABB());
            // guardamos los triggers en las dos salas, ya que son bidireccionales
            triggers[trigger.getName()].push_back(std::make_pair(trigger.getClass(),rect));
            triggers[trigger.getClass()].push_back(std::make_pair(trigger.getName(),rect));
        }
    }
    else
    {
        std::cout << "Failed loading map" << std::endl;
    }

    cam->setBounds(getCamBounds());


}

void MapComponent::render() {
    SDL_Rect camPos = cam->camera;
    int cols = sdlutils().levels().at("level1").cols;
    int offsetX = camPos.x;
    int offsetY = camPos.y;
    int room = currentRoom;
    for (int i = 0; i < vectorTiles[room].size(); i++) {
        auto it = vectorTiles[room][i].first;
        auto ot = vectorTiles[room][i].second;
        ot.x -= offsetX;
        ot.y -= offsetY;
        if (it == 0) continue;
        tilemap->renderFrame(ot, (it - (it % 20)) / 20, it % 20 - 1);
    }
}