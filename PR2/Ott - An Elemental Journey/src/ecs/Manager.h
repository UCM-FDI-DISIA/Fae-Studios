#ifndef TPV2_MANAGER_H
#define TPV2_MANAGER_H
#include <vector>
#include <array>
#include "../game/ecs.h"
#include "../utils/Vector2D.h"

const int LEVEL_WIDTH = 8000;
const int LEVEL_HEIGHT = 8000;
const auto CAM_OFFSET_HEIGHT = 0.6;
const int CAM_DEAD_ZONE = 250;

//Declaramos una clase Entity "falsa" para evitar dependencias circulares
class Entity;

/// Clase que se encarga del manejo de todas las entidades del juego
class Manager {
private:
    std::array<std::vector<Entity*>, ecs::maxGroupId> entsByGroup_; ///< Matriz que separa las entidades por grupos
    bool deleted;

public:
    /// Constructora de la clase Manager
    Manager();

    /// Destructora de la clase Manager
    virtual ~Manager();

    /// Añade una entidad al Manager
    /// \param gId Grupo al que se quiere añadir la entidad (GENERAL por defecto)
    /// \return Un puntero a la entidad añadida
    Entity* addEntity(ecs::grpId_type gId = ecs::_grp_GENERAL);

    /// Devuelve todas las entidades asociadas a un grupo
    /// \param gId Grupo del que se quieren obtener las entidades
    /// \return Vector con punteros a entidades
    const inline std::vector<Entity*>& getEntities(ecs::grpId_type gId = ecs::_grp_GENERAL) const { return entsByGroup_[gId]; }

    void addToGroupList(ecs::grpId_type gId, Entity* e);

    /// Borra las entidades "muertas" del manager
    void refresh();

    /// Llama al update de todas las entidades asociadas al manager
    void update();

    /// Llama al render de todas las entidades asociadas al manager
    void render();

    /// Llama al handleInput de todas las entidades asociadas al manager
    void handleInput();

    void setDelete() { deleted = true; }
};

#endif //TPV2_MANAGER_H
