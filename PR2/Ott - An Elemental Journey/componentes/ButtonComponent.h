#pragma once
#include "Component.h"
#include "Image.h"
#include<string>

class SDLApplication;

using CallBack = void(SDLApplication* app);

class ButtonComponent : public Component
{
private:
	enum button_State { MOUSE_OUT = 0, MOUSE_OVER = 1, CLICKED = 2 };

	int currentButtonFrame = MOUSE_OUT;
	std::string buttonText;
	SDLApplication* app = nullptr;
	CallBack* callback = nullptr;
	Image* image = nullptr;

	void onClick();
public:
	ButtonComponent(std::string text, SDLApplication* a, CallBack* c) : Component(), buttonText(text), app(a), callback(c) {};
	void initComponent() override;
	void update() override;
};

