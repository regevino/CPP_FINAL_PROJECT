#include <iostream>
#include "VLVector.hpp"
#include <algorithm>
int main()
{
    VLVector<int> v;

    int b[5] = {0};
    std::fill(b, b+5, 5);
    for (int i: b)
    {
        std::cerr << i << '\n';
    }

//    auto a = std::make_unique<int[]>(2);
//    a[0] = 1;
//    a[1] = 2;
//    std::cerr << a[0] << '\n';
//    std::cerr << a[1] << '\n';
    return 0;
}
