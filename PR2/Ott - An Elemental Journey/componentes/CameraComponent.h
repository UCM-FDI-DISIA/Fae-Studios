#pragma once
#include "Component.h"
#include "../dependencies/Vector2D.h"
#include "Transform.h"
#include "../Src/Entity.h"
#include "../Src/Manager.h"


class CameraComponent : public Component
{
public:
	CameraComponent();
	virtual ~CameraComponent();
	virtual void initComponent();
	virtual void update();
	inline void camaraShake(bool n) {
		cameraShake = n;
	};
	inline void changeSize(int w, int h) {
		tr_->setWidth(w);
		tr_->setHeight(h);
	}
	constexpr static cmpId_type id = ecs::_CAMERA;
	SDL_Rect camera;
private:
	Transform* playerTrnf_;
	Transform* tr_;
	bool cameraShake = false;
	int holi;
	bool left = false;
	bool right = true;
};

