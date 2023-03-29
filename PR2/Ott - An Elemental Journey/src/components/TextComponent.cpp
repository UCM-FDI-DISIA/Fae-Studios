#include "../utils/checkML.h"
#include "TextComponent.h"
#include "../sdlutils/SDLUtils.h"
#include "../ecs/Entity.h"

TextComponent::TextComponent(std::string text, Font& f, SDL_Color fontColor, SDL_Color bgColor) : text(text), f(f), fontColor(fontColor), bgColor(bgColor) {
    x = 0;
    y = 0;

    textTexture = createTexture(this->text, this->f, this->fontColor, this->bgColor);
}

Texture* TextComponent::createTexture(std::string text, Font& f, SDL_Color fontColor, SDL_Color bgColor) {
    //Mac renderiza el texto de diferente manera que Windows, por tanto hacemos esa distinción aquí
#ifdef __APPLE__
    return new Texture(sdlutils().renderer(), text, f, fontColor, bgColor);
#endif

#ifdef __WINDOWS__
    if (bgColor.a <= 1) return new Texture(sdlutils().renderer(), text, f, fontColor);
    else return new Texture(sdlutils().renderer(), text, f, fontColor, bgColor);
#endif
}

void TextComponent::render() {
    textTexture->render(x, y);
}

void TextComponent::changeText(std::string text){
    delete textTexture;
    this->text = text;
    textTexture = createTexture(this->text, this->f, this->fontColor, this->bgColor);
}

void TextComponent::changeColor(SDL_Color c) {
    delete textTexture;
    this->fontColor = c;
    textTexture = createTexture(this->text, this->f, this->fontColor, this->bgColor);
}

