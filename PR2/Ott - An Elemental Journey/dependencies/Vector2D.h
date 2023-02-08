#pragma once
#ifndef PROYECTOSSDL_VECTOR2D_H
#define PROYECTOSSDL_VECTOR2D_H

/// Clase que añade vectores a nuestro juego (clase proporcionada en los apuntes)
class Vector2D {
private:
    double _x; ///< Coordenada en el eje OX
    double _y; ///< Coordenada en el eje OY

    /// Calcula el módulo del vector
    /// \return Un número decimal con el módulo del vector
    double modulus() const;

public:
    /// Constructora de la clase vector
    /// \param x Coordenada en el eje OX
    /// \param y Coordenada en el eje OY
    Vector2D(double x = 0, double y = 0);

    /// Devuelve la coordenada en el eje OX del vector
    /// \return Número decimal con la coordenada en el eje OX
    double getX() const;

    /// Devuelve la coordenada en el eje OY del vector
    /// \return Número decimal con la coordenada en el eje OY
    double getY() const;

    /// Normaliza un vector dado
    void normalize();

    /// Suma de dos vectores
    /// \param other Vector2D
    /// \return Un Vector2D con la suma de los dos vectores
    Vector2D operator+(const Vector2D& other) const;

    /// Resta de dos vectores
    /// \param other Vector2D
    /// \return Un Vector2D con la resta de los dos vectores
    Vector2D operator-(const Vector2D& other) const;

    /// Producto de un vector por un escalar
    /// \param other Número decimal
    /// \return Un Vector2D con el producto de un vector por un escalar
    Vector2D operator*(double other) const;

    /// Producto escalar de dos vectores
    /// \param other Vector2D
    /// \return Un número decimal con el producto escalar de dos vectores
    double operator*(const Vector2D& other) const;

    /// Producto de un vector por un escalar (para poder hacer num * Vector en lugar de solo Vector * num)
    /// \param num Número decimal
    /// \param vector Vector2D
    /// \return Un Vector2D con el producto de un vector por un escalar
    friend Vector2D operator*(double num, const Vector2D& vector);
};

#endif //PROYECTOSSDL_VECTOR2D_H

