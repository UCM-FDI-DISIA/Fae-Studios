#pragma once
#include <array>

namespace elementsInfo {
	enum elements { Light, Earth, Water, Fire, Dark };
	// Representación interna doblada
	int matrix[5][5] = {2, 2, 2, 2, 2,
						2, 2, 4, 1, 0,
						2, 1, 2, 4, 0,
						2, 4, 1, 2, 0,
						2, 4, 4, 4, 2 };
	int numElems = 5;
}
