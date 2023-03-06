#include "../utils/checkML.h"
#include "Text.h"
#include "../sdlutils/SDLUtils.h"
#include "../ecs/Entity.h"

Text::Text(std::string text, Font& f, SDL_Color fontColor, SDL_Color bgColor) {
    x = 0;
    y = 0;

    //Mac renderiza el texto de diferente manera que Windows, por tanto hacemos esa distinción aquí
#ifdef __APPLE__
    textTexture = new Texture(sdlutils().renderer(), text, f, fontColor, bgColor);
#endif

#ifdef __WINDOWS__
    if (bgColor.a <= 1) textTexture = new Texture(sdlutils().renderer(), text, f, fontColor);
    else textTexture = new Texture(sdlutils().renderer(), text, f, fontColor, bgColor);
#endif
}

void Text::render() {
    textTexture->render(x, y);
}

