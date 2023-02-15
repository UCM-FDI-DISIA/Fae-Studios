#include "Mapa.h"
#include "../dependencies/Parser.h"

Mapa::Mapa(SDLApplication* app, ListaNiveles l) : GameObject(), currentLevel(l), app(app) {
    initializeSources();
    auto it = infoLevel.find(l);
    if (it != infoLevel.end()) {
        auto ot = it->second.begin();
        for (ot; ot != it->second.end(); ++ot) {
            textures[ot->typeT] = app->getTexture(ot->name, PLAY_STATE);
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

void Mapa::loadMap(string path) {
    if (map.load(path))
    {
        const auto& layers2 = map.getLayers();
        // cout << "Map has " << layers2.size() << " layers" << endl;
        for (const auto& layer : layers2)
        {
#pragma region Groups
            //cout << "Found Layer: " << layer->getName() << endl;
            //cout << "Layer Type: " << int(layer->getType()) << endl;

           /*if (layer->getType() == tmx::Layer::Type::Group)
           {
               cout << "Checking sublayers" << endl;
               const auto& sublayers = layer->getLayerAs<LayerGroup>().getLayers();
               cout << "LayerGroup has " << sublayers.size() << " layers" << endl;
               for (const auto& sublayer : sublayers)
               {
                   cout << "Found Layer: " << sublayer->getName() << endl;
                   cout << "Layer Type: " << int(sublayer->getType()) << endl;

                   if (sublayer->getType() == Layer::Type::Object)
                   {
                       cout << sublayer->getName() << " has " << sublayer->getLayerAs<ObjectGroup>().getObjects().size() << " objects" << endl;
                   }
                   else if (sublayer->getType() == tmx::Layer::Type::Tile)
                   {
                       cout << sublayer->getName() << " has " << sublayer->getLayerAs<TileLayer>().getTiles().size() << " tiles" << endl;
                   }
               }
           }*/
#pragma endregion

#pragma region Objects
            if (layer->getType() == Layer::Type::Object)
            {
                const auto& objects = layer->getLayerAs<ObjectGroup>().getObjects();

                //Guardamos objetos en un vector
                vectorObjects = objects;

                /* Ejemplo de propiedades de un objeto (posicion, tama�o, ID y nombre)
                     cout << "Found " << objects.size() << " objects in layer" << endl;
                     for (const auto& object : objects)
                    {
                        Vector2f holi = object.getPosition();
                        cout << holi.x << " " << holi.y << endl;
                        cout << object.getAABB().width << " " << object.getAABB().height << endl;
                        cout << "Object " << object.getUID() << ", " << object.getName() << endl;
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

                /* Ejemplo de propiedades de tiles (ID)
                    if (tiles.empty())
                    {
                        const auto& chunks = layer->getLayerAs<tmx::TileLayer>().getChunks();
                        if (chunks.empty())
                        {
                            std::cout << "Layer has missing tile data\n";
                        }
                        else
                        {
                            std::cout << "Layer has " << chunks.size() << " tile chunks.\n";
                        }
                    }
                    else
                    {
                        std::cout << "Layer has " << tiles.size() << " tiles.\n";
                        for (int i = 0; i < tiles.size(); i++) {
                            cout << tiles[i].ID << " ";
                        }
                        cout << endl;
                    }
                */
            }
#pragma endregion

#pragma region Properties
            /*const auto& properties = layer->getProperties();
            std::cout << properties.size() << " Layer Properties:" << std::endl;
            for (const auto& prop : properties)
            {
                std::cout << "Found property: " << prop.getName() << std::endl;
                std::cout << "Type: " << int(prop.getType()) << std::endl;
            }*/
#pragma endregion
        }
    }
    else
    {
        std::cout << "Failed loading map" << std::endl;
    }

}

void Mapa::render() const{
    int offsetX = 0;
    int offsetY = 0; 
    for (int i = 0; i < vectorTiles.size(); i++) {
        auto it = vectorTiles[i].ID;
        cout << textures[TILESET] << " h: " << textures[TILESET]->getH() <<
            " w: " << textures[TILESET]->getW() <<
            " row: " << textures[TILESET]->getNumCols() << 
            " col: " << textures[TILESET]->getNumRows() << endl;
        textures[TILESET]->renderFrame({ (int)(i % mapSize) * 14 - offsetX, (int)((i / mapSize) * 14) - offsetY, 14, 14 }, (it - (it % textures[TILESET]->getW() / 30)) / (textures[TILESET]->getW() / 30), it % (textures[TILESET]->getW() / 30 - 1));
    }
   
    
}

void Mapa::initializeSources() {
    MapTexturesParser::parse(levelTextureRoute, infoLevel);
    MapParser::parse(levelRoute,levelPath);
}