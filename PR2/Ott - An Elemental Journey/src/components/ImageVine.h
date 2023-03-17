//LIMPIO

#pragma once
#include "../ecs/Component.h"
#include "../sdlutils/Texture.h"
#include "Transform.h"
#include "../ecs/Entity.h"
#include "CameraComponent.h"

class ImageVine : public Component {
private:
	Transform* tr_;
	Texture* tex_;
	SDL_Rect destTransform;
	SDL_Rect destTexture;
	CameraComponent* cam;

public:
	constexpr static ecs::cmpId_type id = ecs::_IMAGE;
	
	ImageVine(Texture* text) : Component(), tr_(nullptr), tex_(text) {}
	
	void initComponent() override;
	void render() override;
	inline SDL_Rect getRect() {return destTransform;}
};