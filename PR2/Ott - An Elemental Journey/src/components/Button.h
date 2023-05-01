//LIMPIO

#pragma once
#include "FramedImage.h"
#include "TextComponent.h"
#include "Transform.h"
#include "../ecs/Component.h"
#include <functional>
#include "Image.h"

class ButtonNeedle : public Component {
private:
	Transform* transform;
	Image* texture;

public:
	constexpr static ecs::cmpId_type id = ecs::_BUTTON_NEEDLE;
	ButtonNeedle() : Component() {
		transform = nullptr;
		texture = nullptr;
	}
	virtual ~ButtonNeedle() = default;
	inline void setPosition(Vector2D& position) { transform->setPosition(position); };
	void initComponent() override;
	inline void show() { texture->enableRender(); }
	inline void hide() { texture->disableRender(); }
};

class Button : public Component {
private:
	enum button_State { MOUSE_OUT = 0, MOUSE_OVER = 1, CLICKED = 2 }; ///< Estados en los que puede estar el botón
	Entity* needle;
	int currentButtonFrame; ///< Estado actual en que se encuentra el bot�n
	std::function<void()> callback; ///< Puntero a una funci�n void con un par�metro Game*
	FramedImage* texture; ///< Puntero a la textura del botón
	TextComponent* text; ///< Puntero al texto del botón
	Transform* transform; ///< Posición del botón en pantalla

	bool selected;

public:
	constexpr static ecs::cmpId_type id = ecs::_BUTTON;
	
	Button(std::function<void()> const& callback) : Component(), callback(callback), 
		currentButtonFrame(MOUSE_OUT), texture(nullptr), text(nullptr), transform(nullptr), needle(nullptr), selected(false) {}
	
	void update() override;
	void initComponent() override;
	void handleInput() override;
	void setNeedle(Entity* needle);
	inline void select() { selected = true; }
	inline void unselect() { selected = false; }
	void onClick();
};

