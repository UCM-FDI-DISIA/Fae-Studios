#pragma once
#ifndef PROYECTOS2_MENUSTATE_H
#define PROYECTOS2_MENUSTATE_H

#include "../GameState.h"

/// Clase base de la que parten todos los estados relacionados con menús
class MenuState : public GameState {
protected:
    //Texture* menuBg = nullptr; ///< Puntero a la textura del fondo

    /// Constructora de MenuState
    /// \param stateID ID del estado
    /// \param bg Textura con el fondo
    /// \param app Puntero a SDLApplication
    MenuState() : GameState(ecs::_state_MENU) {};
};

#endif //PROYECTOS2_MENUSTATE_H
