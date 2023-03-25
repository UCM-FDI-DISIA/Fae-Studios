//LIMPIO

#pragma once
#include "../ecs/Component.h"
#include "../utils/Vector2D.h"
#include "Transform.h"
#include "../ecs/Entity.h"
#include "../ecs/Manager.h"
#include "../sdlutils/SDLUtils.h"


class CameraComponent : public Component {
private:
	Transform* playerTrnf_;
	Transform* tr_;
	bool camerashake = false;
	int timer;
	bool left = false;
	bool right = true;
	SDL_Rect bounds;

public:
	constexpr static ecs::cmpId_type id = ecs::_CAMERA;
	SDL_Rect camera;

	CameraComponent() : Component(), playerTrnf_(nullptr), tr_(nullptr), camera({0,0,0,0}) {}
	
	inline void setPos(Vector2D newPos) {
		float x = newPos.getX() - sdlutils().width() / 2;
		float y = newPos.getY() - sdlutils().height() / 2;
		tr_->setPosition(Vector2D(x,y));
	}
	virtual void initComponent();
	virtual void update();
	inline void cameraShake(bool n) {
		camerashake = n;
	}
	inline void setBounds(const SDL_Rect& b) { bounds = b; }

};

