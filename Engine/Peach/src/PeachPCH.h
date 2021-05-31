#pragma once


#include <stdio.h>
#include <iostream> // std::cout
#include <sstream> // stringstream
#include <memory> // smart pointers
#include <vector>
#include <SDL.h>


#define WIN32_LEAN_AND_MEAN
#include <windows.h>

//ADDITIONAL ENGINE INCLUDES
#include "MathStructs.h"

#pragma region Templates & Macros
template<class T>
inline void SafeDelete(T& pObjectToDelete)
{
	if (pObjectToDelete != nullptr)
	{
		delete(pObjectToDelete);
		pObjectToDelete = nullptr;
	}
}

#pragma endregion
