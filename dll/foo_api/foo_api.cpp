#include "foo_api.h"
#include <iostream>
#include <string>

class MyFooApi : public FooApi
{
	FooSpi* fooSpi;

public:

	void RegisterSpi(FooSpi* fooSpi)
	{
		this->fooSpi = fooSpi;
	}

	void PrintName()
	{
		std::cout << "Name: " << fooSpi->GetName() << std::endl;
	};
};

FooApi* CreateFooApi()
{
	return new MyFooApi();
}