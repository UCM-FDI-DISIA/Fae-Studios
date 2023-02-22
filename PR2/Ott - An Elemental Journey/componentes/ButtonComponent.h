#pragma once
#include "Component.h"
#include "Image.h"
#include <string>
#include "../dependencies/Font.h"

class SDLApplication;

using CallBack = void(SDLApplication* app);

class ButtonComponent : public Component
{
private:
	enum button_State { MOUSE_OUT = 0, MOUSE_OVER = 1, CLICKED = 2 };

	int currentButtonFrame = MOUSE_OUT;
	std::string buttonText;
	Font* font;
	Texture* texture;
	SDLApplication* app = nullptr;
	CallBack* callback = nullptr;
	Image* image;
	void onClick();
public:
	ButtonComponent(std::string text, SDLApplication* a, CallBack* c);
	void initComponent() override;
	void update() override;
	constexpr static cmpId_type id = ecs::_BUTTON;
};

