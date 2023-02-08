#include "Texture.h"
#include <iostream>
#include "Exceptions.h"
#include "../checkML.h"

using namespace std;

//Esta clase no ha sido comentada ya que ha sido proporcionada en los apuntes

void Texture::libera() {
    SDL_DestroyTexture(texture);
    texture = nullptr;
    w = h = 0;
}

void Texture::load(string filename, uint nRows, uint nCols) {
    SDL_Surface* tempSurface = IMG_Load(filename.c_str());
    if (tempSurface == nullptr) throw SDLError("Error at loading image");
    libera();
    texture = SDL_CreateTextureFromSurface(renderer, tempSurface);
    if (texture == nullptr) throw SDLError("Error at loading image");
    numRows = nRows;
    numCols = nCols;
    w = tempSurface->w;
    h = tempSurface->h;
    fw = w / numCols;
    fh = h / numRows;
    SDL_FreeSurface(tempSurface);
}

void Texture::render(const SDL_Rect& destRect, SDL_RendererFlip flip) const {
    SDL_Rect srcRect;
    srcRect.x = 0; srcRect.y = 0;
    srcRect.w = w; srcRect.h = h;
    SDL_RenderCopyEx(renderer, texture, &srcRect, &destRect, 0, 0, flip);
}

void Texture::renderFrame(const SDL_Rect& destRect, int row, int col, int angle, SDL_RendererFlip flip) const {
    SDL_Rect srcRect;
    srcRect.x = fw * col;
    srcRect.y = fh * row;
    srcRect.w = fw;
    srcRect.h = fh;
    SDL_RenderCopyEx(renderer, texture, &srcRect, &destRect, angle, 0, flip);
}

void Texture::loadFromText(SDL_Renderer* renderer, std::string text, const Font& font, SDL_Color color) {
    SDL_Surface* textSurface = font.generateSurface(text, color);
    if (textSurface == nullptr) {
        throw SDLError("Unable to render text surface: " + std::string(TTF_GetError()));
    }
    else {
        libera();
        texture = SDL_CreateTextureFromSurface(renderer, textSurface); if (texture == nullptr) {
            throw SDLError("Unable to create texture from text: " + std::string(SDL_GetError()));
            w = h = 0;
        }
        else {
            w = textSurface->w;
            h = textSurface->h;
        }
        SDL_FreeSurface(textSurface);
    }
}