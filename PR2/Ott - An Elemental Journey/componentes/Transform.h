#pragma once
#include "Component.h"
#include "../dependencies/Vector2D.h"

#include <iostream>
#include <SDL.h>
class Transform : public Component {
public:
	Transform();
	Transform(Vector2D pos, float w, float h);
	Transform(float x, float y, float w, float h);
	virtual ~Transform();
	inline Vector2D& getPos() { return position_; }
	inline float& getW() { return width_; }
	inline float& getH() { return height_; }
	inline float& getRotation() { return rotation_; }
	inline SDL_Rect& getRect() {
		SDL_Rect result; result.x = position_.getX(); result.y = position_.getY(); result.w = width_; result.h = height_;
		return result;
	}
	virtual void initComponent();
	virtual void update();
	virtual void render(); 
	constexpr static cmpId_type id = ecs::_TRANSFORM;
private:
	Vector2D position_;
	float width_;
	float height_;
	float rotation_;
};

