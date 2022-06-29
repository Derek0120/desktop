#pragma once
#if defined(_WIN32)
#  if defined(COMMON_LIBRARY)
#    define COMMON_EXPORT __declspec(dllexport)
#  else
#    define COMMON_EXPORT __declspec(dllimport)
#  endif
#else
#define COMMON_EXPORT __attribute__((visibility("default")))
#endif
#pragma warning( disable: 4251 )