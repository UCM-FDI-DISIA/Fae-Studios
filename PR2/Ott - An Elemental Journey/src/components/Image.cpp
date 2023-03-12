#include "Image.h"
#include "../ecs/Entity.h"
void Image::render() {
	auto rect = transform->getRect();
	if (cam != nullptr) {
		auto camera = cam->camera;
		rect.x -= camera.x;
		rect.y -= camera.y;
	}

	texture->render(rect);
}

void Image::initComponent() {
	transform = ent_->getComponent<Transform>();
	auto camera = mngr_->getCamera();
	if (camera != nullptr) {
		cam = mngr_->getCamera()->getComponent<CameraComponent>();
	}
	else cam = nullptr;
}
