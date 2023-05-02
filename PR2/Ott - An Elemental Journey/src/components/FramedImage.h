#pragma once
#ifndef TPV2_FRAMEDIMAGE_H
#define TPV2_FRAMEDIMAGE_H

#include "../ecs/Component.h"
#include "Transform.h"
#include "PlayerAnimationComponent.h"
#include "../sdlutils/SDLUtils.h"
#include "PhysicsComponent.h"
#include "CameraComponent.h"

class FramedImage : public Component {
private:
    Texture* texture;
    Transform* transform;
    
    int totalRows, totalCols; //Columnas y filas totales de la imagen
    int currentRow, currentCol; //Fila y columna que actualmente se renderiza
    SDL_Rect getRect() const;
    CameraComponent* cam;
    PhysicsComponent* physics;
    SDL_RendererFlip flip;
public:
    constexpr static ecs::cmpId_type id = ecs::_IMAGE;
    FramedImage(Texture* texture, int rows, int cols) : Component(), texture(texture), totalRows(rows), totalCols(cols) {
        transform = nullptr;
        currentRow = 0;
        currentCol = 0;
        flip = SDL_FLIP_NONE;
    }
    virtual ~FramedImage() = default;
    void initComponent() override;
    void render() override;
    void setRow(int row) {currentRow = row;}
    void setCol(int col) {currentCol = col;}
    inline int getCurrentCol() const { return currentCol; }
    inline int getCurrentRow() const { return currentRow; }
    int getFullWidth() const {return texture->width();}
    int getFullHeight() const {return texture->height();}
    int getFrameWidth() const {return texture->width() / totalCols;}
    int getFrameHeight() const {return texture->height() / totalRows;}
    inline Texture* getTexture() { return texture; }
    inline void flipTexture(bool horizontalFlip)
    {
        if (horizontalFlip) flip = SDL_FLIP_HORIZONTAL;
        else flip = SDL_FLIP_NONE;
    }

    inline void changeTexture(Texture* t) { texture = t; }
};

class FramedImageOtt : public Component
{
public:
    FramedImageOtt(Texture* t) : tex_(t) {};
    virtual ~FramedImageOtt();
    void initComponent() override;
    void render() override;
    inline int getCurCol() { return col; }
    inline int getCurRow() { return row; }
    inline void setRow(int r) { row = r; }
    inline void setCol(int c) { col = c; }
    void hasAllRelics();
    void changeElement(ecs::elements newElem);
    inline void shielded(bool b) { isShielded = b; }
    inline void setLookingRight(bool l) { lookingRight = l; }
    inline bool getLookingRight() const { return lookingRight; }
    constexpr static ecs::cmpId_type id = ecs::_IMAGE;
private:
    Transform* tr_;
    Texture* tex_;
    CameraComponent* cam;
    PhysicsComponent* physics;
    Texture* shieldTex_;
    PlayerAnimationComponent* pAnim;
    int numRows_, numCols_;
    int row = 0, col = 0;
    int tPerFrame;
    bool isShielded = false, lookingRight = true;
    bool hasRelics = false;
};

#endif //TPV2_FRAMEDIMAGE_H
