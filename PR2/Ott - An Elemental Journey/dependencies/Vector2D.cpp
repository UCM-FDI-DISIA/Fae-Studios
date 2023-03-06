#include "Vector2D.h"
#include <math.h>
#include "../checkML.h"

//Esta clase no ha sido comentada ya que ha sido proporcionada en los apuntes

Vector2D::Vector2D(double x, double y)
{
    _x = x;
    _y = y;
}

double Vector2D::getX() const
{
    return _x;
}

double Vector2D::getY() const
{
    return _y;
}

double Vector2D::modulus() const
{
    return sqrt(pow(_x, 2) + pow(_y, 2));
}

void Vector2D::normalize()
{
    double modulo = modulus();
    if(modulo > 0.0) {
        _x = (1.0 * _x) / (1.0 * modulo);
        _y = (1.0 * _y) / (1.0 * modulo);
    }
}

Vector2D Vector2D::operator+(const Vector2D& other) const
{
    Vector2D nuevo;
    nuevo._x = _x + other._x;
    nuevo._y = _y + other._y;
    return nuevo;
}

Vector2D Vector2D::operator*(double other) const {
    Vector2D nuevo;
    nuevo._x = _x * other;
    nuevo._y = _y * other;
    return nuevo;
}
bool Vector2D::operator==(const Vector2D& other) const
{
    return _x == other.getX() && _y == other.getY();
}


Vector2D Vector2D::operator-(const Vector2D& other) const
{
    Vector2D nuevo;
    nuevo = *this + other*double(-1);
    return nuevo;
}

double Vector2D::operator*(const Vector2D &other) const {
    return this->_x * other._x + this->_y * other._y;
}

Vector2D operator*(double num, const Vector2D& vector) {
    Vector2D nuevo = vector * num;
    return nuevo;
}