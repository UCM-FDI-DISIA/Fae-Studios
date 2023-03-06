#pragma once
#include "../ecs/Component.h"
#include "../utils/Vector2D.h"
#include "../sdlutils/Texture.h"
class Transform : public Component
{
private:
	Vector2D position;
	Vector2D velocity;
	float rotation;
	float width;
	float height;

public:
	constexpr static ecs::cmpId_type id = ecs::_TRANSFORM;
	Transform(Vector2D p, Vector2D v, float w, float h, float r = 0.0f) : Component() {
		mngr_ = nullptr;
		ent_ = nullptr;
		position = p;
		velocity = v;
		rotation = r;
		width = w;
		height = h;
	};
	virtual ~Transform() = default;
	inline float getRotation() const { return rotation; };
	inline void setRotation(float r) { rotation += r; };
	void update() override;
	inline Vector2D getPosition() const { return position; };
	inline void setPosition(Vector2D newPos) { position = newPos; };
	inline Vector2D getVelocity() const { return velocity; };
	inline void setVelocity(Vector2D v) { velocity = v; };
	inline float getWidth() const { return width; };
	inline float getHeight() const { return height; };
};

