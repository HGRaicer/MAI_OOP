#include <iostream>
#include "number1.h"

int main()
{
    int start, end;
    std::cin >> start >> end;
    int ans = how_one_in_cons(start, end);
    std::cout << ans << std::endl;
    return 0;
}
