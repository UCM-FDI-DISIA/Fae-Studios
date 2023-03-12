#include "Image.h"
#include "../ecs/Entity.h"
void Image::render() {
	auto uwu = transform->getRect();
	if (cam != nullptr) {
		auto camera = cam->camera;
		uwu.x -= camera.x;
		uwu.y -= camera.y;
	}

	texture->render(uwu);
}

void Image::initComponent() {
	transform = ent_->getComponent<Transform>();
	auto camera = mngr_->getCamera();
	if (camera != nullptr) {
		cam = mngr_->getCamera()->getComponent<CameraComponent>();
	}
	else cam = nullptr;
}
