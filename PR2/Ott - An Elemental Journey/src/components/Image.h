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

	bool allowRender_;

public:
	constexpr static ecs::cmpId_type id = ecs::_IMAGE;
	Image(Texture* tx) : Component() {
		transform = nullptr;
		texture = tx;
		allowRender_ = true;
	};
	virtual ~Image() = default;
	void initComponent() override;
	void render() override;
    int getWidth() const {return texture->width();}
    int getHeight() const {return texture->height();}
	void changeText(Texture* tx) { texture = tx; }
	void disableRender() { allowRender_ = false; }
	void enableRender() { allowRender_ = true; }
};

