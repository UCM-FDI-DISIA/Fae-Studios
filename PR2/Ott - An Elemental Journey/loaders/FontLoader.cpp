#include "../checkML.h"
#include "FontLoader.h"
#include "../SDLApplication.h"

void FontLoader::createFont(const FontDescription& font) {
	try {
		fonts.insert({ font.name, new Font(font.filename, font.fontSize)});
	}
	catch (SDLError& e) {
		throw e;
	}
}

void FontLoader::addFont(const std::string& id, Font* font) {
	std::unordered_map<std::string, Font*>::iterator it = fonts.find(id);
	if (it != fonts.end()) delete font;
	else fonts[id] = font;
}

Font* FontLoader::getFont(const std::string& id) {
	std::unordered_map<std::string, Font*>::iterator it = fonts.find(id);
	if (it != fonts.end()) return (it->second);
    else return nullptr;
}

void FontLoader::deleteFonts() {
	for (auto it = fonts.begin(); it != fonts.end();) {
		delete it->second;
		it = fonts.erase(it);
	}
}