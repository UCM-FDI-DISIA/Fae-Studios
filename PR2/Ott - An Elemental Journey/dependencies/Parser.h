#pragma once

#include <string>
#include <unordered_map>
#include "../loaders/TextureLoader.h"
#include "../loaders/FontLoader.h"

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
