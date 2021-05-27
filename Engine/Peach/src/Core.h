#pragma once

#ifdef P_PLATFORM_WINDOWS
#ifdef P_BUILD_DLL
#define PEACH_API __declspec(dllexport)
#else 
#define PEACH_API __declspec(dllimport)

#endif
#else
#error Peach only supports windows
#endif