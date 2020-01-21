#include "foo.h"
#include <iostream>
#include <boost/thread.hpp>

namespace foo
{
    void Hello()
    {
        boost::thread thread([]() { std::cout << "foo::Hello()" << std::endl; });
        thread.join();
    }
}