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
}