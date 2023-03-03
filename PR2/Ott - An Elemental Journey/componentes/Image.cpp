#include "Image.h"

Image::Image(Texture* text) : tr_(nullptr), tex_(text), Component()
{
}

void Image::initComponent()
{
	tr_ = ent_->getComponent<Transform>();
}

void Image::render()
{ 
	SDL_Rect dest; dest.x = tr_->getPos().getX(); dest.y = tr_->getPos().getY();
	dest.w = tr_->getW(); dest.h = tr_->getH();
	auto cam = mngr_->getCamera()->getComponent<CameraComponent>()->camera;
	dest = { dest.x - cam.x, dest.y - cam.y, dest.w, dest.h };
	tex_->render(dest);
}

Image::~Image()
{
}
