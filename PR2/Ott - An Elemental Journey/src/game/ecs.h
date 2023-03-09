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
        _VINE,
        _CAMERA,
        _ANIM,
        _TRIGGER,
        _ATTACK,
        _ENEMYMOV,
        _HEALTH,
        _INTERACTION,
        _MAP,
        _PHYSICS,
        _CTRL,
        _GEN,

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
        _grp_CHARACTERS,
        _grp_INTERACTION,
        _grp_MAP,
        _grp_GROUND,
        _grp_VINE,

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
    
}

#endif //TPV2_ECS_DEF_H
