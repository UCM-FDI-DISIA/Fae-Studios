#pragma once
#include <array>

class elementsInfo {
public:
	static enum elements { Light, Earth, Water, Fire, Dark };
	static const int numElems = 5;
	// Representación interna doblada
	static int matrix[5][5];
};
