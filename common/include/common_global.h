#pragma once

#  if defined(COMMON_LIBRARY)
#    define COMMON_EXPORT __declspec(dllexport)
#  else
#    define COMMON_EXPORT __declspec(dllimport)
#  endif
#pragma warning( disable: 4251 )