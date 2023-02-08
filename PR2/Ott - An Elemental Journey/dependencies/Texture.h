#pragma once
#ifndef TextureH
#define TextureH

#include "SDL.h" // Windows
#include "SDL_image.h" // Windows
#include "Font.h"

#include <string>

using namespace std;

typedef unsigned int uint;

/// Clase que se encarga del manejo, creación y renderización de las texturas en pantalla (clase proporcionada en los apuntes)
class Texture {
private:
    SDL_Texture* texture = nullptr; ///< Puntero a SDL_Texture
    SDL_Renderer* renderer = nullptr; ///< Puntero al renderer de nuestro juego
    uint w = 0; ///< Anchura de la textura
    uint h = 0; ///< Altura de la textura
    uint fw = 0; ///< Anchura del frame de la textura
    uint fh = 0; ///< Altura del frame de la textura
    uint numCols = 1; ///< Número de columnas de la textura
    uint numRows = 1; ///< Número de filas de la textura

public:
    /// Constructora vacía de la clase Texture
    /// \param r Renderer de nuestro juego
    Texture(SDL_Renderer* r) : renderer(r) {};

    /// Constructora de la clase Texture
    /// \param r Renderer de nuestro juego
    /// \param filename Ruta del archivo de la textura
    /// \param numRows Número de filas en que se divide la textura
    /// \param numCols Número de columnas en que se divide la textura
    Texture(SDL_Renderer* r, string filename, uint numRows = 1, uint numCols = 1) : renderer(r) { load(filename, numRows, numCols); };
    Texture(SDL_Renderer* r, string text, const Font& f, SDL_Color c) : renderer(r) { loadFromText(r, text, f, c);};

    /// Destructora de la clase Texture
    ~Texture() { libera(); };

    /// Destruye la textura y libera la memoria
    void libera();

    /// Devuelve la anchura de la textura
    /// \return Entero con la anchura de la textura
    int getW() const { return w; };

    /// Devuelve la altura de la textura
    /// \return Entero con la altura de la textura
    int getH() const { return h; };

    /// Devuelve el número de columnas en que se divide la textura
    /// \return Entero con el número de columnas en que se divide la textura
    uint getNumCols() const { return numCols; };

    /// Devuelve el número de filas en que se divide la textura
    /// \return Entero con el número de filas en que se divide la textura
    uint getNumRows() const { return numRows; };

    /// Devuelve un puntero a SDL_Texture con la textura que se desee
    /// \return Puntero a SDL_Texture con una textura
    SDL_Texture* getTexture() const { return texture; };

    /// Carga una textura
    /// \param filename Ruta del archivo de la textura
    /// \param numRows Número de filas en que se quiere dividir la textura
    /// \param numCols Número de columnas en que se quiere dividir la textura
    void load(string filename, uint numRows = 1, uint numCols = 1);

    /// Renderiza una textura en pantalla
    /// \param rect Rectángulo con la posición, altura y anchura con que se quiera mostrar la textura en pantalla
    /// \param flip Rotación que se le quiera dar a la textura
    void render(const SDL_Rect& rect, SDL_RendererFlip flip = SDL_FLIP_NONE) const;

    /// Dada una textura, renderiza solo una parte de ella (frame) dada la fila y la columna que se desee mostrar
    /// \param destRect Rectángulo con la posición, altura y anchura con que se quiera mostrar la textura en pantalla
    /// \param row Fila de la textura que se quiere mostrar
    /// \param col Columna de la textura que se quiere mostrar
    /// \param angle Ángulo con que se quiere mostrar la textura
    /// \param flip Rotación que se le quiere dar a la textura
    void renderFrame(const SDL_Rect& destRect, int row, int col, int angle = 0, SDL_RendererFlip flip = SDL_FLIP_NONE) const;

    void loadFromText(SDL_Renderer* renderer, string text, const Font& font, SDL_Color color);
};

#endif