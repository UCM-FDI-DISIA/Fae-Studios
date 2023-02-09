#pragma once

#include "UIElement.h"
#include "Text.h"

class SDLApplication; //Declaramos aquí una clase game auxiliar para romper las dependencias circulares que puedan surgir
using SliderCallBack = void(int value, SDLApplication* app); //Declaramos el callback de los sliders

const int MAX_VALUE = 100;
const int MIN_VALUE = 0;

class Slider : public UIElement {
private:
    /// Estados en los que puede estar la textura de un slider
    enum slider_State { MOUSE_OUT = 0, MOUSE_OVER = 1, CLICKED = 2 };

    class SliderNeedle : public UIElement {
    private:
        Vector2D initialPos;
    public:
        int currentSliderNeedleFrame = MOUSE_OUT;
        SliderNeedle(const Vector2D& position, const Vector2D& initialPos, Texture* texture, const Scale& scale = Scale(1.0f, 1.0f)) : UIElement(position, texture, scale), initialPos(initialPos) {}
        void render() const final;
        int move();
    };

    bool showValue = true; ///< Indica si queremos o no mostrar el valor del slider dentro de este
    
    SDLApplication* app = nullptr; ///< Puntero a la clase SDLApplication
    SliderNeedle* needle = nullptr; ///< Aguja del slider
    std::string sliderText; ///< Texto contenido en el slider
    Text* textValue = nullptr; ///< Valor del slider renderizado en pantalla
    int currentSliderFrame = MOUSE_OUT; ///< Estado actual en que se encuentra el slider
    SliderCallBack* callback = nullptr; ///< Puntero a una función void con un parámetro SDLApplication* y un int con el valor
    int value; ///< Valor del slider
    int previousValue = MAX_VALUE; ///< Valor anterior del slider
    bool clicked = false; ///< Indica si hemos o no clicado en el slider (para detectar si arrastramos mientras pulsamos)
    
    Text* title = nullptr; ///< Título del slider
    Scale titleScale; ///< Escala del título
    SDL_Color textColor; ///< Color del título

    /// Método que se ejecuta cuando arrastramos el slider
    void onChange();

public:
    Slider(const Vector2D& position, Texture* sliderTexture, Texture* needleTexture, const std::string& sliderTitle, SDLApplication* app, 
        SliderCallBack* callback, int initialValue = 100, bool showValue = true, const Scale& sliderScale = Scale(1.0f, 1.0f), 
        const Scale& needleScale = Scale(0.125f, 0.33f), const Scale& titleScale = Scale(2.0f, 2.0f), const SDL_Color& titleColor = { 255,255,255 });

    ~Slider() override;

    void handleEvents(const SDL_Event& event) final;

    void update() final;

    void render() const final;
};

