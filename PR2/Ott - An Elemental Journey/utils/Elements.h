#pragma once
#include <array>

namespace elementsInfo {
	static enum elements { Light, Earth, Water, Fire, Dark };
	static const int numElems = 5;
	// Representación interna doblada
	static int matrix[5][5] = {
	{ 2, 2, 2, 2, 2 },
	{ 2, 2, 4, 1, 0 },
	{ 2, 1, 2, 4, 0 },
	{ 2, 4, 1, 2, 0 },
	{ 2, 4, 4, 4, 2 }
	};
}
