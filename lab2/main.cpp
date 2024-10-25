#include <iostream>
#include "Six.h"

int main() {
    Six first(1, 4);
    Six second("4");
    second.print(std::cout) << " ";
    first.print(std::cout) << std::endl;
    std::cout<< first.equal(second) << std::endl;
    return 0;
}
