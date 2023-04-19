//LIMPIO

#pragma once
#include "../ecs/Component.h"
#include "../sdlutils/Texture.h"
#include "Transform.h"
#include "../ecs/Entity.h"
#include "CameraComponent.h"
class ImageVine : public Component {
public:
    ImageVine(Texture* text, float rot, bool canClimb);
    virtual ~ImageVine();
    void initComponent() override;
    void render() override;
    inline SDL_Rect getRect() {
        return destTransform;
    }
    inline bool canClimb() { return canClimb_; }
    constexpr static ecs::cmpId_type id = ecs::_IMAGE;
private:
    Transform* tr_ = nullptr;
    Texture* tex_ = nullptr;
    SDL_Rect destTransform;
    SDL_Rect destTexture;
    SDL_Rect initialPos = {0,0,0,0};
    float rotation;
    bool canClimb_;
};