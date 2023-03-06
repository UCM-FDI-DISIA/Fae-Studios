#pragma once
#include "../sdlutils/Texture.h"
#include "../game/ecs.h"
#include "Transform.h"
class Image : public Component
{
private:
	Transform* transform;
	Texture* texture;
	SDL_Rect getRect() const;
public:
	constexpr static ecs::cmpId_type id = ecs::_IMAGE;
	Image(Texture* tx) : Component() {
		transform = nullptr;
		texture = tx;
	};
	virtual ~Image() = default;
	void initComponent() override;
	void render() override;
};

