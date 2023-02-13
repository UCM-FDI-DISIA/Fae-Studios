#include "MapGenerator.h"

void MapGenerator::loadMap(string path) {
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

                /* Ejemplo de propiedades de un objeto (posicion, tamaño, ID y nombre)
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