#pragma once
#include <cstdint>
namespace ecs
{
	using cmpId_type = uint8_t;
	using grpId_type = uint8_t;
	enum cmpId : cmpId_type {
		_TRANSFORM,
		_INTERACTION,
		_IMAGE,
		_HEALTH,
		_CTRL,
		_FRAMEDIMAGE,
		_BUTTON,
		_MAP,
		_PHYSICS,
		_CAMERA,
		_ANIM,
		_TRIGGER,
		_ATTACK,
		_BULLET,
		_GEN,
		_ENEMYMOV,
		// do not remove this
		_LAST_CMP_ID
	};
	static constexpr cmpId_type maxComponentId = _LAST_CMP_ID;
	
	enum grpId : grpId_type {
		_grp_GENERAL,
		_grp_MAP,
		_grp_INTERACTION,
		_grp_CHARACTERS,
		_grp_GROUND,
		_grp_PROYECTILES,
		

		_LAST_GRP_ID
	};
	static constexpr grpId_type maxGroupId = _LAST_GRP_ID;

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

	static int ottMatrix[5][5] = {
		{ 1, 1, 1, 1, 1 },
		{ 1, 1, 2, 0, -1 },
		{ 1, 0, 1, 2, -1 },
		{ 1, 2, 0, 1, -1 },
		{ 1, 2, 2, 2, 1 }
	};
};

