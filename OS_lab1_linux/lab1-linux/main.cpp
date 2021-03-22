#include "Number.h"
#include "Vector.h"

int main() {
    Vector v1(Number::createNumber(13), Number::createNumber(11));
    Vector v2(Number::createNumber(35), Number::createNumber(42));
    std::cout << "v1:\n" << v1 << '\n' << "v2:\n" << v2 << '\n';
    std::cout << "sum:\n" << v1 + v2 << '\n';
    std::cout << "diff:\n" << v1 - v2 <<  '\n';
    std::cout << "v1 R: " << v1.getR() << '\n';
    std::cout << "v1 Phi: " << v1.getPhi() << '\n';
    return 0;
}
