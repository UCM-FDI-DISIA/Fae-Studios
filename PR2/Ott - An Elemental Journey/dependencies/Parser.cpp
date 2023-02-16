#include "../checkML.h"
#include "Parser.h"
#include <fstream>
#include "Exceptions.h"

void TextureParser::parse(std::string route, std::unordered_map<std::string, TextureDescription>& textureMap) {
	ifstream input;
	std::string file = route + "images.info";
	input.open(file);
	if (!input.is_open()) throw FileNotFoundError("No se han podido parsear las texturas: ", file);

	while (input) {
		string str = " ";
		string subroute, filename, name;
		uint rows, cols;
		int forTimes;
		input >> subroute >> forTimes;
		for (int i = 0; i < forTimes; ++i) {
			input >> filename >> rows >> cols >> name;
			textureMap.insert({ name, TextureDescription(route + subroute + "/" + filename, rows, cols, name) });
		}
	}
	
	input.close();
}

void FontParser::parse(std::string route, std::unordered_map<std::string, FontDescription>& fontMap) {
	ifstream input;
	std::string file = route + "fonts.info";
	input.open(file);
	if (!input.is_open()) throw FileNotFoundError("No se han podido parsear las fuentes: ", file);
	int forTimes;
	input >> forTimes;
	for (int i = 0; i < forTimes; ++i) {
		string str = " ";
		string filename, name;
		input >> filename >> name;
		fontMap.insert({ name, FontDescription(route + filename, name) });
	}

	input.close();
}

void MapTexturesParser::parse(std::string route, std::unordered_map<ListaNiveles, list<infoTexture>>& texturesUsedInLevel) {
    ifstream input;
    std::string file = route + "leveltexture.info";
    input.open(file);
    if(!input.is_open()) throw FileNotFoundError("No se han podido parsear las texturas de los mapas: ", file);
    int forTimes;
    input >> forTimes;
    for(int i = 0; i < forTimes; ++i) {
        int listaNivel, numTexturas;
        input >> listaNivel >> numTexturas;
        string name;
        int textureType;
        for(int j = 0; j < numTexturas; ++j) {
            input >> name >> textureType;
            texturesUsedInLevel[ListaNiveles(listaNivel)].push_back(infoTexture(name, TypeTexture(textureType)));
        }
    }
    input.close();
}

void MapParser::parse(std::string route, std::unordered_map<ListaNiveles, infoMap>& levelRouteMap) {
    ifstream input;
    std::string file = route + "levels.info";
    input.open(file);
    if (!input.is_open()) throw FileNotFoundError("No se han podido parsear los mapas: ", file);
    int forTimes;
    input >> forTimes;
    for(int i = 0; i < forTimes; ++i) {
        int listaNivel;
        string filename;
        int mapSize;
        input >> listaNivel >> filename >> mapSize;
        levelRouteMap.insert({ListaNiveles(listaNivel), infoMap(route + filename, mapSize)});
    }

    input.close();
}