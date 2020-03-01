#include "bar.h"
#include <iostream>
#include <libfoo/foo.h>

namespace bar
{
    void Hello()
    {
        std::cout << "bar::Hello()" << std::endl;
        foo::Hello();
    }

    int FuncA()
    {
        std::cout << "bar::FuncA()" << std::endl;
        return 1;
    }

    int FuncB()
    {
        std::cout << "bar::FuncB()" << std::endl;
        return FuncA() * 10;
    }
}