#pragma once
#include "SDL_events.h"
#include "../ecs/Entity.h"
#include "../ecs/Manager.h"
#include "../components/FadeTransitionComponent.h"

class Game; // Declaramos una clase Game para romper las dependencias circulares

/// Clase base que proporcionará funcionalidad a nuestros estados
class GameState {
protected:
    ecs::stateId_type stateID; ///< Identificador de nuestro estado
    Manager* mngr_; ///< Puntero a un manager
    bool doNotDetectKeyboardInput; ///< Booleano que indica si se permite o no la lectura de teclado (para evitar problemas al abrir menús, etc...)
    Entity* fade;

    /// Constructora de la clase GameState
    /// \param stateID Identificador de nuestro estado
    /// \param g Puntero a la clase Game
    GameState(ecs::stateId_type stateID) : stateID(stateID) { 
        mngr_ = new Manager(); 
        doNotDetectKeyboardInput = true; 
       
    };
    //Creamos un manager nuevo para cada estado e interrumpimos la lectura de teclado

public:
    /// Destructora de la clase GameState
	virtual ~GameState() {delete mngr_;} //Borramos el manager

    /// Llama al update del manager asociado al estado
	virtual void update() {mngr_->update();}

    /// Llama al render del manager asociado al estado
    virtual void render() const {mngr_->render();}

    /// Llama al handleInput del manager asociado al estado
    virtual void handleInput() {mngr_->handleInput();}

    /// Llama al refresh del manager asociado al estado
    virtual void refresh() {mngr_->refresh();}

    /// Devuelve el ID de la escena
    /// \return int con el ID de la escena
	virtual ecs::stateId_type getStateID() const { return stateID; };

    void setDelete() { mngr_->setDelete(); }
};

