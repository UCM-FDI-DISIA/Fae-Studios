#pragma once
#ifndef PROYECTOSSDL_FONT_H
#define PROYECTOSSDL_FONT_H

#include <SDL_ttf.h>
#include <string>

/// Clase que incopora soporte para las fuentes TrueType
class Font {
private:
    TTF_Font* font = nullptr; ///< Fuente
public:
    /// Constructora por defecto de Font
    Font() {};

    /// Constructora de Font
    /// \param filename Archivo que contiene la fuente
    /// \param size Tamaño en píxeles de la fuente
    Font(std::string filename, int size) { load(filename, size); };

    /// Destructora por defecto de Font
    ~Font() {libera();}

    /// Carga (crea) una fuente
    /// \param filename Archivo de la fuente
    /// \param size Tamaño de la fuente en píxeles
    /// \return Un booleano indicando si la textura se ha cargado correctamente, o en su defecto una excepción
    bool load(std::string filename, int size);

    /// Libera la fuente creada
    void libera();

    /// Genera una SDL_Surface a partir de una fuente
    /// \param text Texto a generar por la fuente
    /// \param color Color del texto
    /// \return Puntero a SDL_Surface con el texto impreso en la fuente
    SDL_Surface* generateSurface(std::string text, SDL_Color color) const;
};

#endif //PROYECTOSSDL_FONT_H
