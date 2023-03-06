#pragma once
#include "../utils/checkML.h"
#ifndef TPV2_ECS_DEF_H
#define TPV2_ECS_DEF_H

#include <cstdint>

namespace ecs {
#pragma region Components
    using cmpId_type = uint8_t;
    /// Identificador de los componentes
    enum cmpId : cmpId_type {
        _TRANSFORM = 0, ///< Transform
        _IMAGE, ///< Image y FramedImage
        _TEXT, ///< Text
        _BUTTON,
        _SLIDER,
        _SLIDER_NEEDLE,
        _SLIDER_PERCENTAGE,

        _LAST_CMP_ID
    };
    constexpr cmpId_type maxComponentId = _LAST_CMP_ID;
#pragma endregion

#pragma region Groups
    using grpId_type = uint8_t;
    /// Identificador de los grupos
    enum grpId : grpId_type {
        _grp_GENERAL, ///< General
        _grp_UI, ///< Elementos de la interfaz gráfica

        _LAST_GRP_ID
    };
    constexpr grpId_type maxGroupId = _LAST_GRP_ID;
#pragma endregion

#pragma region States
    using stateId_type = uint8_t;
    /// Identificador de los estados
    enum stateId : stateId_type {
        _state_MENU, ///< Menú
        _state_PLAY, ///< Estado de juego

        _LAST_STATE_ID
    };
    constexpr stateId_type maxStateId = _LAST_STATE_ID;
#pragma endregion
}

#endif //TPV2_ECS_DEF_H
