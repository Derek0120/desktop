#pragma once
#if defined(_WIN32)
#  if defined(BASE_LIBRARY)
#    define BASE_EXPORT __declspec(dllexport)
#  else
#    define BASE_EXPORT __declspec(dllimport)
#  endif
#else
#define BASE_EXPORT __attribute__((visibility("default")))
#endif
#pragma warning( disable: 4251 )