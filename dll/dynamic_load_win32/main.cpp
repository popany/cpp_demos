#include <string>
#include <iostream>
#include <windows.h>
#include "foo_api.h"

typedef FooApi* __stdcall CreateFooApiFunc();

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
	HINSTANCE fooApiDll = LoadLibraryA("../../foo_api/Debug/foo_api.dll");
	CreateFooApiFunc* CreateFooApi = (CreateFooApiFunc*)GetProcAddress(fooApiDll, "CreateFooApi");

	FooApi* fooApi = CreateFooApi();
	MyFooSpi fooSpi;
	fooSpi.SetName("123");

	fooApi->RegisterSpi(&fooSpi);
	fooApi->PrintName();
	delete fooApi;
}

int main()
{
	Run();

	return 0;
}