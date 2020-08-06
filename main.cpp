#include <iostream>
#include "VLVector.hpp"
#include <algorithm>
int main()
{
    VLVector<int> v;
    v.push_back(1);
    v.push_back(2);
//    auto iter = v.begin();
//    std::cerr << *iter << '\n';
//    *iter = 3;
//    std::cerr << *iter << '\n';
    for(auto it = v.cbegin(); it != v.cend(); ++it)
    {
        std::cerr << *it << '\n';
    }



//    std::shared_ptr<int> a = std::shared_ptr<int>(new int[5], [&](int *p){delete [] p;});
//    for (int i = 0; i < 5; ++i)
//    {
//        a.get()[i] = i+1;
//    }
//    for (int i = 0; i < 5; ++i)
//    {
//        std::cerr << a.get()[i] << '\n';
//    }
//    std::cerr << "------------------------------\n";
//    int *b = a.get();
//    for (int i = 0; i < 5; ++i)
//    {
//        std::cerr << b[i] << '\n';
//    }
    return 0;
}
