#include "Font.h"
#include "Exceptions.h"
#include "../checkML.h"

bool Font::load(std::string filename, int size) {
    font = TTF_OpenFont(filename.c_str(), size); //Abre una fuente de un archivo de texto con un tamaño
    if (font == nullptr) throw SDLError("Error at loading font");
    else return true;
}

void Font::libera() {
    if(font != nullptr) TTF_CloseFont(font); //Libera la fuente
    font = nullptr;
}

SDL_Surface* Font::generateSurface(std::string text, SDL_Color color) const {
    return TTF_RenderUTF8_Solid(font, text.c_str(), color); //Devuelve un Surface que contiene un texto sin sombreado
}