#include <iostream>
#include "constants.h"

int main() {
    int num;
    long sum = 0;

    while(std::cin >> num && num != END) {
        sum += num;
    }
    std::cout << "sum: " << sum << '\n';
    return 0;
}
