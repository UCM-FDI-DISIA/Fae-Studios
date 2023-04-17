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
        _ACTIVE_WATER,
        _VINE,
        _CAMERA,
        _WATER_BOSS_ATTACK,
        _ANIM,
        _ENEMYANIM,
        _TRIGGER,
        _ATTACK,
        _ENEMYMOV,
        _ENEMYCONTACT,
        _HEALTH,
        _INTERACTION,
        _MAP,
        _PHYSICS,
        _HEALTH_IMAGE,
        _CTRL,
        _GEN,
        _BULLET,
        _CHARGED_ATTACK,
        _COLLIDERVINE,
        _GROWVINE,
        _PLAYERATTACK,
        _ENEMYSTATES,
        _BOSS,
        _FIREBOSS_ANIM,
        _BOSSACCELERATION,
        _BOSS_PIVOT,
        _BOSS_DESTRUCTION,
        _VINEMANAGER,
        _ENTERBOSS,
        _FADEOUTANIM,
        _EARTH_ATTACK_ANIM,
        _EARTHMNGR,
        _WATER_ATTACK_ANIM,
        _GET_ELEMENT,
        _LIFESHARDANIM,
        _SHIELD,
        _CHARGED_ATTACK_BAR,

        _LAST_CMP_ID
    };
    constexpr cmpId_type maxComponentId = _LAST_CMP_ID;
#pragma endregion

#pragma region Groups
    using grpId_type = uint8_t;
    /// Identificador de los grupos
    enum grpId : grpId_type {
        _grp_GENERAL, ///< General
        _grp_MINIBOSS,
        _grp_GROUND,
        _grp_VINE,
        _grp_MAP,
        _grp_INTERACTION,
        _grp_TRIGGER,
        _grp_CHARACTERS,
        _grp_PROYECTILES,
        _grp_WATER,
        _grp_UI, ///< Elementos de la interfaz gráfica
        _grp_FADEOUT,

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
        _state_MAP, ///< Estado de juego

        _LAST_STATE_ID
    };
    constexpr stateId_type maxStateId = _LAST_STATE_ID;
#pragma endregion

#pragma region AudioChannels
    using channelId_type = int8_t;
    enum channelId : channelId_type {
        _channel_UI = 0,
        _channel_PLAYER = 1,
        _channel_AMBIENTAL = 2,
        _channel_ALERTS = 3,
        _channel_ENEMY_SLIME = 4,
        _channel_ENEMY_MELEE = 5,
        _channel_ENEMY_RANGE = 6,
        _channel_EARTH_BOSS = 7,
        _channel_WATER_BOSS = 8,
        _channel_FIRE_BOSS = 9,

        _LAST_CHANNEL_ID
    };

    constexpr channelId_type maxChannelId = _LAST_CHANNEL_ID;
#pragma endregion

    static enum elements { Light, Earth, Water, Fire, Dark };
    
    enum maps { EARTH_MAP, WATER_MAP, FIRE_MAP, LAST_MAP_ID };

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
