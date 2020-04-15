#pragma once

#include <string>

#ifdef WIN32
#    ifdef FOOLIBRARY_EXPORTS
#        define FOOLIBRARY_API __declspec(dllexport)
#    else
#        define FOOLIBRARY_API __declspec(dllimport)
#    endif
#else
#    define FOOLIBRARY_API
#endif

#ifdef WIN32
#	define CALLING_CONVENTION __stdcall
#else
#	define CALLING_CONVENTION
#endif

class FooSpi
{
public:
	virtual std::string CALLING_CONVENTION GetName() = 0;
};

class FOOLIBRARY_API FooApi
{
public:
	virtual void CALLING_CONVENTION RegisterSpi(FooSpi* fooSpi) = 0;

	virtual void CALLING_CONVENTION PrintName() = 0;
};

extern "C"
{
	FOOLIBRARY_API FooApi* CALLING_CONVENTION CreateFooApi();
}

