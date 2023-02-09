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