#include <iostream>
#include <cmath>
#include "constants.h"

int main() {
    int num;

    while(std::cin >> num && num != END) {
        std::cout << std::pow(num, 3) << ' ';
    }
    std::cout << END;
    return 0;
}