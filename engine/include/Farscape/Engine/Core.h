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
