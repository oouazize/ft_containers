#pragma once
#include <iostream>
#include <algorithm>

namespace ft
{
    template<typename A, typename B, class Comp>
    bool compare(A a, B b, Comp u = Comp())
    { return u(a, b); }
}