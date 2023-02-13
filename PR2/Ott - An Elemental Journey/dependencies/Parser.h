#pragma once
#include <string>
#include <list>
#include <unordered_map>
#include "../loaders/TextureLoader.h"
#include "../loaders/FontLoader.h"
#include "../gameobjects/Mapa.h"

class TextureParser {
private:
	TextureParser() = default;
public:
	static void parse(std::string route, std::unordered_map<std::string, TextureDescription>& textureMap);
};

class FontParser {
private:
	FontParser() = default;

public:
	static void parse(std::string route, std::unordered_map<std::string, FontDescription>& fontMap);
};

class MapTexturesParser {
private:
    MapTexturesParser() = default;
public:
    static void parse(std::string route, std::unordered_map<ListaNiveles, list<infoTexture>> texturesUsedInLevel);
};

class MapParser {
private:
    MapParser() = default;
public:
    static void parse(std::string route, std::unordered_map<ListaNiveles, infoMap> levelRouteMap);
};
