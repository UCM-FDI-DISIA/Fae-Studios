#pragma once
#ifndef PROYECTOS2_MENUSTATE_H
#define PROYECTOS2_MENUSTATE_H

#include "../GameState.h"
#include "../../dependencies/Texture.h"

/// Clase base de la que parten todos los estados relacionados con menús
class MenuState : public GameState {
protected:
    Texture* menuBg = nullptr; ///< Puntero a la textura del fondo

    /// Constructora de MenuState
    /// \param stateID ID del estado
    /// \param bg Textura con el fondo
    /// \param app Puntero a SDLApplication
    MenuState(STATEID stateID, Texture* bg, SDLApplication* app) : GameState(stateID, app), menuBg(bg) {};

public:
    /// Renderiza los objetos del menú y el fondo
    void render() const override;
};

#endif //PROYECTOS2_MENUSTATE_H
