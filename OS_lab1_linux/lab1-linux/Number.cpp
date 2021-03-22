#include <cmath>
#include "Number.h"

Number::Number() : value(0) {}

Number::Number(const Number &number) {
    this->value = number.value;
}

Number::Number(const int& val) : value(val) {}

Number::Number(const unsigned int& val) : value(val) {}

Number::Number(const short& val) : value(val) {}

Number::Number(const unsigned short& val) : value(val) {}

Number::Number(const long& val) : value(val) {}

Number::Number(const unsigned long& val) : value(val) {}

Number::Number(const long long int& val) : value(val) {}

Number::Number(const unsigned long long int& val) : value(val) {}

Number::Number(const float& val) : value(val) {}

Number::Number(const double& val) : value(val) {}

Number::Number(const long double& val) : value(val) {}

long double Number::getValue() const {
    return this->value;
}

void Number::setValue(const long double& val) {
    this->value = val;
}

Number Number::operator+(const Number &number) const {
    return Number(this->getValue() + number.getValue());
}

Number Number::operator-(const Number &number) const {
    return Number(this->getValue() - number.getValue());
}

Number Number::operator*(const Number &number) const {
    return Number(this->getValue() * number.getValue());
}

Number Number::operator/(const Number &number) const {
    return Number(this->getValue() / number.getValue());
}

Number Number::createNumber(const int& val) {
    return Number(val);
}

Number Number::createNumber(const unsigned int &val) {
    return Number(val);
}

Number Number::createNumber(const short &val) {
    return Number(val);
}

Number Number::createNumber(const unsigned short &val) {
    return Number(val);
}

Number Number::createNumber(const long &val) {
    return Number(val);
}

Number Number::createNumber(const unsigned long &val) {
    return Number(val);
}

Number Number::createNumber(const long long int &val) {
    return Number(val);
}

Number Number::createNumber(const unsigned long long int &val) {
    return Number(val);
}

Number Number::createNumber(const float &val) {
    return Number(val);
}

Number Number::createNumber(const double &val) {
    return Number(val);
}

Number Number::createNumber(const long double &val) {
    return Number(val);
}

Number Number::getZeroNumber() {
    return Number(0);
}

Number Number::getOneNumber() {
    return Number(1);
}

std::ostream& operator<<(std::ostream& out, const Number& number) {
    out << number.getValue();
    return out;
}

std::istream &operator>>(std::istream &in, Number &number) {
    in >> number.value;
    return in;
}

Number Number::sqrt() const {
    return Number(std::sqrt(this->getValue()));
}
