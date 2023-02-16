#pragma once

#include <unordered_map>
#include <string>
#include "../dependencies/Font.h"

class SDLApplication;

/// Struct que contiene la información de las fuentes
struct FontDescription {
	std::string filename;
	std::string name;
	float fontSize;
	FontDescription(std::string filename, std::string name, float fontSize = 20.0f) : filename(filename), name(name), fontSize(fontSize) {}
};

class SDLApplication;

class FontLoader {
private:
	SDLApplication* app = nullptr;
	std::unordered_map<std::string, Font*> fonts;

public:
	FontLoader(SDLApplication* app) : app(app) {}
	~FontLoader() { deleteFonts(); };
	void createFont(const FontDescription& font);
	void addFont(const std::string& id, Font* font);
	Font* getFont(const std::string& id);
	void deleteFonts();
};

