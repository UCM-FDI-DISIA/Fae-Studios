#pragma once
#ifndef PROYECTOSSDL_TEXT_H
#define PROYECTOSSDL_TEXT_H

#include "../dependencies/Font.h"
#include "UIElement.h"
#include <string>

/// Clase que se encarga de generar un texto, usando una textura generada a partir de la clase Font y Texture
class UIText : public UIElement {
public:
    /// Constructora de la clase Text
    UIText(const std::string& text, const Font& f, const Vector2D& position, SDL_Renderer* renderer, const SDL_Color& c = {255,255,255}, const Scale& scale = Scale(1.0f, 1.0f)) :
            UIElement(position, new Texture(renderer, text, f, c), scale) {};

    ~UIText() override { delete texture; }

    Texture* getTexture() const { return texture; };

    void movePosition(const Vector2D& newPos);
};

#endif //PROYECTOSSDL_TEXT_H
