#pragma once
#include <cstdint>
class ecs
{
public:
	using cmpId_type = uint8_t;
	using grpId_type = uint8_t;
	enum cmpId : cmpId_type {
		_TRANSFORM,
		_IMAGE,
		_HEALTH,
		_CTRL,
		_FRAMEDIMAGE,
		_BUTTON,
		// do not remove this
		_LAST_CMP_ID
	};
	static constexpr cmpId_type maxComponentId = _LAST_CMP_ID;
	
	enum grpId : grpId_type {
		_grp_GENERAL,
		_grp_CHARACTERS,
		_grp_GROUND,
		_grp_PROYECTILES,
		_LAST_GRP_ID
	};
	static constexpr grpId_type maxGroupId = _LAST_GRP_ID;
};

