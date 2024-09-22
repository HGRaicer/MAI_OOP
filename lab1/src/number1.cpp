#include <iostream>
#include <climits>
#include "number1.h"


void Error_Arg(int start, int end) {
    if (start < 0 || end < 0 || start > end) {
        throw std::invalid_argument("Invalid arguments entered(must be start < end and start > 0 and end > 0)");
    }
}

void ErrorAns_type(int ans) {
    if (ans == INT_MAX) {
        throw std::overflow_error("Integer type overflowed(Answer is too big)");
    }
}
int how_one(int numb) {
    int ans = 0;
    while (numb != 0) {
        if (numb % 2 == 1) {
            ErrorAns_type(ans);
            ++ans;
        }
        numb>>=1;
    }
    return ans;
}

int how_one_in_cons(int start, int end) {
    Error_Arg(start, end);
    int ans = 0;
    for (int i = start; i <= end; ++i) {
        ErrorAns_type(ans);
        ans +=how_one(i);
    }
    return ans;
}