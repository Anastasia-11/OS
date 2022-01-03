#ifndef OS_LAB1_VECTOR_H
#define OS_LAB1_VECTOR_H

#include "Number.h"

class Vector {
public:
    Vector();
    Vector(const Number& a, const Number& b);

    const Number &getX() const;
    const Number &getY() const;

    Number getR() const;
    Number getPhi() const;

    void setX(const Number &x);
    void setY(const Number &y);

    Vector operator+(const Vector& vector) const;
    Vector operator-(const Vector& vector) const;

    friend std::ostream& operator<<(std::ostream& out, const Vector& vector);

private:
    Number x;
    Number y;
};


#endif //OS_LAB1_VECTOR_H
