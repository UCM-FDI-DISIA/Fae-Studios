#pragma once
#ifndef TPV2_FRAMEDIMAGE_H
#define TPV2_FRAMEDIMAGE_H

#include "../ecs/Component.h"
#include "Transform.h"

const float ANIM_TIME = 50;

class FramedImage : public Component {
private:
    Texture* texture;
    Transform* transform;
    int totalRows, totalCols; //Columnas y filas totales de la imagen
    int currentRow, currentCol; //Fila y columna que actualmente se renderiza
    float animTime;

    SDL_Rect getRect() const;
public:
    constexpr static ecs::cmpId_type id = ecs::_IMAGE;
    FramedImage(Texture* texture, int rows, int cols) : Component(), texture(texture), totalRows(rows), totalCols(cols) {
        transform = nullptr;
        animTime = 0;
    }
    virtual ~FramedImage() = default;
    void initComponent() override;
    void render() override;
    void update() override;
};


#endif //TPV2_FRAMEDIMAGE_H
