#include <iostream>
#include "number1.h"

int main()
{
    int start, end;
    std::cin >> start >> end;
    uint64_t ans = how_one_in_cons(start, end);
    std::cout << ans << std::endl;
    return 0;
}
