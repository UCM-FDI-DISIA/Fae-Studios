#pragma once
#include "../ecs/Component.h"
#include "../utils/Vector2D.h"
#include "../sdlutils/Texture.h"
class Transform : public Component
{
private:
	Vector2D position;
	float rotation;
	float width;
	float height;

public:
	constexpr static ecs::cmpId_type id = ecs::_TRANSFORM;
	Transform(Vector2D p, float w, float h, float r = 0.0f) : Component() {
		mngr_ = nullptr;
		ent_ = nullptr;
		position = p;
		rotation = r;
		width = w;
		height = h;
	};
	Transform(float x, float y, float w, float h) : Component() {
		position = Vector2D(x, y);
		width = w;
		height = h;
	}
	Transform(const Vector2D& position, Texture* texture, const Vector2D& scale = Vector2D(1.0f, 1.0f)) : Component() {
		this->position = position;
		width = texture->width() / texture->getNumCols() * scale.getX();
		height = texture->height() / texture->getNumRows() * scale.getY();
	}
	virtual ~Transform() = default;
	inline float getRotation() const { return rotation; };
	inline void setRotation(float r) { rotation += r; };
	void update() override;
	inline Vector2D getPosition() const { return position; };
	inline void setPosition(Vector2D newPos) { position = newPos; };
	inline void setWidth(float w) { width = w; }
	inline void setHeight(float h) { height = h; }
	inline float getWidth() const { return width; };
	inline float getHeight() const { return height; };
	inline SDL_Rect& getRect() {
		SDL_Rect result; result.x = position.getX(); result.y = position.getY(); result.w = width; result.h = height;
		return result;
	}
};

