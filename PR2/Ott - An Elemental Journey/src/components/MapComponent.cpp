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
    tilemap = &sdlutils().images().at(sdlutils().levels().at("demo").tileset);
    loadMap(sdlutils().levels().at("demo").route);

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

                //Guardamos objetos en un vector
                vectorObjects.push_back(objects);

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

#pragma region Tiles
            if (layer->getType() == tmx::Layer::Type::Tile)
            {
                const auto& tiles = layer->getLayerAs<tmx::TileLayer>().getTiles();
                //Guardamos tiles en un vector
                vectorTiles = tiles;
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
    SDL_Rect camPos = static_cast<PlayState*>(GameStateMachine::instance()->getPlayState())->getCamera()->getComponent<CameraComponent>()->camera;
    int cols = sdlutils().levels().at("demo").cols;
    int offsetX = camPos.x;
    int offsetY = camPos.y;
    for (int i = 0; i < vectorTiles.size(); i++) {
        auto it = vectorTiles[i].ID;
        if (it == 0) continue;
        tilemap->renderFrame({ (i % cols) * usedTileSize - offsetX, ((i / cols) * usedTileSize) - offsetY, usedTileSize, usedTileSize}, (it - (it % 20)) / 20, it % 20 - 1);
    }
}