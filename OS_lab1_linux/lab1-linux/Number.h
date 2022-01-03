#pragma once
#ifndef OS_LAB1_NUMBER_H
#define OS_LAB1_NUMBER_H

#include <iostream>

class Number {
public:
    Number();
    Number(const Number& number);
    Number(const int& val);
    Number(const unsigned int& val);
    Number(const short& val);
    Number(const unsigned short& val);
    Number(const long& val);
    Number(const unsigned long& val);
    Number(const long long int& val);
    Number(const unsigned long long int& val);
    Number(const float& val);
    Number(const double& val);
    Number(const long double& val);

    Number sqrt() const;
    Number operator+(const Number& number) const;
    Number operator-(const Number& number) const;
    Number operator*(const Number& number) const;
    Number operator/(const Number& number) const;

    static Number createNumber(const int& val);
    static Number createNumber(const unsigned int& val);
    static Number createNumber(const short & val);
    static Number createNumber(const unsigned short & val);
    static Number createNumber(const long & val);
    static Number createNumber(const unsigned long& val);
    static Number createNumber(const long long int& val);
    static Number createNumber(const unsigned long long int& val);
    static Number createNumber(const float & val);
    static Number createNumber(const double & val);
    static Number createNumber(const long double& val);

    long double getValue() const;
    void setValue(const long double& val);

    static Number getOneNumber() ;
    static Number getZeroNumber() ;

    friend std::ostream& operator<<(std::ostream& out, const Number& number);
    friend std::istream& operator>>(std::istream& in, Number& number);

long double value;
};

#endif //OS_LAB1_NUMBER_H
