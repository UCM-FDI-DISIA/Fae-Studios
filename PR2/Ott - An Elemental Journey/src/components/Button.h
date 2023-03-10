//LIMPIO

#pragma once
#include "FramedImage.h"
#include "TextComponent.h"
#include "Transform.h"
#include "../ecs/Component.h"

using Callback = void(void);

class Button : public Component {
private:
	enum button_State { MOUSE_OUT = 0, MOUSE_OVER = 1, CLICKED = 2 }; ///< Estados en los que puede estar el botón
	int currentButtonFrame; ///< Estado actual en que se encuentra el bot�n
	Callback* callback; ///< Puntero a una funci�n void con un par�metro Game*
	FramedImage* texture; ///< Puntero a la textura del botón
	TextComponent* text; ///< Puntero al texto del botón
	Transform* transform; ///< Posición del botón en pantalla

	void onClick();

public:
	constexpr static ecs::cmpId_type id = ecs::_BUTTON;
	
	Button(Callback* callback) : Component(), callback(callback), 
		currentButtonFrame(MOUSE_OUT), texture(nullptr), text(nullptr), transform(nullptr) {}
	virtual ~Button() = default;
	
	void initComponent() override;
	void handleInput() override;
};

