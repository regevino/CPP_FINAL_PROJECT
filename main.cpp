#include <iostream>
#include "VLVector.hpp"
#include <vector>
int main()
{
    VLVector<int> v;

    auto a = std::make_unique<int[]>(2);
    a[0] = 1;
    a[1] = 2;
    std::cerr << a[0] << '\n';
    std::cerr << a[1] << '\n';
    return 0;
}
