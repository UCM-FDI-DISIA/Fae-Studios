#pragma once
#include "../ecs/Component.h"
#include "../sdlutils/Texture.h"
#include "../ecs/Entity.h"
#include "../utils/Vector2D.h"

class BackgroundImage : public Component
{
public:
	BackgroundImage(Vector2D pos, Texture* text, int wScale, int hScale);
	virtual ~BackgroundImage();
	void initComponent() override;
	void render() override;
	constexpr static ecs::cmpId_type id = ecs::_IMAGE;
private:
	Texture* tex_;
	Vector2D position;
	int wScale, hScale;
};