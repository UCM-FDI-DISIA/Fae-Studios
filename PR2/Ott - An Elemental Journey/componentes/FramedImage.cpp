#include "FramedImage.h"


FramedImage::FramedImage(Texture* text, int r, int c) : tex_(text), numRows_(r), numCols_(c), tPerFrame(120)
{
}

FramedImage::FramedImage(Texture* text, int r, int c, int f) : tex_(text), numRows_(r), numCols_(c), tPerFrame(f)
{
}
FramedImage::FramedImage() : numRows_(9), numCols_(8)
{
	
}
void FramedImage::initComponent()
{
	if(tex_ == nullptr) tex_ = mngr_->getTexture(0);
	tr_ = ent_->getComponent<Transform>();
	shieldTex_ = mngr_->getTexture(4);
}

void FramedImage::render()
{
	SDL_Rect dest; dest.x = tr_->getPos().getX(); dest.y = tr_->getPos().getY();
	dest.w = tr_->getW(); dest.h = tr_->getH();
	if (ent_->hasComponent<PlayerAnimationComponent>()) {
		PlayerAnimationComponent* pAnim = ent_->getComponent<PlayerAnimationComponent>();
		bool lookRight = ent_->getComponent<PhysicsComponent>()->getLookDirection();
		SDL_RendererFlip flip = SDL_FLIP_NONE;
		if (!lookRight) flip = SDL_FLIP_HORIZONTAL;
		int state = pAnim->getState();
		if (col == (pAnim->getNFrames(state) - 1) && (SDL_GetTicks() / pAnim->getTPerFrame(state)) % pAnim->getNFrames(state) == 0) pAnim->endAnim();
		switch (state)
		{
		case IDLE: col = (SDL_GetTicks() / pAnim->getTPerFrame(IDLE)) % pAnim->getNFrames(IDLE); tex_->renderFrame(dest, pAnim->getRowNum(IDLE), col, 0, flip); break;
		case WALK: col = (SDL_GetTicks() / pAnim->getTPerFrame(WALK)) % pAnim->getNFrames(WALK); tex_->renderFrame(dest, pAnim->getRowNum(WALK), col, 0, flip); break;
		case RUN: col = (SDL_GetTicks() / pAnim->getTPerFrame(RUN)) % pAnim->getNFrames(RUN); tex_->renderFrame(dest, pAnim->getRowNum(RUN), col, 0, flip); break;
		case JUMP_UP: col = (SDL_GetTicks() / pAnim->getTPerFrame(JUMP_UP)) % pAnim->getNFrames(JUMP_UP); tex_->renderFrame(dest, pAnim->getRowNum(JUMP_UP), col, 0, flip); break;
		case PEAK: tex_->renderFrame(dest, pAnim->getRowNum(PEAK), 4, 0, flip); break;
		case FALL: tex_->renderFrame(dest, pAnim->getRowNum(FALL), 5, 0, flip); break;
		case LAND: col = ((SDL_GetTicks() / pAnim->getTPerFrame(LAND))+ 6)% pAnim->getNFrames(LAND) + 6; tex_->renderFrame(dest, pAnim->getRowNum(LAND), col, 0, flip); break;
		case VANISH: col = (SDL_GetTicks() / pAnim->getTPerFrame(VANISH)) % pAnim->getNFrames(VANISH); tex_->renderFrame(dest, pAnim->getRowNum(VANISH), col, 0, flip); break;
		case DIE: col = (SDL_GetTicks() / pAnim->getTPerFrame(DIE)) % pAnim->getNFrames(DIE); tex_->renderFrame(dest, pAnim->getRowNum(DIE), col, 0, flip); break;
		case ATTACK: col = (SDL_GetTicks() / pAnim->getTPerFrame(ATTACK)) % pAnim->getNFrames(ATTACK); tex_->renderFrame(dest, pAnim->getRowNum(ATTACK), col, 0, flip); break;
		default:
			
			break;
		}
	}
	if (isShielded) shieldTex_->render(tr_->getRect());
	//tex_->renderFrame(dest, row, col);
	//row = (SDL_GetTicks() / tPerFrame) % numRows_; col = (SDL_GetTicks() / tPerFrame) % numCols_;
}

void FramedImage::elementChanged(int newElem)
{
	tex_ = mngr_->getTexture(newElem);
}

FramedImage::~FramedImage()
{

}

