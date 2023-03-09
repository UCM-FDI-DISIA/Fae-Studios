#include "BackgroundImage.h"
BackgroundImage::BackgroundImage(Vector2D pos, Texture* text, int wS, int hS) : position(pos), tex_(text),wScale(wS), hScale(hS), Component()
{
}

void BackgroundImage::initComponent()
{

}

void BackgroundImage::render()
{
	SDL_Rect dest; dest.x = position.getX(); dest.y = position.getY();
	dest.w = tex_->width() / tex_->getNumCols() * wScale;
	dest.h = tex_->height() / tex_->getNumRows() * hScale;
	tex_->render(dest);
}

BackgroundImage::~BackgroundImage()
{
}
