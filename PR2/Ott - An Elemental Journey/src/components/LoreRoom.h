
#pragma once
#include "../ecs/Component.h"
#include "../sdlutils/Texture.h"
#include "Transform.h"
#include "../ecs/Entity.h"
class LoreRoom : public Component {
public:
    LoreRoom(Entity* p):player_(p){};
    virtual ~LoreRoom(){};
    void initComponent() override{};
    void render() override{};
    void startLore();
   
    constexpr static ecs::cmpId_type id = ecs::_LORE;
private:
    Entity* player_;
};