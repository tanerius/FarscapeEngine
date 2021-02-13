#pragma once

#if defined(_WIN32)
#  if defined(FARSCAPE_BUILD_EXPORTS)
#    define FARSCAPE_API __declspec(dllexport)
#  else
#    define FARSCAPE_API __declspec(dllimport)
#  endif
#else // non windows
#  define FARSCAPE_API
#endif

#if defined(FS_ENABLE_ASSERTS)
	#define FS_ASSERT(x, ...) { if(!(x)) {FS_ERROR("Assertion failed! {0}", __VA_ARGS__); __debugbreak(); } }
	#define FS_CORE_ASSERT(x, ...) { if(!(x)) {FS_CORE_ERROR("Assertion failed! {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define FS_ASSERT(x, ...) 
	#define FS_CORE_ASSERT(x, ...) 
#endif

#define BIT(x) (1 << x)