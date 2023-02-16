#pragma once
#ifndef PROYECTOS2_BUTTON_H
#define PROYECTOS2_BUTTON_H

#include "UIElement.h"
#include "UIText.h"

class SDLApplication; //Declaramos aquí una clase game auxiliar para romper las dependencias circulares que puedan surgir

using CallBack = void (SDLApplication* app); //Declaramos el callback de los botones

struct ButtonParams {
    Vector2D position;
    std::string buttonText; 
    Texture* texture; 
    SDLApplication* app; 
    CallBack* callback; 
    Scale scale;
    Scale textScale;
    SDL_Color textCol;

    ButtonParams(const Vector2D& position, const std::string& buttonText, Texture* texture, SDLApplication* app, CallBack* callback,
        const Scale& scale = Scale(1.0f, 1.0f), const Scale& textScale = Scale(2.0f, 2.0f), const SDL_Color& textCol = { 255,255,255 }) :
        position(position), buttonText(buttonText), texture(texture), app(app), callback(callback), scale(scale), textScale(textScale),
        textCol(textCol) {}

};

/// Clase abstracta que se encargará servir como base para los botones que podamos tener en pantalla
class Button : public UIElement {
protected:
    /// Estados en los que puede estar la textura de un botón
    enum button_State {MOUSE_OUT = 0, MOUSE_OVER = 1, CLICKED = 2};

    std::string buttonText; ///< Texto contenido en el botón
    UIText* text = nullptr; ///< Texto del botón renderizado en pantalla
    SDLApplication* app = nullptr; ///< Puntero a la clase Game
    int currentButtonFrame = MOUSE_OUT; ///< Estado actual en que se encuentra el botón
    CallBack* callback = nullptr; ///< Puntero a una función void con un parámetro Game*
    Scale textScale;

    /// Método que se ejecuta cuando clicamos en el botón
    void onClick();

public:
    /// Constructora de la clase Button
    /// \param position Posición del botón en pantalla
    /// \param texture Textura del botón
    /// \param game Puntero a la clase Game
    /// \param callback Función que se ejecutará cuando pulsemos el botón
    /// \param scale Tamaño en el que se quiere escalar el botón
    Button(const ButtonParams& params);

    /// Destructora de la clase Button
    ~Button() override;

    /// Renderiza el botón en pantalla en sus 3 estados
    virtual void render(const SDL_Rect& camera = { 0,0,0,0 }) const;

    /// Manejo de eventos, principalmente el pulsar el botón
    /// \param e SDL_Event con el evento detectado en Game
    void handleEvents(const SDL_Event& e) override;
};

enum ImageClass { FULL_IMAGE, SPRITESHEET };

class ImageButton : public Button {
private:
    Texture* image = nullptr;
    SDL_Rect imagePos;
    ImageClass imgClass;
    uint row;
    uint col;

public:
    ImageButton(const ButtonParams& params, Texture* image, ImageClass imgClass, uint row = 0, uint col = 0);

    void render(const SDL_Rect& camera = { 0,0,0,0 }) const final;

    void handleEvents(const SDL_Event& e) final;
};

#endif //PROYECTOS2_BUTTON_H
