#include "foo_api.h"

#include <iostream>
#include <string>

class MyFooSpi : public FooSpi
{
	std::string name;

public:
	MyFooSpi()
	{
	}

	void SetName(const std::string& name)
	{
		this->name = name;
	}

	std::string GetName() override
	{
		return this->name;
	}
};

void Run()
{
	MyFooSpi fooSpi;
	FooApi* fooApi = CreateFooApi();

	fooApi->RegisterSpi(&fooSpi);
	fooSpi.SetName("abc");
	fooApi->PrintName();
	delete fooApi;
}

int main()
{
	Run();

	return 0;
}