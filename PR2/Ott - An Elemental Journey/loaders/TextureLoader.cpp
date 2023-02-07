#include "../checkML.h"
#include "TextureLoader.h"
#include "../dependencies/Exceptions.h"
#include "../SDLApplication.h"
#include <iostream>



void TextureLoader::createTexture(const TextureDescription& texture, int stateID) {
	try {
		textures.insert({ texture.name, new Texture(app->getRenderer(), texture.filename, texture.numRows, texture.numCols)}); //Las insertamos en nuestro diccionario de texturas
	}
	catch (SDLError& e) {
		throw e;
	}
}

void TextureLoader::addTexture(const std::string& id, Texture* texture, int stateID) {
	std::unordered_map<std::string, Texture*>::iterator it = textures.find(id);
	if (it != textures.end()) delete texture;
	else {
		textures[id] = texture;
		registerTexture(id, stateID);
	}
}

Texture* TextureLoader::getTexture(const std::string& id, int stateID) {
	std::unordered_map<std::string, Texture*>::iterator it = textures.find(id);
	if (it != textures.end()) {
		registerTexture(id, stateID);
		return (it->second);
	}
	else return nullptr;
}

void TextureLoader::deleteTextures() {
	for (auto it = textures.begin(); it != textures.end();) {
		delete it->second;
		it = textures.erase(it);
	}
}

void TextureLoader::registerTexture(const std::string& id, int stateID) {
	for (auto it = whereIsTextureBeingUsed[id].begin(); it != whereIsTextureBeingUsed[id].end(); ++it) {
		if ((*it) == stateID) return;
	}
	whereIsTextureBeingUsed[id].push_front(stateID);
}

void TextureLoader::unregisterTexture(int stateID) {
	for (auto it = whereIsTextureBeingUsed.begin(); it != whereIsTextureBeingUsed.end();) {
		for (auto it2 = it->second.begin(); it2 != it->second.end();) {
			if ((*it2) == stateID) it2 = it->second.erase(it2);
			else ++it2;
		}
		if (it->second.empty()) {
			deleteTexture(it->first);
			it = whereIsTextureBeingUsed.erase(it);
		}
		else ++it;
	}
}

void TextureLoader::deleteTexture(const std::string& id) {
	auto it = textures.find(id);
	delete it->second;
	textures.erase(id);
}