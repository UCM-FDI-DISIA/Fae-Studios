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
    std::vector<Entity*>::iterator interactionIt;
    bool deleted;
    Entity* player;
    Entity* camera;
    float gravityValue = 0.2;

    void createLamp(int x1, int y1, int x2, int y2);
    void createSanctuary(Vector2D position, int width = 100, int height = 130);
    void createGrass(Vector2D position, int width = 60, int height = 60);
    void createVine(Vector2D position, int width = 60, int height = 120);

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

    void createPlayer();

    inline float getGravityValue() const { return gravityValue; }
    inline Entity* getPlayer() const { return player; }
    inline Entity* getCamera() const { return camera; }
    inline int getLvlW() const { return LEVEL_WIDTH; }
    inline int getLvlH() const { return LEVEL_HEIGHT; }
    inline int getCamDZ() const { return CAM_DEAD_ZONE; }
    inline float getCamOH() const { return CAM_OFFSET_HEIGHT; }

    static void Teleport(Manager* m);
    static void Save(Manager* m);
    static void AddEnredadera(Manager* m);
    void checkInteraction();
    inline Entity* getCurrentInteraction() const { return *interactionIt; }
};

#endif //TPV2_MANAGER_H
