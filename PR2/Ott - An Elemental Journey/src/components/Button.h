#pragma once
#include "FramedImage.h"
#include "Text.h"
#include "Transform.h"
#include "../ecs/Component.h"

using Callback = void(void);

class Button : public Component {
private:
	enum button_State { MOUSE_OUT = 0, MOUSE_OVER = 1, CLICKED = 2 };
	int currentButtonFrame; ///< Estado actual en que se encuentra el bot�n
	Callback* callback; ///< Puntero a una funci�n void con un par�metro Game*
	FramedImage* texture;
	Text* text;
	Transform* transform;

	void onClick();

public:
	constexpr static ecs::cmpId_type id = ecs::_BUTTON;
	Button(Callback* callback) : Component(), callback(callback) {
		currentButtonFrame = MOUSE_OUT;
		texture = nullptr;
		text = nullptr;
		transform = nullptr;
	}
	virtual ~Button() = default;
	void initComponent() override;
	void handleInput() override;
};

