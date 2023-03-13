#include "MapComponent.h"
//#include "../dependencies/Parser.h"
#include "../sdlutils/SDLUtils.h"
#include "../ecs/Manager.h"
#include "../ecs/Entity.h"
#include "../components/CameraComponent.h"
#include "../states/PlayState.h"
#include "../states/GameStateMachine.h"

MapComponent::MapComponent() {
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
    vectorObjects.reserve(3);
    vectorTiles.reserve(3);
    vectorTiles.push_back({});
    vectorTiles.push_back({});
    vectorTiles.push_back({});
    vectorObjects.push_back({});
    vectorObjects.push_back({});
    vectorObjects.push_back({});
    tilemap = &sdlutils().images().at(sdlutils().levels().at("level1").tileset);

}

void MapComponent::initComponent() {
    cam = mngr_->getCamera()->getComponent<CameraComponent>();
    loadMap(sdlutils().levels().at("level1").route);
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
                const auto& objects = layer->getLayerAs<ObjectGroup>().getObjects();
                if (layer->getName() == "Salas") {
                    vectorObjects[0] = objects;
                }
                else if (layer->getName() == "Objetos interactuables") {
                    vectorObjects[1] = objects;
                }
                else if (layer->getName() == "Colisiones") {
                    vectorObjects[2] = objects;
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
                for (auto salas : vectorObjects[0]) {
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
        
    }
    else
    {
        std::cout << "Failed loading map" << std::endl;
    }

}

void MapComponent::render() {
    SDL_Rect camPos = cam->camera;
    int cols = sdlutils().levels().at("level1").cols;
    int offsetX = camPos.x;
    int offsetY = camPos.y;
    for (int i = 0; i < vectorTiles[1].size(); i++) {
        auto it = vectorTiles[1][i].first;
        auto ot = vectorTiles[1][i].second;
        ot.x -= offsetX;
        ot.y -= offsetY;
        if (it == 0) continue;
        tilemap->renderFrame(ot, (it - (it % 20)) / 20, it % 20 - 1);
    }
}