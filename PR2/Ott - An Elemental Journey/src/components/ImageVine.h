//LIMPIO

#pragma once
#include "../ecs/Component.h"
#include "../sdlutils/Texture.h"
#include "Transform.h"
#include "../ecs/Entity.h"
#include "CameraComponent.h"
class ImageVine : public Component {
public:
    ImageVine(Texture* text, float rot);
    virtual ~ImageVine();
    void initComponent() override;
    void render() override;
    inline SDL_Rect getRect() {
        return destTransform;
    }
    constexpr static ecs::cmpId_type id = ecs::_IMAGE;
private:
    Transform* tr_;
    Texture* tex_;
    SDL_Rect destTransform;
    SDL_Rect destTexture;
    float rotation;
};