#pragma once
#include "Versions.h"

#if defined(_WIN32)
#  if !defined(FARSCAPE_STATIC)
#    if defined(FARSCAPE_BUILD_EXPORTS)
#      define FARSCAPE_API __declspec(dllexport)
#    else
#      define FARSCAPE_API __declspec(dllimport)
#    endif
#  else
#    define FARSCAPE_API
#  endif
#else // non windows
#  define FARSCAPE_API
#  define FS_PLATFORM Apple
#endif


#if defined(_WIN32)
#  define FS_PLATFORM Windows
#else // non windows
#  define FS_PLATFORM Apple
#  define FARSCAPE_API
#endif


// TODO: come up with solution for mac __debugbreak()
#if defined(FS_ENABLE_ASSERTS) && defined(_WIN32)
	#define FS_ASSERT(x, ...) { if(!(x)) {FS_ERROR("Assertion failed! {0}", __VA_ARGS__); __debugbreak(); } }
	#define FS_CORE_ASSERT(x, ...) { if(!(x)) {FS_CORE_ERROR("Assertion failed! {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define FS_ASSERT(x, ...) 
	#define FS_CORE_ASSERT(x, ...) 
#endif

#define BIT(x) (1 << x)

#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)

// An object interface which can lift any weight
namespace Farscape {
	class FARSCAPE_API IObject
	{

	};
}