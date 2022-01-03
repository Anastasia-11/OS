#include <iostream>
#include "constants.h"

int main() {
    int num;

    while(std::cin >> num && num != END) {
        std::cout << num * 7 << ' ';
    }
    std::cout << END;
    return 0;
}