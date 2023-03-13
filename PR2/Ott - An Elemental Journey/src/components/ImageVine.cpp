#include "ImageVine.h"
#include "CameraComponent.h"
#include <vector>
#include "../states/PlayState.h"
#include "../states/GameStateMachine.h"

void ImageVine::initComponent() {
	tr_ = ent_->getComponent<Transform>();
}

void ImageVine::render()
{
	//Cogemos las medidas del SDL_Rect del Transform
	destTransform.x = tr_->getPosition().getX(); destTransform.y = tr_->getPosition().getY();
	destTransform.w = tr_->getWidth(); destTransform.h = tr_->getHeight();

	//Cogemos las medidas de la textura
	destTexture.h = tex_->height(); destTexture.w = tex_->width();

	auto cam = mngr_->getCamera()->getComponent<CameraComponent>()->camera;
	destTransform = { destTransform.x - cam.x, destTransform.y - cam.y, destTransform.w, destTransform.h };

	float i = (destTransform.h / (destTexture.h*2)) + 1;
	std::vector<SDL_Rect> anidatedVines;
	SDL_Rect aux = destTransform;
	aux.h = destTexture.h*2;
	aux.w = destTexture.w*2;
	anidatedVines.push_back(aux);

	for (int j = 1; j < i; ++j) {
		aux.y += (destTexture.h*2);
		anidatedVines.push_back(aux);
	}

	for (int j = 0; j < i; ++j) {
		tex_->render(anidatedVines[j]);
	}
}
