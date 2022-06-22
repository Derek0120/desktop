#pragma once

#  if defined(BASE_LIBRARY)
#    define BASE_EXPORT __declspec(dllexport)
#  else
#    define BASE_EXPORT __declspec(dllimport)
#  endif
#pragma warning( disable: 4251 )