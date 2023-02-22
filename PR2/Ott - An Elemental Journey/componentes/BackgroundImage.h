#pragma once
#include "Component.h"
#include "../dependencies/Texture.h"
#include "../Src/Entity.h"
#include "../dependencies/Vector2D.h"
class BackgroundImage : public Component
{
public:
	BackgroundImage(Vector2D pos, Texture* text, int wScale, int hScale);
	virtual ~BackgroundImage();
	void initComponent() override;
	void render() override;
	constexpr static cmpId_type id = ecs::_IMAGE;
private:
	Texture* tex_;
	Vector2D position;
	int wScale, hScale;
};

