#include "Vector.h"
#include <cmath>

Vector::Vector() {
    this->x = Number(0);
    this->y = Number(0);
}

const Number &Vector::getX() const {
    return this->x;
}

const Number &Vector::getY() const {
    return this->y;
}

void Vector::setX(const Number &a) {
    Vector::x = a;
}

void Vector::setY(const Number &b) {
    Vector::y = b;
}

Vector::Vector(const Number& a, const Number& b) {
    this->x = a;
    this->y = b;
}

Number Vector::getPhi() const {
    return Number::createNumber(atan((x / y).getValue()));
}

Number Vector::getR() const {
    return (x * x + y * y).sqrt();
}

Vector Vector::operator+(const Vector &vector) const {
    return Vector(this->getX() + vector.getX(), this->getY() + vector.getY());
}

Vector Vector::operator-(const Vector &vector) const {
    return Vector(this->getX() - vector.getX(), this->getY() - vector.getY());
}

std::ostream &operator<<(std::ostream &out, const Vector &vector) {
    out << "x: " << vector.getX() << '\n' << "y: " << vector.getY() << '\n';
    return out;
}

