#pragma once
#ifndef TPV2_FRAMEDIMAGE_H
#define TPV2_FRAMEDIMAGE_H

#include "../ecs/Component.h"
#include "Transform.h"

class FramedImage : public Component {
private:
    Texture* texture;
    Transform* transform;
    int totalRows, totalCols; //Columnas y filas totales de la imagen
    int currentRow, currentCol; //Fila y columna que actualmente se renderiza
    SDL_Rect getRect() const;
public:
    constexpr static ecs::cmpId_type id = ecs::_IMAGE;
    FramedImage(Texture* texture, int rows, int cols) : Component(), texture(texture), totalRows(rows), totalCols(cols) {
        transform = nullptr;
        currentRow = 0;
        currentCol = 0;
    }
    virtual ~FramedImage() = default;
    void initComponent() override;
    void render() override;
    void setRow(int row) {currentRow = row;}
    void setCol(int col) {currentCol = col;}
    int getFullWidth() const {return texture->width();}
    int getFullHeight() const {return texture->height();}
    int getFrameWidth() const {return texture->width() / totalCols;}
    int getFrameHeight() const {return texture->height() / totalRows;}
};


#endif //TPV2_FRAMEDIMAGE_H
