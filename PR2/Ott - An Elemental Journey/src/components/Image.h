#pragma once
#include "../sdlutils/Texture.h"
#include "../game/ecs.h"
#include "Transform.h"
#include "CameraComponent.h"
class Image : public Component
{
private:
	Transform* transform;
	Texture* texture;
	CameraComponent* cam;
public:
	constexpr static ecs::cmpId_type id = ecs::_IMAGE;
	Image(Texture* tx) : Component() {
		transform = nullptr;
		texture = tx;
	};
	virtual ~Image() = default;
	void initComponent() override;
	void render() override;
    int getWidth() const {return texture->width();}
    int getHeight() const {return texture->height();}
	void changeText(Texture* tx) { texture = tx; }
};

