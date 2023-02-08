#pragma once

#include <unordered_map>
#include <deque>
#include <string>
#include "../dependencies/Texture.h"

/// Struct que contiene la información de las texturas
struct TextureDescription {
	std::string filename;
	uint numRows, numCols;
	std::string name;
	TextureDescription(std::string filename, uint numRows, uint numCols, std::string name) : filename(filename), numRows(numRows), numCols(numCols), name(name) {}
};

class SDLApplication;

class TextureLoader {
private:
	SDLApplication* app = nullptr;
	std::unordered_map<std::string, Texture*> textures;
	std::unordered_map<std::string, deque<int>> whereIsTextureBeingUsed;

	void registerTexture(const std::string& id, int stateID);
	void deleteTexture(const std::string& id);

public:
	TextureLoader(SDLApplication* app) : app(app) {}
	~TextureLoader() { deleteTextures(); };
	void createTexture(const TextureDescription& texture, int stateID);
	void addTexture(const std::string& id, Texture* texture, int stateID);
	Texture* getTexture(const std::string& id, int stateID);
	void unregisterTexture(int stateID);
	void deleteTextures();
};

