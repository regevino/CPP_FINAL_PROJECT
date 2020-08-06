#include <iostream>
#include "VLVector.hpp"
#include <algorithm>
int main()
{
    VLVector<int, 4> v;
    int c = 0;
    v.push_back(c);
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    v.push_back(4);
    v.push_back(5);
    v.push_back(6);
    v.push_back(7);
    v.push_back(8);

    VLVector<int, 4> v1;
    std::cerr << (v == v1) << '\n';
    std::cerr << (v != v1) << '\n';

    VLVector<int, 4> v2;
    v1.push_back(c);
    v1.push_back(1);
    v1.push_back(2);
    v1.push_back(3);
    v1.push_back(4);
    v1.push_back(5);
    v1.push_back(6);
    v1.push_back(7);
    v1.push_back(8);

    std::cerr << (v == v1) << '\n';
    std::cerr << (v != v1) << '\n';
//    std::cerr << v.size() << '\n';
//    auto res = v.erase(v.begin());
//    if (res == v.begin())
//    {
//        std::cerr << "AAAAAAAAAAAAAA" << '\n';
//    }
//    else
//    {
//        std::cerr << "BBBBBBBBBBBBBB" << '\n';
//    }
//    std::cerr << v.size() << '\n';

//    std::cerr << v.empty() << '\n';
//
//    v.clear();
//    std::cerr << v.empty() << '\n';
//    auto iter = v.begin();
//    std::cerr << *iter << '\n';
//    *iter = 3;
//    std::cerr << *iter << '\n';
//    for(auto it = v.cbegin(); it != v.cend(); ++it)
//    {
//        std::cerr << *it << '\n';
//    }
//    v.pop_back();
//
//    for (auto &it: v)
//    {
//        std::cerr << it << '\n';
//    }
//
//    v.pop_back();
//
//    for (auto &it: v)
//    {
//        std::cerr << it << '\n';
//    }
//    std::shared_ptr<int> a = std::shared_ptr<int>(new int[5], [&](int *p){delete [] p;});
//    for (int i = 0; i < 5; ++i)
//    {
//        a.get()[i] = i+1;
//    }
//    for (int i = 0; i < (int)v.size()+1; ++i)
//    {
//        std::cerr << v[i] << '\n';
//    }
//    const char f = v.at(4);
//    std::cerr << v.at(4) << '\n';
//    std::cerr << f << '\n';
//    for (int i = 0; i < (int)v.size()+1; ++i)
//    {
//        std::cout << v.at(i) << '\n';
//    }
//    std::cerr << "------------------------------\n";
//    int *b = a.get();
//    for (int i = 0; i < 5; ++i)
//    {
//        std::cerr << b[i] << '\n';
//    }
    return 0;
}
