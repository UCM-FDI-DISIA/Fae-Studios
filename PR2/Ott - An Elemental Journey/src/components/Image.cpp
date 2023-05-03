#include "Image.h"
#include "../ecs/Entity.h"
#include "../states/GameStateMachine.h"
#include "../states/PlayState.h"

void Image::render() {
	if (allowRender_) {
		auto rect = transform->getRect();
		if (cam != nullptr) {
			auto camera = cam->camera;
			rect.x -= camera.x;
			rect.y -= camera.y;

		}
		texture->render(rect, transform->getRotation());
	}
}

void Image::initComponent() {
	transform = ent_->getComponent<Transform>();
	auto camera = mngr_->getCamera();
	if (camera != nullptr) {
		cam = camera->getComponent<CameraComponent>();
	}
	else cam = nullptr;
}
