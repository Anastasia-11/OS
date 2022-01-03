#include <iostream>
#include "constants.h"

int main() {
    int num;

    while(std::cin >> num && num != END) {
        std::cout << num + NUM << ' ';
    }
    std::cout << END;

    return 0;
}