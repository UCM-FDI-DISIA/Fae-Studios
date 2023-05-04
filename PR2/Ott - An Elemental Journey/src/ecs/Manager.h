#ifndef TPV2_MANAGER_H
#define TPV2_MANAGER_H
#include <vector>
#include <array>
#include "../game/ecs.h"
#include "../utils/Vector2D.h"

const int LEVEL_WIDTH = 80000;
const int LEVEL_HEIGHT = 80000;
const auto CAM_OFFSET_HEIGHT = 0.6;
const int CAM_DEAD_ZONE = 250;

//Declaramos una clase Entity "falsa" para evitar dependencias circulares
class Entity;

/// Clase que se encarga del manejo de todas las entidades del juego
class Manager {
private:
    std::array<std::vector<Entity*>, ecs::maxGroupId> entsByGroup_; ///< Matriz que separa las entidades por grupos
    bool deleted;
    Entity* player_ = nullptr;
    Entity* camera_ = nullptr;
    Entity* earthBoss_ = nullptr;
    Entity* fireBoss_ = nullptr;
    Entity* fireBossRoom_ = nullptr;
    Entity* map_ = nullptr;
    Entity* bossDoor = nullptr;

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

    inline Entity* getPlayer() { return player_; } // handler para el player
    inline void setPlayer(Entity* p) { player_ = p; } // handler para el player

    inline Entity* getMap() { return map_; } // handler para el player
    inline void setMap(Entity* p) { map_ = p; } // handler para el player

    inline Entity* getCamera() { return camera_; } // handler para el player
    inline void setCamera(Entity* c) { camera_ = c; } // handler para el player

    Entity* getEarthBoss() { return earthBoss_; }
    void setEarthBoss(Entity* e) { earthBoss_ = e; }

    Entity* getFireBoss() { return fireBoss_; }
    void setFireBoss(Entity* e) { fireBoss_ = e; }

    Entity* getFireBossRoom() { return fireBossRoom_; }
    void setFireBossRoom(Entity* e) { fireBossRoom_ = e; }

    Entity* getBossDoor() { return bossDoor; }
    void setBossDoor(Entity* e) { bossDoor = e; }

    inline void setDelete() { deleted = true; }

    inline bool isDeleted() { return deleted; }

    void saveToFile(std::ofstream& file);

    void loadFromFile(std::ifstream& file);
};

#endif //TPV2_MANAGER_H
