#include "ImageVine.h"
#include "CameraComponent.h"
#include <vector>
#include "../states/PlayState.h"
#include "../states/GameStateMachine.h"
ImageVine::ImageVine(Texture* text, float rot, bool canClimb) :tr_(nullptr), tex_(text), rotation(rot) {
    //Rotation 0 es vertical y 1 horizontal
    canClimb_ = canClimb;
}

void ImageVine::initComponent()
{
    tr_ = ent_->getComponent<Transform>();
    grow_ = ent_->getComponent<GrowVine>();
    assert(grow_ != nullptr);
}

void ImageVine::render()
{
    if (tr_ != nullptr) {
        //Cogemos las medidas del SDL_Rect del Transform
        destTransform.x = tr_->getPosition().getX(); destTransform.y = tr_->getPosition().getY();
        destTransform.w = tr_->getWidth(); destTransform.h = tr_->getHeight();

        //Cogemos las medidas de la textura
        destTexture.h = tex_->height(); destTexture.w = tex_->width();

        if (initialPos.w == 0) {
            initialPos = destTransform;
        }
        auto cam = mngr_->getCamera()->getComponent<CameraComponent>()->camera;
        SDL_Rect actualInitialPos = initialPos;
        actualInitialPos.x -= cam.x;
        actualInitialPos.y -= cam.y;
        destTransform = { destTransform.x - cam.x, destTransform.y - cam.y, destTransform.w, destTransform.h };
        float i = (destTransform.h / (destTexture.h * 2)) + 1;
        std::vector<std::pair<SDL_Rect, SDL_Rect>> anidatedVines;
        SDL_Rect aux = destTransform;
        destTexture.x = 0;
        aux.h = destTexture.h * 2;
        aux.w = destTexture.w * 2;
        
        if (!grow_->getUngrow()) {
            if (rotation == 0) {
                for (int j = 0; j < i; ++j) {
                    if (actualInitialPos.y > aux.y) {
                        if (actualInitialPos.y <= aux.y +aux.h) {
                            destTexture.y = tex_->height() - abs((actualInitialPos.y - aux.y))/2;
                            destTexture.h = tex_->height() - destTexture.y;
                        }
                        else { 
                            destTexture.y = 0; 
                            destTexture.h = tex_->height();
                        }
                        aux.h = destTexture.h * 2;
                        anidatedVines.push_back({ destTexture, aux });
                    }
                    aux.y += (tex_->height() * 2);
                }
            
                for (int j = 0; j < anidatedVines.size(); ++j) {
                    SDL_Rect rect = anidatedVines[j].second;
                    tex_->render(anidatedVines[j].first, rect, 0);
                }

            }
            else {
                for (int j = 0; j < i; ++j) {
                    anidatedVines.push_back({ destTexture,aux });
                    aux.x += (destTexture.w * 2);
                }
                for (int j = 0; j < anidatedVines.size(); ++j) {
                    tex_->renderFrame(anidatedVines[j].second, 0, 0);
                }
            }
        }
        else {
            if (rotation == 0) {
                for (int j = i; j > 0; --j) {
                    actualInitialPos.y = aux.y + tex_->height() * 2;
                    if (actualInitialPos.y > aux.y) {
                        destTexture.y = 0;
                        destTexture.h = tex_->height();
                        aux.h = destTexture.h * 2;
                        anidatedVines.push_back({ destTexture, aux });
                    }
                    aux.y += (tex_->height() * 2);
                    std::cout << aux.y << std::endl;
                }

                for (int j = 0; j < anidatedVines.size(); ++j) {
                    SDL_Rect rect = anidatedVines[j].second;
                    tex_->render(anidatedVines[j].first, rect, 0);
                }
            }
        }
    }
}

ImageVine::~ImageVine()
{
}