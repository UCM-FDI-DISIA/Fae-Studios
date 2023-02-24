#pragma once
#include "Component.h"
#include "../dependencies/Texture.h"
#include "Transform.h"
#include "../Src/Entity.h"
#include <SDL.h>
class FramedImage : public Component
{
public:
	FramedImage(Texture* text, int r, int c);
	FramedImage(Texture* text, int r, int c, int f);
	virtual ~FramedImage();
	void initComponent() override;
	void render() override;
	constexpr static cmpId_type id = ecs::_FRAMEDIMAGE;
private:
	Transform* tr_;
	Texture* tex_;
	int numRows_, numCols_;
	int row = 0, col = 0;
	int tPerFrame;
};

