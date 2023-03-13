#include "Image.h"
#include "../ecs/Entity.h"
#include "../states/GameStateMachine.h"
#include "../states/PlayState.h"

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
	if (ent_->hasComponent<CameraComponent>()) {
		cam = static_cast<PlayState*>(GameStateMachine::instance()->getPlayState())->getCamera()->getComponent<CameraComponent>();
	}
	else cam = nullptr;
}
