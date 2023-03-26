#pragma once
#include "../utils/checkML.h"
#include "../game/ecs.h"
#include <fstream>
#include <iostream>
#ifndef TPV2_COMPONENT_H
#define TPV2_COMPONENT_H

//Declaramos dos clases "falsas" para evitar las dependencias circulares
class Entity;
class Manager;

/// Clase base que da funcionalidad a los componentes
class Component {
protected:
    Entity* ent_; ///< Puntero a la entidad que contiene al componente
    Manager* mngr_; ///< Puntero al manager en el que está contenida la entidad

public:
    ///Constructora de la clase Component
    Component() : ent_(), mngr_() {}

    /// Destructora de la clase Component
    virtual ~Component() = default;

    /// Setea el contexto del component: le da una entidad y un manager específicos
    /// \param ent Puntero a la entidad que lo contiene
    /// \param mngr Puntero al manager que contiene a la entidad
    inline void setContext(Entity* ent, Manager* mngr) {
        ent_ = ent;
        mngr_ = mngr;
    };

    /// Inicializa el componente, en caso de que este tenga referencias a otros
    virtual void initComponent() {}

    /// Actualiza las variables del componente
    virtual void update() {}

    /// Renderiza las imágenes del componente en pantalla
    virtual void render() {}

    /// Maneja la entrada del usuario
    virtual void handleInput() {}

    virtual void saveToFile(std::ofstream& file) {};

    virtual void loadFromFile(std::ifstream& file) {};
};

#endif //TPV2_COMPONENT_H
