#include "MapComponent.h"
#include "../dependencies/Parser.h"
#include "../SDLApplication.h"
MapComponent::MapComponent(SDLApplication* app, ListaNiveles l) : currentLevel(l), app(app) {
    initializeSources();
    //textures = std::vector<Texture*>(NUMBER_OF_TYPES);
    auto it = infoLevel.find(l);
    if (it != infoLevel.end()) {
        auto ot = it->second.begin();
        for (ot; ot != it->second.end(); ++ot) {
            tilemap = app->getTexture(ot->name, PLAY_STATE);
        }
        auto ut = levelPath.find(l);
        if (ut != levelPath.end()) {
            mapSize = ut->second.size;
            loadMap(ut->second.route);
        }
    }
    else
    {
        cout << "Failed loading map" << std::endl;
    }

}

void MapComponent::loadMap(string path) {
    if (map.load(path))
    {
        const auto& layers2 = map.getLayers();
        cout << "Map has " << layers2.size() << " layers" << endl;
        for (const auto& layer : layers2)
        {
#pragma region Objects
            if (layer->getType() == Layer::Type::Object)
            {
                const auto& objects = layer->getLayerAs<ObjectGroup>().getObjects();

                //Guardamos objetos en un vector
                vectorObjects.push_back(objects);

                //Ejemplo de propiedades de un objeto (posicion, tama�o, ID y nombre)
                cout << "Found " << objects.size() << " objects in layer" << endl;
                for (const auto& object : objects)
                {
                    Vector2f holi = object.getPosition();
                    cout << "Object " << object.getUID() << ", " << object.getName() << " " << object.getClass() << endl;
                }

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
    Vector2D camPos = mngr_->getCamera()->getComponent<Transform>()->getPos();
    int offsetX = camPos.getX();
    int offsetY = camPos.getY();
    for (int i = 0; i < vectorTiles.size(); i++) {
        auto it = vectorTiles[i].ID;
        if (it == 0) continue;
        tilemap->renderFrame({ (int)(i % 100) * usedTileSize - offsetX, (int)((i / 100) * usedTileSize) - offsetY, usedTileSize, usedTileSize }, (it - (it % 20)) / 20, it % 20 - 1);
    }
}


void MapComponent::initializeSources() {
    MapTexturesParser::parse(levelTextureRoute, infoLevel);
    MapParser::parse(levelRoute, levelPath);
}