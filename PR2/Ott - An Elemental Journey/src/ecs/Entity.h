#pragma once
#ifndef TPV2_ENTITY_H
#define TPV2_ENTITY_H
#include "../utils/checkML.h"
#include "../game/ecs.h"
#include "Component.h"
#include "Manager.h"
#include <vector>
#include <array>
#include <utility>

/// Clase base que se encarga del manejo de la funcionalidad de una entidad
class Entity {
private:
    bool alive_, active_ = true; ///< Booleano que indica si la entidad está viva o no
    Manager* mngr_; ///< Puntero al manager que la contiene
    std::vector<Component*> currCmps_; ///< Vector con los componentes que tiene la entidad
    std::array<Component*, ecs::maxComponentId> cmps_; ///< Array con TODOS los componentes de nuestro juego

public:
    /// Constructora de la clase Entity
    Entity() : mngr_(nullptr), cmps_(), currCmps_(), alive_(), active_(true) {
        currCmps_.reserve(ecs::maxComponentId); //Reservamos tantos huecos en el vector como número total de componentes tengamos
    }

    /// Destructora de la clase Entity
    virtual ~Entity() {
        for (auto c : currCmps_) {
            delete c; //Borramos todos los componentes que esta tenga
        }
    }

    /// Le da un contexto a la entidad, es decir, le asigna su manager correspondiente
    /// \param mngr Puntero al manager que contiene a la entidad
    inline void setContext(Manager* mngr) { mngr_ = mngr; }

    /// Indica si la entidad está o no viva
    /// \return Booleano que indica si la entidad está o no viva
    inline bool isAlive() { return alive_; }

    /// Cambiamos si nuestra entidad está viva o no
    /// \param alive Booleano: true (si la entidad está viva), false (si queremos borrarla)
    inline void setAlive(bool alive) { alive_ = alive; }

    // Métodos para activar / desactivar entidades. Lo usamos para que no se rendericen cosas que no se deberían ver ni actualizar.
    inline void setActive(bool active) { active_ = active; }

    inline bool isActive() { return active_; }

    /// Elimina un componente dado su tipo
    /// \tparam T Componente
    template <typename T>
    inline void removeComponent() {
        constexpr ecs::cmpId_type cId = T::id; //Nos guardamos la ID del componente
        if (cmps_[cId] != nullptr) { //Si no es nula...
            auto iter = std::find(currCmps_.begin(),
                currCmps_.end(),
                cmps_[cId]); //... lo buscamos en los componentes actuales de la entidad...
            currCmps_.erase(iter); //... lo quitamos de la lista...
            delete cmps_[cId]; //... y lo borramos del array de componentes
            cmps_[cId] = nullptr;
        }
    }

    /// Añade un componente a la entidad
    /// \tparam T Tipo del componente
    /// \tparam Ts Atributos extra que hay que pasarle al componente
    /// \param args Atributos extra que hay que pasarle al componente
    /// \return Instancia del componente añadido
    template <typename T, typename... Ts>
    inline T* addComponent(Ts&&... args) {
        T* c = new T(std::forward<Ts>(args)...); //Creamos el componente con los parámetros que se hayan introducido
        constexpr ecs::cmpId_type cId = T::id; //Nos guardamos su ID

        removeComponent<T>(); //En caso de que ya hubiese un componente del mismo tipo, lo quitamos

        currCmps_.push_back(c); //Lo metemos al vector de componentes actuales
        cmps_[cId] = c; //Cambiamos su referencia en el array de componentes

        c->setContext(this, mngr_); //Le damos un contexto
        c->initComponent(); //Lo inicializamos

        return c; //Y lo devolvemos
    }

    /// Nos devuelve un componente asociado a una entidad dado su tipo
    /// \tparam T Tipo del componente
    /// \return Puntero a la instancia del componente asociada a la entidad
    template <typename T>
    inline T* getComponent() { 
        constexpr ecs::cmpId_type cId = T::id; //Buscamos la ID del componente pedido
        return static_cast<T*>(cmps_[cId]);  //Y lo devolvemos buscándolo en el array
    }

    /// Comprueba si una entidad tiene cierto componente
    /// \tparam T Tipo del componente
    /// \return Un booleano indicando si la entidad tiene o no el componente pedido
    template <typename T>
    inline bool hasComponent() {
        constexpr ecs::cmpId_type cId = T::id; //Buscamos la ID del componente
        return cmps_[cId] != nullptr; //Y devolvemos si lo tiene o no
    }

    /// Llama al update de todos los componentes de una entidad
    inline void update() {
        if (active_) {
            for (auto i = 0u; i < currCmps_.size(); i++)
                currCmps_[i]->update();
        }
    }

    /// Llama al render de todos los componentes de una entidad
    inline void render() {
        if (active_) {
            auto n = currCmps_.size();
            for (auto i = 0u; i < n; i++)
                currCmps_[i]->render();
        }
    }

    /// reinicializa todos los componentes de una entidad
    inline void reinitCmpts() {
        auto n = currCmps_.size();
        for (auto i = 0u; i < n; i++)
            currCmps_[i]->initComponent();
    }

    /// Llama al handleInput de todos los componentes de una entidad
    inline void handleInput() {
        if (active_) {
            auto n = currCmps_.size();
            for (auto i = 0u; i < n; i++)
                currCmps_[i]->handleInput();
        }
    }
    
    inline void saveToFile(std::ofstream& file) {
        auto n = currCmps_.size();
        for (auto i = 0u; i < n; i++)
            currCmps_[i]->saveToFile(file);
    };

    inline void loadFromFile(std::ifstream& file) {
        auto n = currCmps_.size();
        for (auto i = 0u; i < n; i++)
            currCmps_[i]->loadFromFile(file);
    };
};

#endif //TPV2_ENTITY_H
