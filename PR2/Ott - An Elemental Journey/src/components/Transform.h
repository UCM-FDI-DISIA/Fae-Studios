#pragma once
#include "../ecs/Component.h"
#include "../utils/Vector2D.h"
#include "../sdlutils/Texture.h"
#include "PhysicsComponent.h"
#include "../ecs/Entity.h"
class Transform : public Component
{
private:
	Vector2D position, initialPos;
	float rotation = 0.0f;
	float width;
	float height;
	float initWidth, initHeight;
	float scale = 1.0f;
	int initialRoom = 0;
	PhysicsComponent* physics_;

public:
	constexpr static ecs::cmpId_type id = ecs::_TRANSFORM;
	Transform(Vector2D p, float w, float h, float r = 0) : Component() {
		mngr_ = nullptr;
		ent_ = nullptr;
		initialPos = p;
		position = p;
		rotation = 0.0f;
		width = w;
		height = h;
		rotation = r;
		initWidth = w;
		initHeight = h;
	};
	Transform(float x, float y, float w, float h, float r = 0) : Component() {
		position = Vector2D(x, y);
		width = w;
		height = h;
		rotation = r;
	}

	Transform(SDL_Rect pos) :Component() {
		position = Vector2D(pos.x, pos.y);
		width = pos.w;
		height = pos.h;
	}
	Transform(const Vector2D& position, Texture* texture, const Vector2D& scale = Vector2D(1.0f, 1.0f),float r = 0) : Component() {

		this->position = position;
		width = texture->width() / texture->getNumCols() * scale.getX();
		height = texture->height() / texture->getNumRows() * scale.getY();
		rotation = r;
	}
	virtual ~Transform() = default;
	inline float getRotation() const { return rotation; };
	inline void setRotation(float r) { rotation += r; };
	inline Vector2D getPosition() const { return position; };
	inline Vector2D getInitialPosition() const { return initialPos; };
	inline int getInitialRoom() const { return initialRoom; };
	inline void setInitialRoom(int i) { initialRoom = i; };
	inline void setInitialPosition(Vector2D ini) { initialPos = ini; };
	inline void setPosition(Vector2D newPos) { position = newPos; };
	inline void setWidth(float w) { width = w; }
	inline void setHeight(float h) { height = h; }
	inline void setScale(float scale) { width = initWidth * scale; height = initHeight * scale; this->scale = scale; }
	inline float getScale() { return scale; }
	inline float getWidth() const { return width; };
	inline float getHeight() const { return height; };
	inline SDL_Rect& getRect() {
		SDL_Rect result; 
		result.x = position.getX(); 
		result.y = position.getY(); 
		result.w = width; 
		result.h = height;
		return result;
	}
	virtual void initComponent() {
		physics_ = ent_->getComponent<PhysicsComponent>();
	}
	virtual void update() { if (physics_ != nullptr) position = position + (physics_->getVelocity() * scale); }
};

