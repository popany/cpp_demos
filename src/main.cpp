#include <iostream>
#include <libfoo/foo.h>
#include <libbar/bar.h>
#include "demo.h"

int main()
{
    demo::Hello();
    foo::Hello();
    bar::Hello();

    return 0;
}